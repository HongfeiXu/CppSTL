#pragma once
/*

chapter 6.4 Lists

Lists ʹ��һ�� doubly linked list ������Ԫ�ء�

2017.10.21

*/

#include <list>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

using namespace std;

namespace CH6_4_LISTS_H
{
//////////////////////////////////////////////////////////////////////////
// 6.4.1 Lists ������
// ��֧�������ȡ
// �κ�λ����ִ��Ԫ�صİ�����Ƴ����ܿ�
// �����ɾ������������ʹָ������Ԫ�صĸ��� pointers��references��iterators ʧЧ������

//////////////////////////////////////////////////////////////////////////
// 6.4.2 Lists �Ĳ�������

// ��������غ��� Iterator Functions
// ע�����ڲ�֧�������ȡ��lists �Ȳ��ṩ subscript ��������Ҳ���ṩ at()��
// ֻ�����õ����������ܹ���ȡ list �еĸ���Ԫ�ء�
// ���� list �ṩ�ĵ�����ֻ�� ˫������������������������
// ���Է����õ������ȡ���������㷨��������������Ԫ��˳����㷨�����ر��������㷨����������ࣩ�㶼���ܵ��á�
// ���������� list �������Ա���� sort() ���档

// Ԫ�صİ��� Inserting ���Ƴ� Removing
// ע��Lists ������ remove() �� remove_if() �㷨Ӧ�������������汾��
// ��Ҫ����ͨ�汾�� remove �㷨���졣
void f()
{
	list<int> coll { 1,1,2,3,4,5 };
//	coll.remove_if(bind2nd(modulus<int>(), 2));			// �Ƴ���������
	coll.remove_if(not1(bind2nd(modulus<int>(), 2)));	// �Ƴ�����ż��

	copy(coll.begin(), coll.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
}

// Lists ������䶯�Բ��� Special Modifying Operations
// unique splice sort merge
void f2()
{
	list<int> coll1 { 1,3,5 };
	list<int> coll2 { 2,4,6 };
	coll1.merge(coll2, less<int>());

	cout << "coll1: ";
	copy(coll1.begin(), coll1.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "coll2: ";
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	list<int> coll3 { 7,8,9 };
	coll3.splice(coll3.begin(), coll1);

	cout << "coll1: ";
	copy(coll1.begin(), coll1.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "coll3: ";
	copy(coll3.begin(), coll3.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	/*
	coll1: 1 2 3 4 5 6
	coll2:
	coll1:
	coll3: 1 2 3 4 5 6 7 8 9
	�밴���������. . .
	*/
}

//////////////////////////////////////////////////////////////////////////
// 6.4.3 �쳣����


//////////////////////////////////////////////////////////////////////////
// 6.4.4 List ����ʵ��

void printLists(const list<int>& l1, const list<int>& l2)
{
	cout << "list1: ";
	copy(l1.begin(), l1.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "list2: ";
	copy(l2.begin(), l2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
}

void f3()
{
	list<int> list1, list2;
	for (int i = 0; i != 6; ++i)
	{
		list1.push_back(i);
		list2.push_front(i);
	}
	printLists(list1, list2);

	// insert all elements of list1 before the first element with value 3 of the list2
	list2.splice(find(list2.begin(), list2.end(), 3), 
				 list1);
	printLists(list1, list2);

	// move first element to the end
	list2.splice(list2.end(),		// destination position
				 list2,				// source list
				 list2.begin());	// source position
	printLists(list1, list2);
	
	// sort second list, assign to list1 and remove duplicates
	list2.sort();
	list1 = list2;
	list2.unique();
	printLists(list1, list2);

	// merge both sorted lists into the first list
	list1.merge(list2);
	printLists(list1, list2);

	/*
	list1: 0 1 2 3 4 5
	list2: 5 4 3 2 1 0
	list1:
	list2: 5 4 0 1 2 3 4 5 3 2 1 0
	list1:
	list2: 4 0 1 2 3 4 5 3 2 1 0 5
	list1: 0 0 1 1 2 2 3 3 4 4 5 5
	list2: 0 1 2 3 4 5
	list1: 0 0 0 1 1 1 2 2 2 3 3 3 4 4 4 5 5 5
	list2:
	�밴���������. . .
	*/
}

} // !CH6_4_LISTS_H
