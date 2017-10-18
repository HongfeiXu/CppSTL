#pragma once

/*

chapter 1~3

2017.10.16

*/

#include <iostream>
#include <vector>
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
	int size() { return stack.size(); }
};

void f3()
{
	MyStack s1(40);
	cout << s1.size() << endl;
//	MyStack s2 = 4;				// ERROR
}
}	// !CH_1_3_H
