#pragma once
/*

chapter 6.5 Sets 和 Multisets

set 和 multiset 会根据特定的排序准则，自动将元素排序。
只要是 assignable、copyable、comparable 的型别，都可以成为 set 或 multiset 的元素型别。
如果没有传入特别的排序准则，就采用缺省准则 less。
所谓排序准则，必须定义 strict weak ordering，其意义如下：
1. 必须是“反对称的 antisymmetric”
2. 必须是“可传递的 transitive”
3. 必须是“非自反的 irreflexive”

基于这些特性，排序准则也可以用于相等性检验，即如果两个元素都不小于对方（或者说 op(x,y) 和 op(y,x) 都为假），则两个元素相等。

2017.10.21

*/

#include <set>
#include <functional>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "Utility.h"

using namespace std;

namespace CH6_5_SETS_H
{
//////////////////////////////////////////////////////////////////////////
// 6.5.1 Sets 和 Multisets 的能力

// sets 和 multisets 通常以平衡二叉树完成。
// 自动排序的主要优点在于使二叉树搜寻元素时有良好性能。其搜索算法具有对数复杂度。
// 但是，自动排序造成 set 和 multiset 的一个重要限制：你不能直接改变元素值，这样会打乱原本正确的顺序。
// 因此要改变元素值，必须先删除旧元素，在插入新元素。


//////////////////////////////////////////////////////////////////////////
// 6.5.2 Sets 和 Multisets 的操作函数
// 有两种方式可以定义排序准则：
// 1. 以 template 参数定义之。这种情况下，排序准则就是型别的一部分。例如： std::set<int, std::greater<int>> coll;
// 2. 以构造函数参数定义之。这种情况下，同一型别可以运用不同的排序准则，而排序准则的初始值或状态也可以不同。
// 如果执行器才获得排序准则，而且需要用到不同的排序准则（但数据型别必须相同），此方式方可排上用场。

// 非变动性操作 Nonmodifying Operations
// 用来查询大小、相互比较
// 注：元素比较动作只能用于型别相同的容器。否则会产生编译错误。
void f()
{
	set<float> c1 { 2,1,6,3};
	set<float, greater<float>> c2 { 5,1,0,2 };
	//if (c1 == c2)	// ERROR: different types
	//{

	//}
	
	copy(c1.begin(), c1.end(),
		 ostream_iterator<float>(cout, " "));
	cout << endl;

	copy(c2.begin(), c2.end(),
		 ostream_iterator<float>(cout, " "));
	cout << endl;
	
	/*
	1 2 3 6
	5 2 1 0
	请按任意键继续. . .
	*/
}

// 特殊的搜寻函数 Special Search Operations
// set 和 multiset 提供了特殊的搜寻函数，这些函数都是同名的 STL 算法的特殊版本。
// 有着对数时间复杂度。
// count find lower_bound upper_bound equal_range

void f2()
{
	set<int> c;

	c.insert(1);
	c.insert(2);
	c.insert(4);
	c.insert(5);
	c.insert(6);

	cout << "lower_bound(3): " << *c.lower_bound(3) << endl;
	cout << "upper_bound(3): " << *c.upper_bound(3) << endl;
	cout << "equal_range(3): " << *c.equal_range(3).first << " "
		<< *c.equal_range(3).second << endl;

	cout << endl;
	cout << "lower_bound(5): " << *c.lower_bound(5) << endl;
	cout << "upper_bound(5): " << *c.upper_bound(5) << endl;
	cout << "equal_range(5): " << *c.equal_range(5).first << " "
		<< *c.equal_range(5).second << endl;

	/*
	lower_bound(3): 4
	upper_bound(3): 4
	equal_range(3): 4 4

	lower_bound(5): 5
	upper_bound(5): 6
	equal_range(5): 5 6
	请按任意键继续. . .
	*/
}

// 赋值 Assignments 

// 迭代器相关函数 Iterator Functions
// 注：和其他所有关联容器类似，这里的迭代器是双向迭代器。所以，无法使用那些只能用于随机存取迭代器的 STL 算法。
// 更重要的是，对于迭代器而言，所有元素都被视为常熟，这可确保你不会人为改变元素值，从而打乱既定顺序。
// 例如你不能对它们调用 remove()，因为 remove() 实际上是以一个参数值覆盖被移除的元素。
// 如果要移除元素，你只能使用 set 或 multiset 所提供的成员函数。

// 元素的安插 Inserting 和移除 Removing
// insert erase clear
// 注：安插和移除多个元素时，单一调用（一次处理）比多次调用（逐一处理）快很多。
// 注：安插函数的返回值型别不尽相同。
// 注：所有拥有：“位置提示参数”的安插函数，其返回值型别都一样，不论是 set 还是 multiset，都只返回一个迭代器。
// http://en.cppreference.com/w/cpp/container/set/insert
// http://en.cppreference.com/w/cpp/container/multiset/insert

void f3()
{
	set<double> c;
	if (c.insert(3.3).second)
		cout << "3.3 inserted" << endl;
	else
		cout << "3.3 already exists" << endl;
}

// 如果 multisets 内含重复元素，你不能直接使用 erase 来删除这些重复元素中的第一个。可以采用如下做法。
void f4()
{
	typedef multiset<int> MSetInt;
	MSetInt coll { 2,1,1,1,3,4 };
	MSetInt::const_iterator pos = coll.find(1);
	if (pos != coll.cend())
		coll.erase(pos);
	copy(coll.begin(), coll.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	/*
	1 1 2 3 4
	请按任意键继续. . .
	*/
}


//////////////////////////////////////////////////////////////////////////
// 6.5.3 异常处理 Exception Handling

//////////////////////////////////////////////////////////////////////////
// 6.5.4 Sets 和 Multisets 运用实例

void f5()
{
	// type of the collecion: sets
	// - no duplicates
	// - elements are integral values
	// - descending order
	typedef set<int, greater<int>> IntSet;
	IntSet coll1;

	// insert elements in random order
	coll1.insert(4);
	coll1.insert(3);
	coll1.insert(5);
	coll1.insert(1);
	coll1.insert(6);
	coll1.insert(2);
	coll1.insert(5);

	// iterator voer all elements and print them
	IntSet::const_iterator pos;
	for (pos = coll1.begin(); pos != coll1.end(); ++pos)
	{
		cout << *pos << " ";
	}
	cout << endl;

	// insert 4 again and process return value
	pair<IntSet::iterator, bool> status = coll1.insert(4);
	if (status.second)
	{
		cout << "4 inserted as element "
			<< distance(coll1.begin(), status.first) + 1
			<< endl;
	}
	else
	{
		cout << "4 already exists" << endl;
	}

	// assign elements to another set with ascneding order
	set<int> coll2(coll1.begin(), coll1.end());

	// print all elements of the copy
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	// remove all elements up to element with value 3
	coll2.erase(coll2.begin(), coll2.find(3));

	// print all elements
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
	
	// remove all elements with value 5
	size_t num = 0;
	num = coll2.erase(5);
	cout << num << " element(s) removed" << endl;

	// print all elements
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
	/*
	6 5 4 3 2 1
	4 already exists
	1 2 3 4 5 6
	3 4 5 6
	1 element(s) removed
	3 4 6
	请按任意键继续. . .
	*/
}

void f6()
{
	// type of the collecion: sets
	// - no duplicates
	// - elements are integral values
	// - descending order
	typedef multiset<int, greater<int>> MIntSet;
	MIntSet coll1;

	// insert elements in random order
	coll1.insert(4);
	coll1.insert(3);
	coll1.insert(5);
	coll1.insert(1);
	coll1.insert(6);
	coll1.insert(2);
	coll1.insert(5);

	// iterator voer all elements and print them
	MIntSet::const_iterator pos;
	for (pos = coll1.begin(); pos != coll1.end(); ++pos)
	{
		cout << *pos << " ";
	}
	cout << endl;

	// insert 4 again and process return value
	MIntSet::iterator insert_pos = coll1.insert(4);
	cout << "4 inserted as element "
		<< distance(coll1.begin(), insert_pos) + 1
		<< endl;

	// assign elements to another set with ascneding order
	multiset<int> coll2(coll1.begin(), coll1.end());

	// print all elements of the copy
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	// remove all elements up to element with value 3
	coll2.erase(coll2.begin(), coll2.find(3));

	// print all elements
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	// remove all elements with value 5
	size_t num = 0;
	num = coll2.erase(5);
	cout << num << " element(s) removed" << endl;

	// print all elements
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
	/*
	6 5 5 4 3 2 1
	4 inserted as element 5
	1 2 3 4 4 5 5 6
	3 4 4 5 5 6
	2 element(s) removed
	3 4 4 6
	请按任意键继续. . .
	*/
}

//////////////////////////////////////////////////////////////////////////
// 6.5.5 执行期制定排序准则
// 通常你都会将排序准则定义为型别的一部分。但有时必须在执行期处理排序准则，或者你可能需要对同一种数据型别采用不同的排序准则。
// 此时你就需要一个“用来表现排序准则”的特殊型别，使你能够执行期间传递某个准则。
// 见下范例。

// type for sorting criterion
template<class T>
class RuntimeCmp {
public:
	enum cmp_mode { normal, reverse };
private:
	cmp_mode mode;

public:
	// constructor for sorting criterion
	// - default criterion uses value normal
	RuntimeCmp(cmp_mode m = normal) : mode(m)
	{
	}

	// comoparison of elements
	bool operator() (const T& t1, const T& t2) const
	{
		return mode == normal ? t1 < t2 : t2 < t1;
	}

	bool operator==(const RuntimeCmp& rc)
	{
		return mode == rc.mode;
	}
};

// type of a set that uses this sorting criterion
typedef set<int, RuntimeCmp<int>> IntSet;

void fill(IntSet& s)
{
	s.insert(4);
	s.insert(7);
	s.insert(5);
	s.insert(1);
	s.insert(6);
	s.insert(2);
	s.insert(5);
}

void f7()
{
	// create, fill, and print set with normal element order
	// - uses default sorting criterion
	IntSet coll1;
	fill(coll1);
	cout << "coll1: ";
	PRINT_ELEMENTS(coll1, ' ');
	cout << endl;

	// create sorting criterion with reverse element order
	RuntimeCmp<int> reverse_order(RuntimeCmp<int>::reverse);

	// create, fill, and print set with reverese element order
	IntSet coll2(reverse_order);
	fill(coll2);
	cout << "coll2: ";
	PRINT_ELEMENTS(coll2, ' ');
	cout << endl;

	coll1 = coll2;		// coll1 和 coll2 拥有相同型别 set<int, RuntimeCmp<int>>。 assignment 操作符不仅赋值了元素，也赋值了排序准则。
	coll1.insert(3);
	cout << "coll1: ";
	PRINT_ELEMENTS(coll1, ' ');
	cout << endl;

	if (coll1.value_comp() == coll2.value_comp())
	{
		cout << "coll1 and coll2 have same sorting criterion"
			<< endl;
	}
	else
	{
		cout << "coll1 and coll2 have different sorting criterion"
			<< endl;
	}

	/*
	coll1: 1 2 4 5 6 7
	coll2: 7 6 5 4 2 1
	coll1: 7 6 5 4 3 2 1
	coll1 and coll2 have same sorting criterion
	请按任意键继续. . .
	*/
}

// 注：在这个程序中，RuntimeCmp<> 是一个简单的 template，提供“执行期间面对任意型别定义一个排序准则”的泛化能力。
// 其 default 构造函数采用默认值 normal，按升序排序。你也可以将 RuntimeCmp<>::reverse 传递给构造函数，便能按降序排序。

} // !CH6_5_SETS_H
