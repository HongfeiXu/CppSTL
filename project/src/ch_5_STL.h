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
					 std::ostream_iterator<std::string>(std::cout, "\n"));	// 产生一个 output stream iterator，透过 operator<< 向 cout 写入 strings。 第二个参数为元素之间的分隔符。
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

	int num = coll.erase(3);

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


}