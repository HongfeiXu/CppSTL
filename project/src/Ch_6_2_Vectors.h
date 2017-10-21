#pragma once
/*

chapter 6.2 Vectors

2017.10.21

*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <cstring>	// strcpy
#include <cstdio>	// printf

namespace CH6_2_VECTORS_H
{
//////////////////////////////////////////////////////////////////////////
// 6.2.1 Vectrors 的能力

// 大小 Size 和容量 Capacity
// size() empty() max_size()
// capacity()
// reserve()
// 注： vectors 的容量，概念上与 strings 类似。不过有一个大不同点： vector 不能用 reserve() 来缩减容量，而 string 可以。
// 如果调用 reserve() 所给的参数比当前 vector 的容量 capacity 还小，不会引发任何反应。

// 这里有一个间接缩减 vector 容量的小窍门。注意，两个 vectors 交换内容后，两者的容量也会互换。
// 注：这里 shrikCapacity() 会使所有 reference、pointers、iterators 失效。
template<class T>
void shrinkCapacity(std::vector<T>& v)
{
	std::vector<T> tmp(v);
	v.swap(tmp);
}
// 注： C++11 中新增了 std::vector::shrink_to_fit 函数，用来清除未被使用的空间

//////////////////////////////////////////////////////////////////////////
// 6.2.2 Vector 的操作函数

// 构造、拷贝和析构

// 赋值

// 元素存取
void f()
{
	std::vector<int> coll;
	try
	{
		coll.at(4) = 0;		// 如果 4 越界，则抛出 out_of_range
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}

	/*
	invalid vector<T> subscript
	请按任意键继续. . .
	*/
}

// 安插和移除

// 移除“与某值相等”的所有元素
void f2()
{
	std::vector<int> coll { 1,2,3,4,5,5,4,7 };
	coll.erase(std::remove(coll.begin(), coll.end(), 
			   4), 
			   coll.end());
	std::copy(coll.begin(), coll.end(), 
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}
// 移除“与某值相等”的第一个元素
void f3()
{
	std::vector<int> coll { 1,2,3,4,5,5,4,7 };
	std::vector<int>::const_iterator pos = std::find(coll.begin(), coll.end(),
													 4);
	coll.erase(pos);
	std::copy(coll.begin(), coll.end(), 
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 6.2.3 将 Vectors 当做一般 Arrays 使用
void f4()
{
	std::vector<char> v;
	v.resize(41);
	std::strcpy(&v[0], "hello world");
	std::printf("%s\n", &v[0]);
}

//////////////////////////////////////////////////////////////////////////
// 6.2.4 异常处理 Exception Handling
// vector 只支持最低限度的逻辑错误检查。subscript 操作符的安全版本是 at()。


//////////////////////////////////////////////////////////////////////////
// 6.2.5 Vectors 运用实例
void f5()
{
	std::vector<std::string> sentence;
	sentence.reserve(5);
	std::cout << sentence.capacity() << std::endl;
	sentence.shrink_to_fit();
	std::cout << sentence.capacity() << std::endl;

	sentence.reserve(5);

	// add some elements
	sentence.push_back("Hello,");
	sentence.push_back("how");
	sentence.push_back("are");
	sentence.push_back("you");
	sentence.push_back("?");

	// print elements seperated with spaces
	std::copy(sentence.begin(), sentence.end(),
			  std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;

	// print "technical data"
	std::cout << "max_size(): " << sentence.max_size() << std::endl;
	std::cout << "size(): " << sentence.size() << std::endl;
	std::cout << "capacity(): " << sentence.capacity() << std::endl;

	// swap second and fourth elements
	std::swap(sentence[1], sentence[3]);

	// insert element "always" before a element "?"
	sentence.insert(std::find(sentence.begin(), sentence.end(), "?"),
					"always");

	// assign "!" to the last element
	sentence.back() = "i";

	// print elements seperated with spaces
	std::copy(sentence.begin(), sentence.end(),
			  std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;

	// print "technical data"
	std::cout << "max_size(): " << sentence.max_size() << std::endl;
	std::cout << "size(): " << sentence.size() << std::endl;
	std::cout << "capacity(): " << sentence.capacity() << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 6.2.6 Class vector<bool>

void f6()
{
	std::vector<bool> coll { false, true, true };
	coll.flip();
	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	coll[2].flip();
	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}




}
