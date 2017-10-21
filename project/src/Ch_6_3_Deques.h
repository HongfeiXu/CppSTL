#pragma once
/*

chapter 6.3 Deques

Deques 也采用动态数组来管理元素，提供随机存取，并有着和 vector 几乎一模一样的接口。
不同的是 deque 的动态数组头尾都开放，因此在头尾两端进行快速安插和删除。
为了获取这种能力， deque 通常作为一组独立区块，第一区块朝着某方向扩展，最后一个区块朝着另一方向扩展。

2017.10.21

*/

#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

namespace CH6_3_DEQUES_H
{

//////////////////////////////////////////////////////////////////////////
// 6.3.1 Deques 的能力

//////////////////////////////////////////////////////////////////////////
// 6.3.2 Deques 的操作函数

//////////////////////////////////////////////////////////////////////////
// 6.3.3 异常处理

//////////////////////////////////////////////////////////////////////////
// 6.3.4 Deques 运用实例

void f()
{

	deque<string> coll;

	coll.assign(3, string("string"));
	coll.push_back("last string");
	coll.push_front("first string");

	// print elements separated by newlines
	copy(coll.begin(), coll.end(),
		 ostream_iterator<string>(cout, "\n"));
	std::cout << std::endl;

	coll.pop_front();
	coll.pop_back();

	// insert "another" into every element but the first
	for (size_t i = 1; i != coll.size(); ++i)
	{
		coll[i] = "another " + coll[i];
	}

	// print elements separated by newlines
	copy(coll.begin(), coll.end(),
		 ostream_iterator<string>(cout, "\n"));
	std::cout << std::endl;

	// chage size to four elements 
	coll.resize(4, "resized string");

	// print elements separated by newlines
	copy(coll.begin(), coll.end(),
		 ostream_iterator<string>(cout, "\n"));
	std::cout << std::endl;

	/*
	first string
	string
	string
	string
	last string

	string
	another string
	another string

	string
	another string
	another string
	resized string

	请按任意键继续. . .
	*/
}

} // !CH6_3_DEQUES_H
