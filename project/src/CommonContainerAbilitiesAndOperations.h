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
// 6.1.1 �����Ĺ�ͬ����
// ע�����������ṩ�Ķ��� ��value���⡱���ǡ�reference���⡱��
// ����������Ԫ�صİ������ʱ���ڲ�ʵʩ���ǿ������������������ڡ�

void f1()
{
	int arr[] = { 1,2,3,4 };

	std::set<int> c(arr, arr + sizeof(arr) / sizeof(arr[0]));

	std::copy(c.begin(), c.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::deque<int> c2((std::istream_iterator<int>(std::cin)),	// ��Ҫ��©�˴��ġ�����ġ����ţ�
																// ������ʽ�����彫����Ȼ��ͬ��
																// �������� c2 ���ᱻ��Ϊһ������������
					   std::istream_iterator<int>());
}
}	// CH6_1
