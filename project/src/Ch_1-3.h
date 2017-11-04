#pragma once

/*

chapter 1~3

2017.10.16

*/

#include <iostream>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

namespace CH_1_3_H
{
//////////////////////////////////////////////////////////////////////////
// 2.2 新的语言特性 

// Member Templatep （成员模板）
// 通常用来为 template classes 中的成员提供自动型别转换

template <class T>
class MyClass {
private:
	T value;
public:
	template<class X>
	void assign(const MyClass<X>& x)
	{
		value = x.getValue();
	}
	T getValue() const
	{
		return value;
	}
};

void f()
{
	MyClass<double> d;
	MyClass<int> i;

	d.assign(d);	// OK
	d.assign(i);	// OK (int is assignable to double)
}

// Template constructor 是 member template 的一个特殊形式。
// 通常用于“在复制对象时实现隐式型别转换”。
// 注意， template constructor 并不遮蔽 implicit copy constructor，
// 如果型别完全吻合，则 implicit copy constructor 就会被产生出来并被调用。
template <class T>
class MyClass2 {
public:
	template <class U>
	MyClass2(const MyClass2<U>& x)
	{
	}
};

// Explicit Initialization （基本型别的显示初始化）
// 这个特性可以确保我们在撰写 template 程序代码时，任何型别都有一个确切的初值。
// Reference: http://en.cppreference.com/w/cpp/language/types
template <class T>
void f2()
{
	T x = T();	// 如果 T 为基本型，则被初始化为 0
}


// 关键字 explicit
// 可用来禁止“单参数构造函数(single argument constructor)”被用于自动型别转换。
class MyStack {
private:
	vector<int> stack;
public:
	MyStack(): stack() { }
	explicit MyStack(int size) : stack(size, 0)
	{
	}
	vector<int>::size_type size() { return stack.size(); }
};

void f3()
{
	MyStack s1(40);
	cout << s1.size() << endl;
//	MyStack s2 = 4;				// ERROR
}

//////////////////////////////////////////////////////////////////////////
// 3.1.9 New Template Features

/*
Variadic Templates

Since C++11, templates can have parameters that accept a variable number of template arguments.
This ability is called variadic templates. For example, you can use the following to call print()
for a variable number of arguments of different types:
*/

void Print()
{

}

template<typename T, typename... Types>
void Print(const T& firstArg, const Types... args)
{
	std::cout << firstArg << std::endl;	// print first argument
	Print(args...);						// call print() for remaining arguments
}

/*
If one or more arguments are passed, the function template is used, which by specifying the first
argument separately allows the first argument to print and then recursively calls print() for the
remaining arguments. To end the recursion, the non-template overload of print() is provided.
*/

void f4()
{
	Print(7.5, "Hello", bitset<16>(377), 42);

	/*
	7.5
	Hello
	0000000101111001
	42
	请按任意键继续. . .
	*/
}

}	// !CH_1_3_H
