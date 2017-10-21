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
// 6.2.1 Vectrors ������

// ��С Size ������ Capacity
// size() empty() max_size()
// capacity()
// reserve()
// ע�� vectors ���������������� strings ���ơ�������һ����ͬ�㣺 vector ������ reserve() �������������� string ���ԡ�
// ������� reserve() �����Ĳ����ȵ�ǰ vector ������ capacity ��С�����������κη�Ӧ��

// ������һ��������� vector ������С���š�ע�⣬���� vectors �������ݺ����ߵ�����Ҳ�ụ����
// ע������ shrikCapacity() ��ʹ���� reference��pointers��iterators ʧЧ��
template<class T>
void shrinkCapacity(std::vector<T>& v)
{
	std::vector<T> tmp(v);
	v.swap(tmp);
}
// ע�� C++11 �������� std::vector::shrink_to_fit �������������δ��ʹ�õĿռ�

//////////////////////////////////////////////////////////////////////////
// 6.2.2 Vector �Ĳ�������

// ���졢����������

// ��ֵ

// Ԫ�ش�ȡ
void f()
{
	std::vector<int> coll;
	try
	{
		coll.at(4) = 0;		// ��� 4 Խ�磬���׳� out_of_range
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}

	/*
	invalid vector<T> subscript
	�밴���������. . .
	*/
}

// ������Ƴ�

// �Ƴ�����ĳֵ��ȡ�������Ԫ��
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
// �Ƴ�����ĳֵ��ȡ��ĵ�һ��Ԫ��
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
// 6.2.3 �� Vectors ����һ�� Arrays ʹ��
void f4()
{
	std::vector<char> v;
	v.resize(41);
	std::strcpy(&v[0], "hello world");
	std::printf("%s\n", &v[0]);
}

//////////////////////////////////////////////////////////////////////////
// 6.2.4 �쳣���� Exception Handling
// vector ֻ֧������޶ȵ��߼������顣subscript �������İ�ȫ�汾�� at()��


//////////////////////////////////////////////////////////////////////////
// 6.2.5 Vectors ����ʵ��
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
