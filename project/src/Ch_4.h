#pragma once

/*

chapter 4 ͨ�ù��� Utilities

2017 10.17

*/

#include <utility>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>

namespace CH_4_H
{
//////////////////////////////////////////////////////////////////////////
// 4.1 Pairs ����
void f()
{
	std::pair<int, const char*> p(40, "hello");
	std::pair<int, const char*> p_2(p);			// OK: calls built-in default copy constructor
	std::pair<int, std::string> p_3(p);			// OK: calls template constructor
	cout << p_2.first << " " << p_2.second << endl;
	cout << p_3.first << " " << p_3.second << endl;

	std::pair<int, float> p_5(2, 2.0f);
	std::pair<int, float> p_6(1, 2.1f);
	// �������Ϊ true
	std::cout << std::boolalpha << (p_5 > p_6) << std::endl;	// ���� pair �Ƚϴ�Сʱ����һԪ�ؾ��нϸ����ȼ��������Ȳ�ȥ�Ƚϵڶ�Ԫ�ء�
}

//////////////////////////////////////////////////////////////////////////
// 4.2 Class auto_ptr 
// deprecated in C++11 and removed in C++17

//////////////////////////////////////////////////////////////////////////
// 4.3 ��ֵ���� Numeric Limits
void f2()
{
	using std::cout;
	using std::endl;
	using std::numeric_limits;
	using std::boolalpha;

	// numeric_limits<> ʹ�÷���
	// use textual representation for bool

	cout << boolalpha;

	// print maximum of integral types
	cout << "max(short): " << numeric_limits<short>::max() << endl;
	cout << "max(int):   " << numeric_limits<int>::max() << endl;
	cout << "max(long):  " << numeric_limits<long>::max() << endl;
	cout << endl;

	// print maximum of floating-point types
	cout << "max(float):       "
		<< numeric_limits<float>::max() << endl;
	cout << "max(double):      "
		<< numeric_limits<double>::max() << endl;
	cout << "max(long double): "
		<< numeric_limits<long double>::max() << endl;
	cout << endl;

	// print whether char is signed
	cout << "is_signed(char): "
		<< numeric_limits<char>::is_signed << endl;
	cout << endl;

	// print whether numeric limits for type string exist
	cout << "is_specialized(string): "
		<< numeric_limits<string>::is_specialized << endl;
}

//////////////////////////////////////////////////////////////////////////
// 4.4 ��������
// max min swap

// min and max
// function that compares two pointers by comparing the values to which they point.
bool int_ptr_less(int *a, int *b)
{
	return *a < *b;
}

void f4()
{
	int x = 17;
	int y = 42;	
	int *px = &x;
	int *py = &y;
	int *pmax = std::max(px, py, int_ptr_less);
	std::cout << *pmax << std::endl;

	int i = 10;
	long l = 20;
//	l = std::max(i, l);		// ERROR: argument types don't match
	l = std::max<long>(i, l);
}

// swap 
// ͸�� template specialization �� function overloading������Ϊ�����ӵ��ͱ��ṩ����������汾��
// ���ǿ��Խ��������ڲ���Ա��������ʦ���ڷ�����ֵ���Ӷ�����Ч���ϵ�������
class MyContainer {
private:
	int* elems;		// dynamic array of elements
	int numElems;	// number of elements
public:
	void swap(MyContainer& X)
	{
		std::swap(elems, X.elems);
		std::swap(numElems, X.numElems);
	}
};

// overloaded global swap() for this type
inline void swap(MyContainer& c1, MyContainer& c2)
{
	c1.swap(c2);
}

//////////////////////////////////////////////////////////////////////////
// 4.5 �����Եġ��Ƚϲ�������
// ֻ�趨�� < �� == ���������Ϳ���ʹ�� !=��>��<=��>= �ĸ���������
// ֻҪ���� using namespace std::rel_ops

class X {
private:
	int data;
public:
	X(int data_) : data(data_) { }
	bool operator== (const X& x) const
	{
		return data == x.data;
	}
	bool operator<(const X& x) const
	{
		return data < x.data;
	}
};

void f5()
{
	using namespace std::rel_ops;	// make !=, >, etc., available
	X x1(2), x2(3);
	std::cout << std::boolalpha << (x1 > x2) << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 4.6 ͷ�ļ� cstddef �� cstdlib
// exit �� atexit
void f6()
{
	std::cout << "before exit" << std::endl;
}

void f7()
{
	std::atexit(&f6);			// �� exit ��ֹ����֮ǰ���ȵ��� f6
	std::cout << "f7()" << std::endl;
	std::exit(EXIT_SUCCESS);
}

}	// !CH_4_H