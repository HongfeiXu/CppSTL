#pragma once

/*

chapter 4 通用工具 Utilities

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
// 4.1 Pairs 对组
void f()
{
	std::pair<int, const char*> p(40, "hello");
	std::pair<int, const char*> p_2(p);			// OK: calls built-in default copy constructor
	std::pair<int, std::string> p_3(p);			// OK: calls template constructor
	cout << p_2.first << " " << p_2.second << endl;
	cout << p_3.first << " " << p_3.second << endl;

	std::pair<int, float> p_5(2, 2.0f);
	std::pair<int, float> p_6(1, 2.1f);
	// 这里输出为 true
	std::cout << std::boolalpha << (p_5 > p_6) << std::endl;	// 两个 pair 比较大小时，第一元素具有较高优先级。如果相等才去比较第二元素。
}

//////////////////////////////////////////////////////////////////////////
// 4.2 Class auto_ptr 
// deprecated in C++11 and removed in C++17

//////////////////////////////////////////////////////////////////////////
// 4.3 数值极限 Numeric Limits
void f2()
{
	using std::cout;
	using std::endl;
	using std::numeric_limits;
	using std::boolalpha;

	// numeric_limits<> 使用范例
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
// 4.4 辅助函数
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
// 透过 template specialization 或 function overloading，可以为更复杂的型别提供特殊的视作版本；
// 我们可以交换对象内部成员，不必劳师动众反复赋值。从而带来效率上的提升。
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
// 4.5 辅助性的“比较操作符”
// 只需定义 < 和 == 操作符，就可以使用 !=，>，<=，>= 四个操作符。
// 只要加上 using namespace std::rel_ops

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
// 4.6 头文件 cstddef 和 cstdlib
// exit 和 atexit
void f6()
{
	std::cout << "before exit" << std::endl;
}

void f7()
{
	std::atexit(&f6);			// 在 exit 终止程序之前会先调用 f6
	std::cout << "f7()" << std::endl;
	std::exit(EXIT_SUCCESS);
}

}	// !CH_4_H