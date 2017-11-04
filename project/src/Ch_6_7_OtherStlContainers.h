#pragma once
/*

chapter 6.7 ���� STL ����

STL �Ǹ���ܣ������ṩ��׼��������Ҳ������ʹ������������Ϊ�����������ʹ���ַ�����������Ϊ STL ������Ҳ��������׫д����������������������
�����������������STL���������ֲ�ͬ��ʽ��
1. The invasive approach ����ʽ��ֱ���ṩ STL ��������ӿڡ����� begin() �� end() ֮��ĳ��ú�����
2. The noninvasive approach ������ʽ��׫д���ṩ�������������Ϊ�㷨����������֮��Ľ��档
3. The wrapper approach ��װ����дһ���������wrapper class������װ�κ����ݽṹ������ʾ���� STL �������ƵĽӿڡ�

2017.10.29

*/

#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

namespace CH_6_7_H
{
//////////////////////////////////////////////////////////////////////////
// 6.7.1 Strings �ɱ���Ϊһ�� STL ����

// C++ ��׼������е� string ����ǡ���������������дSTL��������һ�������ӡ�Strings �ɱ���Ϊ���ַ�ΪԪ�ص�һ��������
// Strings �ṩ�˳�Ա���� begin() �� end()��ͬʱ֧�ֵ������͵������������strings Ҳ�ṩ��һЩ������������ push_back() ����֧�� back inserters.

//////////////////////////////////////////////////////////////////////////
// 6.7.2 Arrays �ɱ���Ϊһ�� STL ����

// array ����������Բ��ṩ begin() �� end() �ȳ�Ա������Ҳ����������κγ�Ա�������������ֻ�ܲ��÷��������������װ����

// ֱ����������
// ע��ǧ��ע�⣬Ҫ��ȷ��������β��λ�ã������� coll+6��
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
