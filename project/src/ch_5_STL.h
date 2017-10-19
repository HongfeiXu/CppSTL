#pragma once

/*

chapter 5 Standard Template Library

STL �ṩ���ڴ������ݵ��������㷨��������ϸ���� STL �ĸ�����𲽽������еĸ�����⡢�����̼������Լ����������ݵĽ�ɫ��

2017 10.17

*/
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <functional>		// to use std::greater
#include <algorithm>
#include <iterator>
#include <cstdlib>			// stdLLabs()
#include <string>

#include "Utility.h"

namespace CH_5_STL_H
{

//////////////////////////////////////////////////////////////////////////
// 5.2 ���� Containers
// 1. ����ʽ���� Sequence containers�����˿���(ordered)Ⱥ������ÿ��Ԫ�ؾ��й̶���λ�á���ȡ���ڲ���ʱ���͵ص㣬��Ԫ��ֵ�޹ء�
// vector deque list
// 2. ����ʽ���� Associative containers����������(sorted)Ⱥ����Ԫ��λ��ȡ�����ض����������
// set multiset map multimap

// 5.2.1 ����ʽ���� Sequence Containers
// Vectors Deques Lists
// ����Ҳ�ɽ� strings  �� array ����һ������ʽ������
// vector
// dequeue (double-ended queue)
// list ����˫������ʵ�����ɣ�
void f()
{
	std::vector<int> vi;
	for (int i = 1; i <= 6; i++)
	{
		vi.push_back(i);
	}
	for (int i = 0; i < static_cast<int>(vi.size()); ++i)
	{
		std::cout << vi[i] << " ";
	}
	std::cout << std::endl;

	std::deque<float> df;
	for (int i = 1; i <= 6; i++)
	{
		df.push_front(i * 1.1f);
	}
	for (int i = 0; i < static_cast<int>(df.size()); ++i)
	{
		std::cout << df[i] << " ";
	}
	std::cout << std::endl;

	std::list<char> lc;
	for (char c = 'a'; c <= 'z'; ++c)
	{
		lc.push_back(c);
	}
	while (!lc.empty())
	{
		std::cout << lc.front() << ' ';
		lc.pop_front();
	}
	std::cout << std::endl;
}

// 5.2.2 ����ʽ���� Associative Containers
// set multiset map multimap

// 5.2.3 ���������� Container Adapters
// Stacks Queues Priority Queues

void f2()
{
	std::list<char> lc;
	for (char c = 'a'; c <= 'z'; ++c)
	{
		lc.push_back(c);
	}

	std::list<char>::const_iterator pos;		// pos ��ֻ��ģʽ����Ԫ��
	for (pos = lc.begin(); pos != lc.end(); pos++)
	{
		std::cout << *pos << ' ';
	}
	std::cout << std::endl;
}

// 5.3 ������

// 5.3.1 ����ʽ����������ʵ��
// set and multiset
void f3()	// չʾ����� set ֮�а���Ԫ�أ���ʹ�õ���������ӡ����
{
	typedef std::set<int> IntSet;	// ȱʡ������׼���� operator< Ϊ���ݣ���Ԫ�ؽ�������
	typedef std::set<int, std::greater<int>> IntSetDescend;	// �ݼ���ʽ����
	typedef std::multiset<int> IntMultiSet;

	IntSet coll;
	coll.insert(3);
	coll.insert(1);
	coll.insert(5);
	coll.insert(4);
	coll.insert(1);
	coll.insert(6);
	coll.insert(2);

	IntMultiSet::const_iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos)
	{
		std::cout << *pos << ' ';
	}
	std::cout << std::endl;
}

// multimap
void f4()
{
	typedef multimap<int, string> IntStringMMap;

	IntStringMMap coll;		// container for int/string values
	coll.insert(make_pair(5, "tagged"));
	coll.insert(make_pair(2, "a"));
	coll.insert(make_pair(1, "this"));
	coll.insert(make_pair(4, "of"));
	coll.insert(make_pair(6, "strings"));
	coll.insert(make_pair(1, "is"));
	coll.insert(make_pair(3, "multimap"));

	IntStringMMap::const_iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos)
	{
		std::cout << pos->second << ' ';
	}
	std::cout << std::endl;
}
// map
// �� Maps ��������ʽ���� associative arrays����ν����ʽ������ǣ��������Բ����κ��ͱ�
void f5()
{
	typedef map<string, float> StringFloatMap;
	StringFloatMap coll;
	coll["VAT"] = 0.15f;
	coll["Pi"] = 3.1415f;
	coll["an arbitrary number"] = 4983.223f;
	coll["NULL"] = 0;
	coll["an arbitrary number"] = 123;	// ��ֵ "an arbitrary number" ��Ӧ��ʵֵ����
	coll["zero"];	// ��ֵΪ "zero" ʵֵΪ 0

	StringFloatMap::const_iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos)
	{
		std::cout << "key: \"" << pos->first << "\" "
			<< "value: " << pos->second << std::endl;
	}

	/*
	
	key: "NULL" value: 0
	key: "Pi" value: 3.1415
	key: "VAT" value: 0.15
	key: "an arbitrary number" value: 123
	key: "zero" value: 0
	�밴���������. . .
	
	*/

}

// 5.3.2 ���������� Bidirectional iterator
// 1. ˫������� �Ե�������ǰ�����Եݼ��������
// list set multiset map multimap ��������
// 2. �����ȡ������ Random access iterator
// �����߱�˫����������������ԣ����߱��������������
// ���ԶԵ��������ӻ����һ��ƫ���������������֮��ľ��롢����ʹ�� < �� > ֮�����Թ�ϵ���������Ƚ�������������
// vector deque string ��������
// ע��Ϊ��׫д����������������޹صķ��ͳ�����룬��ò�Ҫʹ�������ȡ�����������в������磺
/*
for (pos = coll.begin(); pos != coll.end(); ++pos)
{
	...	
}

for (pos = coll.begin(); pos < coll.end(); ++pos)
{
	...		// ���� list set map �޷�����
}
*/

//////////////////////////////////////////////////////////////////////////
// 5.4 �㷨
// a simple example
void f6()
{
	std::vector<int> coll;
	std::vector<int>::iterator pos;

	coll.push_back(2);
	coll.push_back(5);
	coll.push_back(4);
	coll.push_back(1);
	coll.push_back(6);
	coll.push_back(3);

	pos = std::min_element(coll.begin(), coll.end());
	std::cout << "min: " << *pos << std::endl;
	pos = std::max_element(coll.begin(), coll.end());
	std::cout << "max: " << *pos << std::endl;

	std::sort(coll.begin(), coll.end());
	PRINT_ELEMENTS<std::vector<int>>(coll);
	std::cout << std::endl;

	pos = std::find(coll.begin(), coll.end(),
					3);
	// reverse the order of the found element with value 3 and all following elements
	reverse(pos, coll.end());
	PRINT_ELEMENTS<std::vector<int>>(coll);
	std::cout << std::endl;
}

// 5.4.1 ���� Ranges
// ���ȷ��һ���������� list���ϵ������������ȡ��������ǰ���ϵ��
void f7()
{
	std::list<int> li;
	for (int i = 40; i >= 20; --i)
	{
		li.push_back(i);
	}

	std::list<int>::iterator pos25 = find(li.begin(), li.end(), 25);
	std::list<int>::iterator pos30 = find(li.begin(), li.end(), 30);

	// ERROR: pos25 and pos30 are not random access iterator
	//if (pos25 < pos30)
	//{
	//}

	std::list<int>::iterator pos25_v2 = find(li.begin(), li.end(), 25);
	std::list<int>::iterator pos30_v2 = find(li.begin(), pos25_v2, 30);
	if (pos30_v2 != pos25_v2)
	{
		std::cout << "[pos30_v2; pos25_v2) is valid" << std::endl;
	}
	else
	{
		pos30_v2 = find(pos25_v2, li.end(), 30);
		if (pos30_v2 != pos25_v2)
		{
			std::cout << "[pos25_v2; pos30_v2) is valid" << std::endl;
		}
		else
		{
			std::cout << "both pos25_v2 and pos30_v2 are end()" << std::endl;
		}
	}
}

// 5.4.2 ����������
void f8()
{
	std::list<int> coll1;
	std::vector<int> coll2;

	for (int i = 1; i <= 9; ++i)
	{
		coll1.push_back(i);
	}

	coll2.resize(coll1.size());

	// copy elements from first into second collection
	// overwrites existing elements in destination
	std::copy(coll1.begin(), coll1.end(), 
			  coll2.begin());

	PRINT_ELEMENTS<std::vector<int>>(coll2);
	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 5.5 ������֮����� Iterator Adapters
// 1. Insert iterators
// 2. Stream iterators
// 3. Reverse iterators

// 5.5.1 Insert iterators
// 1. Back inserters		������������β�ˣ����� push_back
// 2. Front inserters		������������ǰ�ˣ����� push_front
// 3. General inserters		һ���԰����������� insert
void f9()
{
	std::list<int> coll1;
	for (int i = 1; i <= 9; i++)
		coll1.push_back(i);

	std::vector<int> coll2;
	std::copy(coll1.begin(), coll1.end(), 
			  std::back_inserter(coll2));
	PRINT_ELEMENTS<std::vector<int>>(coll2);
	std::cout << std::endl;

	std::deque<int> coll3;
	copy(coll1.begin(), coll1.end(), 
		 std::front_inserter(coll3));
	std::for_each(coll3.begin(), coll3.end(), [](const int& i) { std::cout << i << ' '; });
	std::cout << std::endl;

	std::set<int> coll4;
	copy(coll1.begin(), coll1.end(),
		 std::inserter(coll4, coll4.begin()));
	std::for_each(coll4.begin(), coll4.end(), [](const int& i) { std::cout << i << ' '; });
	std::cout << std::endl;
}

// 5.5.2 Stream iterators ��������
//*******************************************************************
void f10()
{
	std::vector<std::string> coll;

	// read all words from the standard input
	std::copy(std::istream_iterator<std::string>(std::cin),		// ����һ�����Դӡ���׼������ cin�� ��ȡ���ݵ� stream iterator
			  std::istream_iterator<std::string>(),				// ����һ���������������� end of stream���ĵ�����
			  back_inserter(coll));

	// print all elements
	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<std::string>(std::cout, "\n"));

	// sort elements
	std::sort(coll.begin(), coll.end());

	// print all elements without duplicates
	std::unique_copy(coll.begin(), coll.end(),					// unique_copy �������ڵ��ظ�ֵ
					 std::ostream_iterator<std::string>(std::cout, "\n"));	
					// ����һ�� output stream iterator��͸�� operator<< �� cout д�� strings�� �ڶ�������ΪԪ��֮��ķָ�����
	/*
	Apple Mac Lenovo ThinkPad HP OMEN
	^Z
	Apple
	Mac
	Lenovo
	ThinkPad
	HP
	OMEN
	Apple
	HP
	Lenovo
	Mac
	OMEN
	ThinkPad
	�밴���������. . .
	*/
}

// 5.5.3 Reverse Iterators ���������
void f11()
{
	std::vector<int> coll;
	for (int i = 1; i <= 9; ++i)
	{
		coll.push_back(i);
	}

	std::copy(coll.rbegin(), coll.rend(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 5.6 �������㷨 Manipulating Algorightms
// ָ��Щ���Ƴ� remove������ resort���޸� modify Ԫ�ص��㷨

// 5.6.1 �Ƴ�Ԫ�� Removeing
void f12()
{
	std::list<int> coll;
	for (int i = 1; i <= 6; ++i)
	{
		coll.push_back(i);
		coll.push_front(i);
	}

	// print all elements of the collection
	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	// remove all elements with value 3
	// - retain new end, but not actually "remove" elements
	std::list<int>::iterator end = std::remove(coll.begin(), coll.end(),
				3);

	// print resulting elements of the collection
	std::copy(coll.begin(), end,
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	// print number of removed elements
	std::cout << "number of removed elements: "
		<< std::distance(end, coll.end()) << std::endl;

	// remove "removed" elements
	coll.erase(end, coll.end());

	// print all elements of the modified collection
	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	/*
	6 5 4 3 2 1 1 2 3 4 5 6
	6 5 4 2 1 1 2 4 5 6
	number of removed elements: 2
	6 5 4 2 1 1 2 4 5 6
	�밴���������. . .
	*/

	// one line
//	coll.erase(std::remove(coll.begin(), coll.end(), 3), coll.end());

	// ע�� list �� remove ��Ա������������ list �ṹ���е㣬���и��õ�Ч��
//	coll.remove(3);
}

// 5.6.2 �������㷨�͹���ʽ����
// �������㷨���ܰѹ���������������Ŀ�ꡣ��Ϊ������������㷨���ڹ��������ϣ�
// ��ı�ĳλ���ϵ�ֵ�������ƻ�������sorted�����ԣ�
// �Ǿ��Ʒ��˹��������Ļ���ԭ�������ڵ�Ԫ�����Ǹ���ĳ������׼���Զ�����
// ��ˣ�Ϊ�˱�֤���ԭ�򣬹��������ϵ����е�������������Ϊָ����������������

void f13() // ��δӹ���������ɾ��Ԫ��
{
	std::set<int> coll;

	for (int i = 1; i <= 9; ++i)
		coll.insert(i);

	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::size_t num = coll.erase(3);

	std::cout << "number of removed elements: " << num << std::endl;

	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

// 5.6.3 �㷨 vs ��Ա����
// ע���������Ǹ�����������������ʹ��ĳ���㷨����Ҳδ�غá����������ṩ�������ƶ����ܸ��õĳ�Ա������
// �� remove �� list.remove
// ������
void f14()
{
	std::list<int> coll;
	for (int i = 1; i <= 6; ++i)
	{
		coll.push_back(i);
		coll.push_front(i);
	}

	// remove all elements with value 3
	// - poor performance
	coll.erase(std::remove(coll.begin(), coll.end(),
			   3),
			   coll.end());

	// remove all elements with value 4
	// - good performance
	coll.remove(4);

	std::copy(coll.begin(), coll.end(),
			  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 5.7 ʹ�����Զ���֮���ͺ��� User-Defined Generic Functions

//template <class T>
//inline void PRINT_ELEMENTS(const T& coll, const char* optcstr = "")
//{
//	typename T::const_iterator pos;
//	std::cout << optcstr;
//	for (pos = coll.begin(); pos != coll.end(); ++pos)
//	{
//		std::cout << *pos << ' ';
//	}
//	std::cout << std::endl;
//}

//////////////////////////////////////////////////////////////////////////
// 5.8 �Ժ�����Ϊ�㷨�Ĳ���

// 5.8.1 ���Ժ�����Ϊ�㷨�Ĳ����� ʵ��ʾ��
// for_each
void f15()
{
	std::vector<int> coll;
	for (int i = 1; i <= 9; ++i)
	{
		coll.push_back(i);
	}
	std::for_each(coll.begin(), coll.end(), [](const int& i) { std::cout << i << ' '; });
	std::cout << std::endl; 
}
// transform
// coll1->transform->coll2
void f16()
{
	std::set<int> coll1;
	std::vector<int> coll2;

	for (int i = 1; i <= 9; ++i)
		coll1.insert(i);
	std::cout << "initialized: ";
	PRINT_ELEMENTS(coll1, ' ');
	std::cout << std::endl;

	// transform each element from coll1 to coll2
	std::transform(coll1.begin(), coll1.end(),
				   back_inserter(coll2),
				   [](const int & elem) { return elem * elem; });

	std::cout << "squared: ";
	PRINT_ELEMENTS(coll2, ' ');
	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// 5.8.2 �ж�ʽ Predicates

// Unary Predicates һԪ�ж�ʽ
// ������;�Ǽ��Ψһ������ĳ������
// ���� isPrime Ϊ Unary Predicates������Ϊ find_if �Ĳ���
bool isPrime(int number)
{
	// ignore negative sign
	number = std::abs(number);

	// 0 and 1 are prime number
	if (number == 0 || number == 1)
		return true;

	// find divisor that divides without a remainder
	int divisor = 0;
	for (divisor = number / 2; number % divisor != 0; --divisor)
		;

	// if no divisor greater than 1 is found, it is a prime number
	return divisor == 1;
}
void f17()
{
	std::list<int> coll;
	
	for (int i = 24; i <= 30; ++i)
		coll.push_back(i);

	list<int>::const_iterator pos;
	pos = std::find_if(coll.begin(), coll.end(),	// range
					   isPrime);					// unary predicate
	if (pos != coll.end())
		std::cout << *pos << " is first prime number found" << std::endl;
	else
		std::cout << "no prime number found" << std::endl;
}

// Binary Predicates ��Ԫ�ж�ʽ
// ������;�ǱȽ������������ض�����

class Person {
private:
	std::string firstname;
	std::string lastname;
public:
	Person() : firstname(), lastname() { }
	Person(std::string firstname_, std::string secondname_ )
		: firstname(firstname_), lastname(secondname_)
	{ }
	void PrintName()
	{
		std::cout << firstname << " " << lastname << std::endl;
	}
	std::string GetFirstname() const
	{
		return firstname;
	}
	std::string GetLastname() const
	{
		return lastname;
	}
};

// binary predicate:
// - returns whether a person is less than another person
bool personSortCriterion(const Person& p1, const Person& p2)
{
	return(p1.GetLastname() < p2.GetLastname() ||
		   (!(p2.GetLastname() < p1.GetLastname())) &&
		   p1.GetFirstname() < p2.GetFirstname());
}

void f18()
{
	std::deque<Person> coll;
	Person p1("Lebron", "James");
	Person p2("Kobe", "Bryant");
	Person p3("Ice", "MJ");
	coll.push_back(p1);
	coll.push_back(p2);
	coll.push_back(p3);

	std::cout << "pre: " << std::endl;
	std::for_each(coll.begin(), coll.end(),
				  [](const Person& person) { std::cout << person.GetFirstname() << " " << person.GetLastname() << std::endl; });

	std::sort(coll.begin(), coll.end(),			// range
			  personSortCriterion);				// sort criterion

	std::cout << "post: " << std::endl;
	std::for_each(coll.begin(), coll.end(),
				  [](const Person& person) { std::cout << person.GetFirstname() << " " << person.GetLastname() << std::endl; });
}

//////////////////////////////////////////////////////////////////////////
// 5.9 �º��� Functors, Function Objects

// 5.9.1 ʲô�Ƿº���
// ʲô�Ƿº������κζ�����ֻҪ��Ϊ�����������Ǹ��������������㶨����һ��������Ϊ���������Ϳ��Ա�����������ʹ�á�
// ��ôʲô�����Ǿ߱�������Ϊ����ν������Ϊ����ָ���ԡ�ʹ��С���Ŵ��ݲ��������Ե���ĳ����������
// ֻ�������ж��� operator()����������ʵĲ����ͱ�

// Functor
class PrintInt {
public:
	void operator() (int elem) const
	{
		std::cout << elem << " ";
	}
};

void print(int elem)
{
	std::cout << elem << ' ';
}

void f19()
{
	std::vector<int> coll;
	for (int i = 1; i <= 9; ++i)
		coll.push_back(i);
	//std::for_each(coll.begin(), coll.end(), print);	// �Ժ�����Ϊ�㷨�Ĳ���
	std::for_each(coll.begin(), coll.end(), PrintInt());// �Էº�����Ϊ�㷨�Ĳ�����
														// ���� PrintInt() ������������һ����ʱ���󣬵��� for_each() �㷨��һ��������
	std::cout << std::endl;
}

// �º����ŵ�
// 1. �º����� "smart functions"��
// �º�����ӵ�г�Ա�����ͳ�Ա����������ζ����ӵ��״̬�����⣬�������ִ����(runtime)��ʼ�����ǡ�
// 2. ÿ���º��������Լ����ͱ�
// 3. �º���ͨ����һ�㺯���ٶȿ�

template <int theValue>
void add(int &elem)		// ���� template ���ԣ�����ϸ���ڱ����ھ��Ѿ�ȷ��
{
	elem += theValue;
}

void f20()
{
	std::vector<int> coll;
	for (int i = 1; i <= 9; ++i)
		coll.push_back(i);
	std::for_each(coll.begin(), coll.end(), 
				  add<10>);
	//std::for_each(coll.begin(), coll.end(),	// ERROR
	//			  add<coll.front()>);			// ģ�����Ӧ��Ϊ����ʱ�������ʽ��������ʱ�Ѿ�ȷ����ֵ�������ֵ������ʱȷ��
	PRINT_ELEMENTS(coll, ' ');
	std::cout << std::endl;
}
// Functor
class AddValue {
private:
	int theValue = 0;
public:
	AddValue(int theValue_) : theValue(theValue_) { }
	void operator() (int& elem)
	{
		elem += theValue;
	}
};

void f21()
{
	std::vector<int> coll;
	for (int i = 1; i <= 9; ++i)
		coll.push_back(i);
	std::for_each(coll.begin(), coll.end(),
				  AddValue(10));				// AddValue(10) ����һ�� AddValue ��������� 10 Ϊ��ֵ��
	PRINT_ELEMENTS(coll, ' ');
	std::cout << std::endl;

	std::for_each(coll.begin(), coll.end(),
				  AddValue(coll.front()));		// �º����ĳ�Ա����������ִ������ʼ�������һ�㺯������������
												// AddValue(coll.front()) ����һ�� AddValue ��������� coll.front() Ϊ��ֵ
	PRINT_ELEMENTS(coll, ' ');
	std::cout << std::endl;

	/*
	11 12 13 14 15 16 17 18 19
	22 23 24 25 26 27 28 29 30
	�밴���������. . .
	*/
}

//////////////////////////////////////////////////////////////////////////
// 5.9.2 Ԥ�ȶ���ķº���
// less<> greater<> negate<> multplies<> equal_to<>
void f22()
{
	std::vector<int> coll { 1,2,3,4,5 };
	std::transform(coll.begin(), coll.end(),	// source
				   coll.begin(),				// destination
				   std::negate <int>());		// operation
	PRINT_ELEMENTS(coll, ' ');
	std::cout << std::endl;
	std::transform(coll.begin(), coll.end(),	// first source
				   coll.begin(),				// second source
				   coll.begin(),				// destination
				   std::multiplies<int>());		// operation
	PRINT_ELEMENTS(coll, ' ');
	std::cout << std::endl;
}

// ͸��һЩ����ĺ��������� function adaptors ������Խ�Ԥ�ȶ���ķº�����������ֵ�����һ�𣬻�ʹ������״��
// std::bind2nd 
// (deprecated in C++11) 
// (removed in C++17)
void f23()
{
	std::set<int, std::greater<int>> coll1;
	std::deque<int> coll2;

	for (int i = 1; i <= 9; ++i)
		coll1.insert(i);

	PRINT_ELEMENTS(coll1, ' ');
	std::cout << std::endl;

	// transform all elements into coll2 by multiplying 10
	std::transform(coll1.begin(), coll1.end(),					// source
				   back_inserter(coll2),						// destination
				   std::bind2nd(std::multiplies<int>(), 10));	// operation
					// ����ʹ�������� bind2nd������ multiplies<int> ����ʱ��
					// ��ԴȺ����Ԫ����Ϊ��һ������10 ��Ϊ�ڶ�������

	PRINT_ELEMENTS(coll2, ' ');
	std::cout << std::endl;

	// replace value equal to 70 with 42
	std::replace_if(coll2.begin(), coll2.end(),					// range
					std::bind2nd(std::equal_to<int>(), 70),		// range criterion
					42);										// new value

	PRINT_ELEMENTS(coll2, ' ');
	std::cout << std::endl;

	// remove all elements with values less than 50
	coll2.erase(std::remove_if(coll2.begin(), coll2.end(),		// range
				std::bind2nd(std::less<int>(), 50)),			// range criterion
				coll2.end());

	PRINT_ELEMENTS(coll2, ' ');
	std::cout << std::endl;
}

// std::mem_fun_ref ���������������õ�Ԫ�ص�ĳ����Ա����
// (deprecated in C++11)
// (removed in C++17)
void f24()
{
	std::vector<Person> coll;
	Person p1("Lebron", "James");
	Person p2("Kobe", "Bryant");
	Person p3("Ice", "MJ");
	coll.push_back(p1);
	coll.push_back(p2);
	coll.push_back(p3);

	for_each(coll.begin(), coll.end(),				// range
			 std::mem_fun_ref(&Person::PrintName));	// operation
}

//////////////////////////////////////////////////////////////////////////
// 5.10 �����ڵ�Ԫ��

//////////////////////////////////////////////////////////////////////////
// 5.11 STL �ڲ��Ĵ�������쳣����

// ��ջշת���⣺http://www.geeksforgeeks.org/stack-unwinding-in-c/

//////////////////////////////////////////////////////////////////////////
// 5.12 ��չ STL

}