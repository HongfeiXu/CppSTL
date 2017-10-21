#pragma once
/*

chapter 6.1 �����Ĺ�ͬ�����͹�ͨ����

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
// 1. ���������ṩ�Ķ��� ��value���⡱���ǡ�reference���⡱��
// ע�� ����������Ԫ�صİ������ʱ���ڲ�ʵʩ���ǿ������������������ڡ�
// 2. ������ԣ�����Ԫ���γ�һ������
// 3. һ����ԣ�����������Ǿ��԰�ȫ�������߱���ȷ���������������Ĳ�������Ҫ��

//////////////////////////////////////////////////////////////////////////
// 6.1.2 �����Ĺ�ͨ����

// ��ʼ�� initialization
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
// ���С��صĲ������� Size Operations

// �Ƚ� Comparisons

// ��ֵ Assignments �� swap()
// ע�������ĸ�ֵ�������۱Ƚϸ߰���������������ͱ���ͬ���ҿ�����Դ�������ڱ�ʹ�ã���ô���ǿ���ʹ��һ���򵥵��Ż�������swap()��


}	// CH6_1
