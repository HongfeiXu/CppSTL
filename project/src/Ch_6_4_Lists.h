#pragma once
/*

chapter 6.4 Lists

Lists 使用一个 doubly linked list 来管理元素。

2017.10.21

*/

#include <list>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

using namespace std;

namespace CH6_4_LISTS_H
{
//////////////////////////////////////////////////////////////////////////
// 6.4.1 Lists 的能力
// 不支持随机存取
// 任何位置上执行元素的安插和移除都很快
// 安插和删除动作并不会使指向其他元素的各个 pointers、references、iterators 失效！！！

//////////////////////////////////////////////////////////////////////////
// 6.4.2 Lists 的操作函数

// 迭代器相关函数 Iterator Functions
// 注：由于不支持随机存取，lists 既不提供 subscript 操作符，也不提供 at()。
// 只有运用迭代器，才能够存取 list 中的各个元素。
// 并且 list 提供的迭代器只是 双向迭代器，而非随机迭代器。
// 所以凡是用到随机存取迭代器的算法（所有用来操作元素顺序的算法——特别是排序算法——都归此类）你都不能调用。
// 不过可以拿 list 的特殊成员函数 sort() 代替。

// 元素的安插 Inserting 和移除 Removing
// 注：Lists 增加了 remove() 和 remove_if() 算法应用于自身的特殊版本。
// 这要比普通版本的 remove 算法更快。
void f()
{
	list<int> coll { 1,1,2,3,4,5 };
//	coll.remove_if(bind2nd(modulus<int>(), 2));			// 移除所有奇数
	coll.remove_if(not1(bind2nd(modulus<int>(), 2)));	// 移除所有偶数

	copy(coll.begin(), coll.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
}

// Lists 的特殊变动性操作 Special Modifying Operations
// unique splice sort merge
void f2()
{
	list<int> coll1 { 1,3,5 };
	list<int> coll2 { 2,4,6 };
	coll1.merge(coll2, less<int>());

	cout << "coll1: ";
	copy(coll1.begin(), coll1.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "coll2: ";
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	list<int> coll3 { 7,8,9 };
	coll3.splice(coll3.begin(), coll1);

	cout << "coll1: ";
	copy(coll1.begin(), coll1.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "coll3: ";
	copy(coll3.begin(), coll3.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	/*
	coll1: 1 2 3 4 5 6
	coll2:
	coll1:
	coll3: 1 2 3 4 5 6 7 8 9
	请按任意键继续. . .
	*/
}

//////////////////////////////////////////////////////////////////////////
// 6.4.3 异常处理


//////////////////////////////////////////////////////////////////////////
// 6.4.4 List 运用实例

void printLists(const list<int>& l1, const list<int>& l2)
{
	cout << "list1: ";
	copy(l1.begin(), l1.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "list2: ";
	copy(l2.begin(), l2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
}

void f3()
{
	list<int> list1, list2;
	for (int i = 0; i != 6; ++i)
	{
		list1.push_back(i);
		list2.push_front(i);
	}
	printLists(list1, list2);

	// insert all elements of list1 before the first element with value 3 of the list2
	list2.splice(find(list2.begin(), list2.end(), 3), 
				 list1);
	printLists(list1, list2);

	// move first element to the end
	list2.splice(list2.end(),		// destination position
				 list2,				// source list
				 list2.begin());	// source position
	printLists(list1, list2);
	
	// sort second list, assign to list1 and remove duplicates
	list2.sort();
	list1 = list2;
	list2.unique();
	printLists(list1, list2);

	// merge both sorted lists into the first list
	list1.merge(list2);
	printLists(list1, list2);

	/*
	list1: 0 1 2 3 4 5
	list2: 5 4 3 2 1 0
	list1:
	list2: 5 4 0 1 2 3 4 5 3 2 1 0
	list1:
	list2: 4 0 1 2 3 4 5 3 2 1 0 5
	list1: 0 0 1 1 2 2 3 3 4 4 5 5
	list2: 0 1 2 3 4 5
	list1: 0 0 0 1 1 1 2 2 2 3 3 3 4 4 4 5 5 5
	list2:
	请按任意键继续. . .
	*/
}

} // !CH6_4_LISTS_H
