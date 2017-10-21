#pragma once
/*

chapter 6.5 Sets �� Multisets

set �� multiset ������ض�������׼���Զ���Ԫ������
ֻҪ�� assignable��copyable��comparable ���ͱ𣬶����Գ�Ϊ set �� multiset ��Ԫ���ͱ�
���û�д����ر������׼�򣬾Ͳ���ȱʡ׼�� less��
��ν����׼�򣬱��붨�� strict weak ordering�����������£�
1. �����ǡ����ԳƵ� antisymmetric��
2. �����ǡ��ɴ��ݵ� transitive��
3. �����ǡ����Է��� irreflexive��

������Щ���ԣ�����׼��Ҳ������������Լ��飬���������Ԫ�ض���С�ڶԷ�������˵ op(x,y) �� op(y,x) ��Ϊ�٣���������Ԫ����ȡ�

2017.10.21

*/

#include <set>
#include <functional>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "Utility.h"

using namespace std;

namespace CH6_5_SETS_H
{
//////////////////////////////////////////////////////////////////////////
// 6.5.1 Sets �� Multisets ������

// sets �� multisets ͨ����ƽ���������ɡ�
// �Զ��������Ҫ�ŵ�����ʹ��������ѰԪ��ʱ���������ܡ��������㷨���ж������Ӷȡ�
// ���ǣ��Զ�������� set �� multiset ��һ����Ҫ���ƣ��㲻��ֱ�Ӹı�Ԫ��ֵ�����������ԭ����ȷ��˳��
// ���Ҫ�ı�Ԫ��ֵ��������ɾ����Ԫ�أ��ڲ�����Ԫ�ء�


//////////////////////////////////////////////////////////////////////////
// 6.5.2 Sets �� Multisets �Ĳ�������
// �����ַ�ʽ���Զ�������׼��
// 1. �� template ��������֮����������£�����׼������ͱ��һ���֡����磺 std::set<int, std::greater<int>> coll;
// 2. �Թ��캯����������֮����������£�ͬһ�ͱ�������ò�ͬ������׼�򣬶�����׼��ĳ�ʼֵ��״̬Ҳ���Բ�ͬ��
// ���ִ�����Ż������׼�򣬶�����Ҫ�õ���ͬ������׼�򣨵������ͱ������ͬ�����˷�ʽ���������ó���

// �Ǳ䶯�Բ��� Nonmodifying Operations
// ������ѯ��С���໥�Ƚ�
// ע��Ԫ�رȽ϶���ֻ�������ͱ���ͬ�����������������������
void f()
{
	set<float> c1 { 2,1,6,3};
	set<float, greater<float>> c2 { 5,1,0,2 };
	//if (c1 == c2)	// ERROR: different types
	//{

	//}
	
	copy(c1.begin(), c1.end(),
		 ostream_iterator<float>(cout, " "));
	cout << endl;

	copy(c2.begin(), c2.end(),
		 ostream_iterator<float>(cout, " "));
	cout << endl;
	
	/*
	1 2 3 6
	5 2 1 0
	�밴���������. . .
	*/
}

// �������Ѱ���� Special Search Operations
// set �� multiset �ṩ���������Ѱ��������Щ��������ͬ���� STL �㷨������汾��
// ���Ŷ���ʱ�临�Ӷȡ�
// count find lower_bound upper_bound equal_range

void f2()
{
	set<int> c;

	c.insert(1);
	c.insert(2);
	c.insert(4);
	c.insert(5);
	c.insert(6);

	cout << "lower_bound(3): " << *c.lower_bound(3) << endl;
	cout << "upper_bound(3): " << *c.upper_bound(3) << endl;
	cout << "equal_range(3): " << *c.equal_range(3).first << " "
		<< *c.equal_range(3).second << endl;

	cout << endl;
	cout << "lower_bound(5): " << *c.lower_bound(5) << endl;
	cout << "upper_bound(5): " << *c.upper_bound(5) << endl;
	cout << "equal_range(5): " << *c.equal_range(5).first << " "
		<< *c.equal_range(5).second << endl;

	/*
	lower_bound(3): 4
	upper_bound(3): 4
	equal_range(3): 4 4

	lower_bound(5): 5
	upper_bound(5): 6
	equal_range(5): 5 6
	�밴���������. . .
	*/
}

// ��ֵ Assignments 

// ��������غ��� Iterator Functions
// ע�����������й����������ƣ�����ĵ�������˫������������ԣ��޷�ʹ����Щֻ�����������ȡ�������� STL �㷨��
// ����Ҫ���ǣ����ڵ��������ԣ�����Ԫ�ض�����Ϊ���죬���ȷ���㲻����Ϊ�ı�Ԫ��ֵ���Ӷ����Ҽȶ�˳��
// �����㲻�ܶ����ǵ��� remove()����Ϊ remove() ʵ��������һ������ֵ���Ǳ��Ƴ���Ԫ�ء�
// ���Ҫ�Ƴ�Ԫ�أ���ֻ��ʹ�� set �� multiset ���ṩ�ĳ�Ա������

// Ԫ�صİ��� Inserting ���Ƴ� Removing
// insert erase clear
// ע��������Ƴ����Ԫ��ʱ����һ���ã�һ�δ����ȶ�ε��ã���һ������ܶࡣ
// ע�����庯���ķ���ֵ�ͱ𲻾���ͬ��
// ע������ӵ�У���λ����ʾ�������İ��庯�����䷵��ֵ�ͱ�һ���������� set ���� multiset����ֻ����һ����������
// http://en.cppreference.com/w/cpp/container/set/insert
// http://en.cppreference.com/w/cpp/container/multiset/insert

void f3()
{
	set<double> c;
	if (c.insert(3.3).second)
		cout << "3.3 inserted" << endl;
	else
		cout << "3.3 already exists" << endl;
}

// ��� multisets �ں��ظ�Ԫ�أ��㲻��ֱ��ʹ�� erase ��ɾ����Щ�ظ�Ԫ���еĵ�һ�������Բ�������������
void f4()
{
	typedef multiset<int> MSetInt;
	MSetInt coll { 2,1,1,1,3,4 };
	MSetInt::const_iterator pos = coll.find(1);
	if (pos != coll.cend())
		coll.erase(pos);
	copy(coll.begin(), coll.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	/*
	1 1 2 3 4
	�밴���������. . .
	*/
}


//////////////////////////////////////////////////////////////////////////
// 6.5.3 �쳣���� Exception Handling

//////////////////////////////////////////////////////////////////////////
// 6.5.4 Sets �� Multisets ����ʵ��

void f5()
{
	// type of the collecion: sets
	// - no duplicates
	// - elements are integral values
	// - descending order
	typedef set<int, greater<int>> IntSet;
	IntSet coll1;

	// insert elements in random order
	coll1.insert(4);
	coll1.insert(3);
	coll1.insert(5);
	coll1.insert(1);
	coll1.insert(6);
	coll1.insert(2);
	coll1.insert(5);

	// iterator voer all elements and print them
	IntSet::const_iterator pos;
	for (pos = coll1.begin(); pos != coll1.end(); ++pos)
	{
		cout << *pos << " ";
	}
	cout << endl;

	// insert 4 again and process return value
	pair<IntSet::iterator, bool> status = coll1.insert(4);
	if (status.second)
	{
		cout << "4 inserted as element "
			<< distance(coll1.begin(), status.first) + 1
			<< endl;
	}
	else
	{
		cout << "4 already exists" << endl;
	}

	// assign elements to another set with ascneding order
	set<int> coll2(coll1.begin(), coll1.end());

	// print all elements of the copy
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	// remove all elements up to element with value 3
	coll2.erase(coll2.begin(), coll2.find(3));

	// print all elements
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
	
	// remove all elements with value 5
	size_t num = 0;
	num = coll2.erase(5);
	cout << num << " element(s) removed" << endl;

	// print all elements
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
	/*
	6 5 4 3 2 1
	4 already exists
	1 2 3 4 5 6
	3 4 5 6
	1 element(s) removed
	3 4 6
	�밴���������. . .
	*/
}

void f6()
{
	// type of the collecion: sets
	// - no duplicates
	// - elements are integral values
	// - descending order
	typedef multiset<int, greater<int>> MIntSet;
	MIntSet coll1;

	// insert elements in random order
	coll1.insert(4);
	coll1.insert(3);
	coll1.insert(5);
	coll1.insert(1);
	coll1.insert(6);
	coll1.insert(2);
	coll1.insert(5);

	// iterator voer all elements and print them
	MIntSet::const_iterator pos;
	for (pos = coll1.begin(); pos != coll1.end(); ++pos)
	{
		cout << *pos << " ";
	}
	cout << endl;

	// insert 4 again and process return value
	MIntSet::iterator insert_pos = coll1.insert(4);
	cout << "4 inserted as element "
		<< distance(coll1.begin(), insert_pos) + 1
		<< endl;

	// assign elements to another set with ascneding order
	multiset<int> coll2(coll1.begin(), coll1.end());

	// print all elements of the copy
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	// remove all elements up to element with value 3
	coll2.erase(coll2.begin(), coll2.find(3));

	// print all elements
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;

	// remove all elements with value 5
	size_t num = 0;
	num = coll2.erase(5);
	cout << num << " element(s) removed" << endl;

	// print all elements
	copy(coll2.begin(), coll2.end(),
		 ostream_iterator<int>(cout, " "));
	cout << endl;
	/*
	6 5 5 4 3 2 1
	4 inserted as element 5
	1 2 3 4 4 5 5 6
	3 4 4 5 5 6
	2 element(s) removed
	3 4 4 6
	�밴���������. . .
	*/
}

//////////////////////////////////////////////////////////////////////////
// 6.5.5 ִ�����ƶ�����׼��
// ͨ���㶼�Ὣ����׼����Ϊ�ͱ��һ���֡�����ʱ������ִ���ڴ�������׼�򣬻����������Ҫ��ͬһ�������ͱ���ò�ͬ������׼��
// ��ʱ�����Ҫһ����������������׼�򡱵������ͱ�ʹ���ܹ�ִ���ڼ䴫��ĳ��׼��
// ���·�����

// type for sorting criterion
template<class T>
class RuntimeCmp {
public:
	enum cmp_mode { normal, reverse };
private:
	cmp_mode mode;

public:
	// constructor for sorting criterion
	// - default criterion uses value normal
	RuntimeCmp(cmp_mode m = normal) : mode(m)
	{
	}

	// comoparison of elements
	bool operator() (const T& t1, const T& t2) const
	{
		return mode == normal ? t1 < t2 : t2 < t1;
	}

	bool operator==(const RuntimeCmp& rc)
	{
		return mode == rc.mode;
	}
};

// type of a set that uses this sorting criterion
typedef set<int, RuntimeCmp<int>> IntSet;

void fill(IntSet& s)
{
	s.insert(4);
	s.insert(7);
	s.insert(5);
	s.insert(1);
	s.insert(6);
	s.insert(2);
	s.insert(5);
}

void f7()
{
	// create, fill, and print set with normal element order
	// - uses default sorting criterion
	IntSet coll1;
	fill(coll1);
	cout << "coll1: ";
	PRINT_ELEMENTS(coll1, ' ');
	cout << endl;

	// create sorting criterion with reverse element order
	RuntimeCmp<int> reverse_order(RuntimeCmp<int>::reverse);

	// create, fill, and print set with reverese element order
	IntSet coll2(reverse_order);
	fill(coll2);
	cout << "coll2: ";
	PRINT_ELEMENTS(coll2, ' ');
	cout << endl;

	coll1 = coll2;		// coll1 �� coll2 ӵ����ͬ�ͱ� set<int, RuntimeCmp<int>>�� assignment ������������ֵ��Ԫ�أ�Ҳ��ֵ������׼��
	coll1.insert(3);
	cout << "coll1: ";
	PRINT_ELEMENTS(coll1, ' ');
	cout << endl;

	if (coll1.value_comp() == coll2.value_comp())
	{
		cout << "coll1 and coll2 have same sorting criterion"
			<< endl;
	}
	else
	{
		cout << "coll1 and coll2 have different sorting criterion"
			<< endl;
	}

	/*
	coll1: 1 2 4 5 6 7
	coll2: 7 6 5 4 2 1
	coll1: 7 6 5 4 3 2 1
	coll1 and coll2 have same sorting criterion
	�밴���������. . .
	*/
}

// ע������������У�RuntimeCmp<> ��һ���򵥵� template���ṩ��ִ���ڼ���������ͱ���һ������׼�򡱵ķ���������
// �� default ���캯������Ĭ��ֵ normal��������������Ҳ���Խ� RuntimeCmp<>::reverse ���ݸ����캯�������ܰ���������

} // !CH6_5_SETS_H
