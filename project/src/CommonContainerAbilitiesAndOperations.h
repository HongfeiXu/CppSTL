#pragma once
/*

chapter 6.1 容器的共同能力和共通操作

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
// 1. 所有容器提供的都是 “value语意”而非“reference语意”。
// 注： 即容器进行元素的安插操作时，内部实施的是拷贝操作，置于容器内。
// 2. 总体而言，所有元素形成一个次序。
// 3. 一般而言，各项操作并非绝对安全。调用者必须确保传给操作函数的参数复合要求。

//////////////////////////////////////////////////////////////////////////
// 6.1.2 容器的共通操作

// 初始化 initialization
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
// 与大小相关的操作函数 Size Operations

// 比较 Comparisons

// 赋值 Assignments 和 swap()
// 注：容器的赋值操作代价比较高昂。如果两个容器型别相同，且拷贝后源容器不在被使用，那么我们可以使用一个简单的优化方法：swap()。


}	// CH6_1
