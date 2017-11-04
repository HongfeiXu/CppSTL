#pragma once
/*

chapter 6.7 其他 STL 容器

STL 是个框架，除了提供标准容器，它也允许你使用其它数据作为容器。你可以使用字符串或数组作为 STL 容器，也可以自行撰写特殊容器以满足特殊需求。
下面是是你的容器“STL化”的三种不同方式：
1. The invasive approach 侵入式，直接提供 STL 容器所需接口。诸如 begin() 和 end() 之类的常用函数。
2. The noninvasive approach 非侵入式，撰写或提供特殊迭代器，作为算法和特殊容器之间的界面。
3. The wrapper approach 包装法，写一个外套类别（wrapper class）来包装任何数据结构，并显示出与 STL 容器相似的接口。

2017.10.29

*/

#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

namespace CH_6_7_H
{
//////////////////////////////////////////////////////////////////////////
// 6.7.1 Strings 可被视为一种 STL 容器

// C++ 标准程序库中的 string 类别，是“以侵入性作法编写STL容器”的一个好例子。Strings 可被视为以字符为元素的一种容器。
// Strings 提供了成员函数 begin() 和 end()，同时支持迭代器和迭代器配接器，strings 也提供了一些操作函数，如 push_back() 用以支持 back inserters.

//////////////////////////////////////////////////////////////////////////
// 6.7.2 Arrays 可被视为一种 STL 容器

// array 不是类别，所以不提供 begin() 和 end() 等成员函数，也不允许存在任何成员函数。这里，我们只能采用非侵入性作法或包装法。

// 直接运用数组
// 注：千万注意，要正确传递数组尾部位置，这里是 coll+6。
void f()
{
	int coll[] = { 5,6,2,4,1,3 };

	transform(coll, coll + 6,
			  coll,
			  coll,
			  multiplies<int>());

	// sort beginning with the second element
	sort(coll + 1, coll + 6);

	// print all elements
	copy(coll, coll + 6,
		 ostream_iterator<int>(cout, " "));
	cout << endl;
}

// now we have std::begin() and std::end() since C++11
void f2()
{
	int coll[] = { 5,6,2,4,1,3 };

	transform(std::begin(coll), std::end(coll),
			  std::begin(coll),
			  std::begin(coll),
			  multiplies<int>());
	sort(std::begin(coll) + 1, std::end(coll));

	copy(std::begin(coll), std::end(coll),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
}

}  // !CH_6_7_H
