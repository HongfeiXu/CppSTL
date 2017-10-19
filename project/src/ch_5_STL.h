#pragma once

/*

chapter 5 Standard Template Library

STL 提供用于处理数据的容器和算法。本章详细介绍 STL 的概念，并逐步解释其中的概念、问题、特殊编程技术，以及它们所扮演的角色。

2017 10.17

*/
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <functional>		// to use std::greater
#include <algorithm>
#include <iterator>
#include <cstdlib>			// stdLLabs()
#include <string>

#include "Utility.h"

namespace CH_5_STL_H
{

//////////////////////////////////////////////////////////////////////////
// 5.2 容器 Containers
// 1. 序列式容器 Sequence containers，此乃可序(ordered)群集，即每个元素均有固定的位置——取决于插入时机和地点，和元素值无关。
// vector deque list
// 2. 关联式容器 Associative containers，此乃已序(sorted)群集，元素位置取决于特定的排序规则。
// set multiset map multimap

// 5.2.1 序列式容器 Sequence Containers
// Vectors Deques Lists
// 此外也可将 strings  和 array 当做一种序列式容器。
// vector
// dequeue (double-ended queue)
// list （由双向链表实作而成）
void f()
{
	std::vector<int> vi;
	for (int i = 1; i <= 6; i++)
	{
		vi.push_back(i);
	}
	for (int i = 0; i < static_cast<int>(vi.size()); ++i)
	{
		std::cout << vi[i] << " ";
	}
	std::cout << std::endl;

	std::deque<float> df;
	for (int i = 1; i <= 6; i++)
	{
		df.push_front(i * 1.1f);
	}
	for (int i = 0; i < static_cast<int>(df.size()); ++i)
	{
		std::cout << df[i] << " ";
	}
	std::cout << std::endl;

	std::list<char> lc;
	for (char c = 'a'; c <= 'z'; ++c)
	{
		lc.push_back(c);
	}
	while (!lc.empty())
	{
		std::cout << lc.front() << ' ';
		lc.pop_front();
	}
	std::cout << std::endl;
}

// 5.2.2 关联式容器 Associative Containers
// set multiset map multimap

// 5.2.3 容器适配器 Container Adapters
// Stacks Queues Priority Queues

void f2()
{
	std::list<char> lc;
	for (char c = 'a'; c <= 'z'; ++c)
	{
		lc.push_back(c);
	}

	std::list<char>::const_iterator pos;		// pos 以只读模式遍历元素
	for (pos = lc.begin(); pos != lc.end(); pos++)
	{
		std::cout << *pos << ' ';
	}
	std::cout << std::endl;
}

// 5.3 迭代器

// 5.3.1 关联式容器的运用实例
// set and multiset
void f3()	// 展示如何在 set 之中安插元素，并使用迭代器来打印它们
{
	typedef std::set<int> IntSet;	// 缺省的排序准则，以 operator< 为依据，对元素进行排序。
	typedef std::set<int, std::greater<int>> IntSetDescend;	// 递减方式排序
	typedef std::multiset<int> IntMultiSet;

	IntSet coll;
	coll.insert(3);
	coll.insert(1);
	coll.insert(5);
	coll.insert(4);
	coll.insert(1);
	coll.insert(6);
	coll.insert(2);

	IntMultiSet::const_iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos)
	{
		std::cout << *pos << ' ';
	}
	std::cout << std::endl;
}

// multimap
void f4()
{
	typedef multimap<int, string> IntStringMMap;

	IntStringMMap coll;		// container for int/string values
	coll.insert(make_pair(5, "tagged"));
	coll.insert(make_pair(2, "a"));
	coll.insert(make_pair(1, "this"));
	coll.insert(make_pair(4, "of"));
	coll.insert(make_pair(6, "strings"));
	coll.insert(make_pair(1, "is"));
	coll.insert(make_pair(3, "multimap"));

	IntStringMMap::const_iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos)
	{
		std::cout << pos->second << ' ';
	}
	std::cout << std::endl;
}
// map
// 将 Maps 当做关联式数组 associative arrays。所谓关联式数组就是：索引可以采用任何型别。
void f5()
{
	typedef map<string, float> StringFloatMap;
	StringFloatMap coll;
	coll["VAT"] = 0.15f;
	coll["Pi"] = 3.1415f;
	coll["an arbitrary number"] = 4983.223f;
	coll["NULL"] = 0;
	coll["an arbitrary number"] = 123;	// 键值 "an arbitrary number" 对应的实值更新
	coll["zero"];	// 键值为 "zero" 实值为 0

	StringFloatMap::const_iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos)
	{
		std::cout << "key: \"" << pos->first << "\" "
			<< "value: " << pos->second << std::endl;
	}

	/*
	
	key: "NULL" value: 0
	key: "Pi" value: 3.1415
	key: "VAT" value: 0.15
	key: "an arbitrary number" value: 123
	key: "zero" value: 0
	请按任意键继续. . .
	
	*/

}

// 5.3.2 迭代器分类 Bidirectional iterator
// 1. 双向迭代器 以递增运算前进或以递减运算后退
// list set multiset map multimap 均属此类
// 2. 随机存取迭代器 Random access iterator
// 不但具备双向迭代器的所有属性，还具备随机访问能力。
// 可以对迭代器增加或减少一个偏移量、处理迭代器之间的距离、或是使用 < 和 > 之类的相对关系操作符来比较两个迭代器。
// vector deque string 均属此类
// 注：为了撰写尽可能与容器类别无关的泛型程序代码，最好不要使用随机存取迭代器的特有操作例如：
/*
for (pos = coll.begin(); pos != coll.end(); ++pos)
{
	...	
}

for (pos = coll.begin(); pos < coll.end(); ++pos)
{
	...		// 对于 list set map 无法运作
}
*/

//////////////////////////////////////////////////////////////////////////
// 5.4 算法
// a simple example
void f6()
{
	std::vector<int> coll;
	std::vector<int>::iterator pos;

	coll.push_back(2);
	coll.push_back(5);
	coll.push_back(4);
	coll.push_back(1);
	coll.push_back(6);
	coll.push_back(3);

	pos = std::min_element(coll.begin(), coll.end());
	std::cout << "min: " << *pos << std::endl;
	pos = std::max_element(coll.begin(), coll.end());
	std::cout << "max: " << *pos << std::endl;

	std::sort(coll.begin(), coll.end());
	PRINT_ELEMENTS<std::vector<int>>(coll);
	std::cout << std::endl;

	pos = std::find(coll.begin(), coll.end(),
					3);
	// reverse the order of the found element with value 3 and all following elements
	reverse(pos, coll.end());
	PRINT_ELEMENTS<std::vector<int>>(coll);
	std::cout << std::endl;
}

// 5.4.1 区间 Ranges
// 如何确定一个容器（如 list）上的两个非随机存取迭代器的前后关系。
void f7()
{
	std::list<int> li;
	for (int i = 40; i >= 20; --i)
	{
		li.push_back(i);
	}

	std::list<int>::iterator pos25 = find(li.begin(), li.end(), 25);
	std::list<int>::iterator pos30 = find(li.begin(), li.end(), 30);

	// ERROR: pos25 and pos30 are not random access iterator
	//if (pos25 < pos30)
	//{
	//}

	std::list<int>::iterator pos25_v2 = find(li.begin(), li.end(), 25);
	std::list<int>::iterator pos30_v2 = find(li.begin(), pos25_v2, 30);
	if (pos30_v2 != pos25_v2)
	{
		std::cout << "[pos30_v2; pos25_v2) is valid" << std::endl;
	}
	else
	{
		pos30_v2 = find(pos25_v2, li.end(), 30);
		if (pos30_v2 != pos25_v2)
		{
			std::cout << "[pos25_v2; pos30_v2) is valid" << std::endl;
		}
		else
		{
			std::cout << "both pos25_v2 and pos30_v2 are end()" << std::endl;
		}
	}
}

// 5.4.2 处理多个区间
void f8()
{
	std::list<int> coll1;
	std::vector<int> coll2;

	for (int i = 1; i <= 9; ++i)
	{
		coll1.push_back(i);
	}

	coll2.resize(coll1.size());

	// copy elements from first into second collection
	// overwrites existing elements in destination
	std::copy(coll1.begin(), coll1.end(), 
			  coll2.begin());

	PRINT_ELEMENTS<std::vector<int>>(coll2);
	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 5.5 迭代器之配接器 Iterator Adapters
// 1. Insert iterators
// 2. Stream iterators
// 3. Reverse iterators

// 5.5.1 Insert iterators
// 1. Back inserters		安插于容器最尾端，调用 push_back
// 2. Front inserters		安插于容器最前端，调用 push_front
// 3. General inserters		一般性安插器，调用 insert
void f9()
{
	std::list<int> coll1;
	for (int i = 1; i <= 9; i++)
		coll1.push_back(i);

	std::vector<int> coll2;
	std::copy(coll1.begin(), coll1.end(), 
			  std::back_inserter(coll2));
	PRINT_ELEMENTS<std::vector<int>>(coll2);
	std::cout << std::endl;

	std::deque<int> coll3;
	copy(coll1.begin(), coll1.end(), 
		 std::front_inserter(coll3));
	std::for_each(coll3.begin(), coll3.end(), [](const int& i) { std::cout << i << ' '; });
	std::cout << std::endl;

	std::set<int> coll4;
	copy(coll1.begin(), coll1.end(),
		 std::inserter(coll4, coll4.begin()));
	std::for_each(coll4.begin(), coll4.end(), [](const int& i) { std::cout << i << ' '; });
	std::cout << std::endl;
}

// 5.5.2 Stream iterators 流迭代器
//*******************************************************************
void f10()
{
	std::vector<std::string> coll;

	// read all words from the standard input
	std::copy(std::istream_iterator<std::string>(std::cin),		// 产生一个可以从“标准输入流 cin” 读取数据的 stream iterator
			  std::istream_iterator<std::string>(),				// 产生一个代表“流结束符号 end of stream”的迭代器
			  back_inserter(coll));

	// print all elements
	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<std::string>(std::cout, "\n"));

	// sort elements
	std::sort(coll.begin(), coll.end());

	// print all elements without duplicates
	std::unique_copy(coll.begin(), coll.end(),					// unique_copy 消除毗邻的重复值
					 std::ostream_iterator<std::string>(std::cout, "\n"));	
					// 产生一个 output stream iterator，透过 operator<< 向 cout 写入 strings。 第二个参数为元素之间的分隔符。
	/*
	Apple Mac Lenovo ThinkPad HP OMEN
	^Z
	Apple
	Mac
	Lenovo
	ThinkPad
	HP
	OMEN
	Apple
	HP
	Lenovo
	Mac
	OMEN
	ThinkPad
	请按任意键继续. . .
	*/
}

// 5.5.3 Reverse Iterators 逆向迭代器
void f11()
{
	std::vector<int> coll;
	for (int i = 1; i <= 9; ++i)
	{
		coll.push_back(i);
	}

	std::copy(coll.rbegin(), coll.rend(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 5.6 更易型算法 Manipulating Algorightms
// 指那些会移除 remove、重排 resort、修改 modify 元素的算法

// 5.6.1 移除元素 Removeing
void f12()
{
	std::list<int> coll;
	for (int i = 1; i <= 6; ++i)
	{
		coll.push_back(i);
		coll.push_front(i);
	}

	// print all elements of the collection
	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	// remove all elements with value 3
	// - retain new end, but not actually "remove" elements
	std::list<int>::iterator end = std::remove(coll.begin(), coll.end(),
				3);

	// print resulting elements of the collection
	std::copy(coll.begin(), end,
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	// print number of removed elements
	std::cout << "number of removed elements: "
		<< std::distance(end, coll.end()) << std::endl;

	// remove "removed" elements
	coll.erase(end, coll.end());

	// print all elements of the modified collection
	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	/*
	6 5 4 3 2 1 1 2 3 4 5 6
	6 5 4 2 1 1 2 4 5 6
	number of removed elements: 2
	6 5 4 2 1 1 2 4 5 6
	请按任意键继续. . .
	*/

	// one line
//	coll.erase(std::remove(coll.begin(), coll.end(), 3), coll.end());

	// 注： list 有 remove 成员函数，利用了 list 结构的有点，具有更好的效率
//	coll.remove(3);
}

// 5.6.2 更易型算法和关联式容器
// 更易型算法不能把关联容器当做操作目标。因为：如果更易型算法用于关联容器上，
// 会改变某位置上的值，进而破坏其已序（sorted）特性，
// 那就推翻了关联容器的基本原则：容器内的元素总是根据某个排序准则自动排序。
// 因此，为了保证这个原则，关联容器上的所有迭代器都被声明为指向常亮（不变量）。

void f13() // 如何从关联容器中删除元素
{
	std::set<int> coll;

	for (int i = 1; i <= 9; ++i)
		coll.insert(i);

	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::size_t num = coll.erase(3);

	std::cout << "number of removed elements: " << num << std::endl;

	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

// 5.6.3 算法 vs 成员函数
// 注：就算我们复合种种条件，得以使用某个算法，那也未必好。容器可能提供功能相似而性能更好的成员函数。
// 如 remove 和 list.remove
// 见下例
void f14()
{
	std::list<int> coll;
	for (int i = 1; i <= 6; ++i)
	{
		coll.push_back(i);
		coll.push_front(i);
	}

	// remove all elements with value 3
	// - poor performance
	coll.erase(std::remove(coll.begin(), coll.end(),
			   3),
			   coll.end());

	// remove all elements with value 4
	// - good performance
	coll.remove(4);

	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 5.7 使用者自定义之泛型函数 User-Defined Generic Functions

//template <class T>
//inline void PRINT_ELEMENTS(const T& coll, const char* optcstr = "")
//{
//	typename T::const_iterator pos;
//	std::cout << optcstr;
//	for (pos = coll.begin(); pos != coll.end(); ++pos)
//	{
//		std::cout << *pos << ' ';
//	}
//	std::cout << std::endl;
//}

//////////////////////////////////////////////////////////////////////////
// 5.8 以函数作为算法的参数

// 5.8.1 “以函数作为算法的参数” 实例示范
// for_each
void f15()
{
	std::vector<int> coll;
	for (int i = 1; i <= 9; ++i)
	{
		coll.push_back(i);
	}
	std::for_each(coll.begin(), coll.end(), [](const int& i) { std::cout << i << ' '; });
	std::cout << std::endl; 
}
// transform
// coll1->transform->coll2
void f16()
{
	std::set<int> coll1;
	std::vector<int> coll2;

	for (int i = 1; i <= 9; ++i)
		coll1.insert(i);
	std::cout << "initialized: ";
	PRINT_ELEMENTS(coll1, ' ');
	std::cout << std::endl;

	// transform each element from coll1 to coll2
	std::transform(coll1.begin(), coll1.end(),
				   back_inserter(coll2),
				   [](const int & elem) { return elem * elem; });

	std::cout << "squared: ";
	PRINT_ELEMENTS(coll2, ' ');
	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 5.8.2 判断式 Predicates

// Unary Predicates 一元判断式
// 典型用途是检查唯一参数的某项属性
// 这里 isPrime 为 Unary Predicates，可作为 find_if 的参数
bool isPrime(int number)
{
	// ignore negative sign
	number = std::abs(number);

	// 0 and 1 are prime number
	if (number == 0 || number == 1)
		return true;

	// find divisor that divides without a remainder
	int divisor = 0;
	for (divisor = number / 2; number % divisor != 0; --divisor)
		;

	// if no divisor greater than 1 is found, it is a prime number
	return divisor == 1;
}
void f17()
{
	std::list<int> coll;
	
	for (int i = 24; i <= 30; ++i)
		coll.push_back(i);

	list<int>::const_iterator pos;
	pos = std::find_if(coll.begin(), coll.end(),	// range
					   isPrime);					// unary predicate
	if (pos != coll.end())
		std::cout << *pos << " is first prime number found" << std::endl;
	else
		std::cout << "no prime number found" << std::endl;
}

// Binary Predicates 二元判断式
// 典型用途是比较两个参数的特定属性

class Person {
private:
	std::string firstname;
	std::string lastname;
public:
	Person() : firstname(), lastname() { }
	Person(std::string firstname_, std::string secondname_ )
		: firstname(firstname_), lastname(secondname_)
	{ }
	void PrintName()
	{
		std::cout << firstname << " " << lastname << std::endl;
	}
	std::string GetFirstname() const
	{
		return firstname;
	}
	std::string GetLastname() const
	{
		return lastname;
	}
};

// binary predicate:
// - returns whether a person is less than another person
bool personSortCriterion(const Person& p1, const Person& p2)
{
	return(p1.GetLastname() < p2.GetLastname() ||
		   (!(p2.GetLastname() < p1.GetLastname())) &&
		   p1.GetFirstname() < p2.GetFirstname());
}

void f18()
{
	std::deque<Person> coll;
	Person p1("Lebron", "James");
	Person p2("Kobe", "Bryant");
	Person p3("Ice", "MJ");
	coll.push_back(p1);
	coll.push_back(p2);
	coll.push_back(p3);

	std::cout << "pre: " << std::endl;
	std::for_each(coll.begin(), coll.end(),
				  [](const Person& person) { std::cout << person.GetFirstname() << " " << person.GetLastname() << std::endl; });

	std::sort(coll.begin(), coll.end(),			// range
			  personSortCriterion);				// sort criterion

	std::cout << "post: " << std::endl;
	std::for_each(coll.begin(), coll.end(),
				  [](const Person& person) { std::cout << person.GetFirstname() << " " << person.GetLastname() << std::endl; });
}

//////////////////////////////////////////////////////////////////////////
// 5.9 仿函数 Functors, Function Objects

// 5.9.1 什么是仿函数
// 什么是仿函数？任何东西，只要行为像函数，它就是个函数。因此如果你定义了一个对象，行为像函数，它就可以被当做函数来使用。
// 那么什么才算是具备函数行为？所谓函数行为，是指可以“使用小括号传递参数，借以调用某个东西”。
// 只需在类中定义 operator()，并给予合适的参数型别。

// Functor
class PrintInt {
public:
	void operator() (int elem) const
	{
		std::cout << elem << " ";
	}
};

void print(int elem)
{
	std::cout << elem << ' ';
}

void f19()
{
	std::vector<int> coll;
	for (int i = 1; i <= 9; ++i)
		coll.push_back(i);
	//std::for_each(coll.begin(), coll.end(), print);	// 以函数作为算法的参数
	std::for_each(coll.begin(), coll.end(), PrintInt());// 以仿函数作为算法的参数，
														// 其中 PrintInt() 产生出此类别的一个临时对象，当做 for_each() 算法的一个参数。
	std::cout << std::endl;
}

// 仿函数优点
// 1. 仿函数是 "smart functions"，
// 仿函数可拥有成员函数和成员变量，这意味着其拥有状态。另外，你可以在执行期(runtime)初始化它们。
// 2. 每个仿函数都有自己的型别
// 3. 仿函数通常比一般函数速度快

template <int theValue>
void add(int &elem)		// 对于 template 而言，更多细节在编译期就已经确定
{
	elem += theValue;
}

void f20()
{
	std::vector<int> coll;
	for (int i = 1; i <= 9; ++i)
		coll.push_back(i);
	std::for_each(coll.begin(), coll.end(), 
				  add<10>);
	//std::for_each(coll.begin(), coll.end(),	// ERROR
	//			  add<coll.front()>);			// 模板参数应该为编译时常量表达式，即编译时已经确定的值，这里的值在运行时确定
	PRINT_ELEMENTS(coll, ' ');
	std::cout << std::endl;
}
// Functor
class AddValue {
private:
	int theValue = 0;
public:
	AddValue(int theValue_) : theValue(theValue_) { }
	void operator() (int& elem)
	{
		elem += theValue;
	}
};

void f21()
{
	std::vector<int> coll;
	for (int i = 1; i <= 9; ++i)
		coll.push_back(i);
	std::for_each(coll.begin(), coll.end(),
				  AddValue(10));				// AddValue(10) 生成一个 AddValue 物件，并以 10 为初值。
	PRINT_ELEMENTS(coll, ' ');
	std::cout << std::endl;

	std::for_each(coll.begin(), coll.end(),
				  AddValue(coll.front()));		// 仿函数的成员变量可以在执行器初始化，这点一般函数是做不到的
												// AddValue(coll.front()) 生成一个 AddValue 物件，并以 coll.front() 为初值
	PRINT_ELEMENTS(coll, ' ');
	std::cout << std::endl;

	/*
	11 12 13 14 15 16 17 18 19
	22 23 24 25 26 27 28 29 30
	请按任意键继续. . .
	*/
}

//////////////////////////////////////////////////////////////////////////
// 5.9.2 预先定义的仿函数
// less<> greater<> negate<> multplies<> equal_to<>
void f22()
{
	std::vector<int> coll { 1,2,3,4,5 };
	std::transform(coll.begin(), coll.end(),	// source
				   coll.begin(),				// destination
				   std::negate <int>());		// operation
	PRINT_ELEMENTS(coll, ' ');
	std::cout << std::endl;
	std::transform(coll.begin(), coll.end(),	// first source
				   coll.begin(),				// second source
				   coll.begin(),				// destination
				   std::multiplies<int>());		// operation
	PRINT_ELEMENTS(coll, ' ');
	std::cout << std::endl;
}

// 透过一些特殊的函数适配器 function adaptors ，你可以将预先定义的仿函数和其它数值组合在一起，或使用特殊状况
// std::bind2nd 
// (deprecated in C++11) 
// (removed in C++17)
void f23()
{
	std::set<int, std::greater<int>> coll1;
	std::deque<int> coll2;

	for (int i = 1; i <= 9; ++i)
		coll1.insert(i);

	PRINT_ELEMENTS(coll1, ' ');
	std::cout << std::endl;

	// transform all elements into coll2 by multiplying 10
	std::transform(coll1.begin(), coll1.end(),					// source
				   back_inserter(coll2),						// destination
				   std::bind2nd(std::multiplies<int>(), 10));	// operation
					// 这里使用适配器 bind2nd，进行 multiplies<int> 运算时，
					// 以源群集的元素作为第一参数，10 作为第二参数。

	PRINT_ELEMENTS(coll2, ' ');
	std::cout << std::endl;

	// replace value equal to 70 with 42
	std::replace_if(coll2.begin(), coll2.end(),					// range
					std::bind2nd(std::equal_to<int>(), 70),		// range criterion
					42);										// new value

	PRINT_ELEMENTS(coll2, ' ');
	std::cout << std::endl;

	// remove all elements with values less than 50
	coll2.erase(std::remove_if(coll2.begin(), coll2.end(),		// range
				std::bind2nd(std::less<int>(), 50)),			// range criterion
				coll2.end());

	PRINT_ELEMENTS(coll2, ' ');
	std::cout << std::endl;
}

// std::mem_fun_ref 用来调用它所作用的元素的某个成员函数
// (deprecated in C++11)
// (removed in C++17)
void f24()
{
	std::vector<Person> coll;
	Person p1("Lebron", "James");
	Person p2("Kobe", "Bryant");
	Person p3("Ice", "MJ");
	coll.push_back(p1);
	coll.push_back(p2);
	coll.push_back(p3);

	for_each(coll.begin(), coll.end(),				// range
			 std::mem_fun_ref(&Person::PrintName));	// operation
}

//////////////////////////////////////////////////////////////////////////
// 5.10 容器内的元素

//////////////////////////////////////////////////////////////////////////
// 5.11 STL 内部的错误处理和异常处理

// 堆栈辗转开解：http://www.geeksforgeeks.org/stack-unwinding-in-c/

//////////////////////////////////////////////////////////////////////////
// 5.12 扩展 STL

}