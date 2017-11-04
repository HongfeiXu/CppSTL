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
// 2.2 �µ��������� 

// Member Templatep ����Աģ�壩
// ͨ������Ϊ template classes �еĳ�Ա�ṩ�Զ��ͱ�ת��

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

// Template constructor �� member template ��һ��������ʽ��
// ͨ�����ڡ��ڸ��ƶ���ʱʵ����ʽ�ͱ�ת������
// ע�⣬ template constructor �����ڱ� implicit copy constructor��
// ����ͱ���ȫ�Ǻϣ��� implicit copy constructor �ͻᱻ���������������á�
template <class T>
class MyClass2 {
public:
	template <class U>
	MyClass2(const MyClass2<U>& x)
	{
	}
};

// Explicit Initialization �������ͱ����ʾ��ʼ����
// ������Կ���ȷ��������׫д template �������ʱ���κ��ͱ���һ��ȷ�еĳ�ֵ��
// Reference: http://en.cppreference.com/w/cpp/language/types
template <class T>
void f2()
{
	T x = T();	// ��� T Ϊ�����ͣ��򱻳�ʼ��Ϊ 0
}


// �ؼ��� explicit
// ��������ֹ�����������캯��(single argument constructor)���������Զ��ͱ�ת����
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
	�밴���������. . .
	*/
}

}	// !CH_1_3_H
