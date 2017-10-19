#pragma once
/*

chapter 6.1

2017.10.19

*/

#include <vector>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <iostream>
#include <iterator>

namespace CH6_1
{

//////////////////////////////////////////////////////////////////////////
// 6.1.1 容器的共同能力
// 注：所有容器提供的都是 “value语意”而非“reference语意”。
// 即容器进行元素的安插操作时，内部实施的是拷贝操作，置于容器内。

void f1()
{
	int arr[] = { 1,2,3,4 };

	std::set<int> c(arr, arr + sizeof(arr) / sizeof(arr[0]));

	std::copy(c.begin(), c.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::deque<int> c2((std::istream_iterator<int>(std::cin)),	// 不要遗漏此处的“多余的”括号，
																// 否则表达式的意义将会迥然不同，
																// 不加括号 c2 将会被视为一个函数声明。
					   std::istream_iterator<int>());
}
}	// CH6_1
