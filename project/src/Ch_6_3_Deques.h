#pragma once
/*

chapter 6.3 Deques

Deques Ҳ���ö�̬����������Ԫ�أ��ṩ�����ȡ�������ź� vector ����һģһ���Ľӿڡ�
��ͬ���� deque �Ķ�̬����ͷβ�����ţ������ͷβ���˽��п��ٰ����ɾ����
Ϊ�˻�ȡ���������� deque ͨ����Ϊһ��������飬��һ���鳯��ĳ������չ�����һ�����鳯����һ������չ��

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
// 6.3.1 Deques ������

//////////////////////////////////////////////////////////////////////////
// 6.3.2 Deques �Ĳ�������

//////////////////////////////////////////////////////////////////////////
// 6.3.3 �쳣����

//////////////////////////////////////////////////////////////////////////
// 6.3.4 Deques ����ʵ��

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

	�밴���������. . .
	*/
}

} // !CH6_3_DEQUES_H
