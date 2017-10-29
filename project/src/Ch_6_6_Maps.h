#pragma once
/*

chapter 6.6 Maps �� Multimaps

Map �� multimap �� key/value pair ����ֵ/ʵֵ ���飩����Ԫ�أ����й���
���ǿ��Ը��� key ������׼���Զ���Ԫ������

Map �� multimap ��Ԫ���ͱ� key �� T����������һ������������
1. key/value ����߱� assignable �� copyable ���ʡ�
2. ��������׼����ԣ�key ������ comparable�ġ�

2017.10.29

*/

#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include "Utility.h"

using namespace std;


namespace CH_6_6_MAPS_H
{
//////////////////////////////////////////////////////////////////////////
// 6.6.1 Maps �� Multimaps ������

// maps/multimaps ͨ����ƽ���������ɡ�
// Maps �� multimaps ����Ԫ�ص� key �Զ���Ԫ�ؽ���������ôһ����������֪�� key ����Ѱĳ��Ԫ��ʱ�����кܺõ����ܣ�
// ��������֪ value ����ѰԪ��ʱ�����ܾͺ���⡣
// ���Զ�������һ����ʹ�� map �� multimap ��������һ����Ҫ�����ƣ��㲻����ֱ�Ӹı�Ԫ�ص� key����Ϊ����ƻ���ȷ����
// Ҫ�޸�Ԫ�ص� key����������Ƴ�ӵ�и� key ��Ԫ�أ�Ȼ�����ӵ���µ� key/value ��Ԫ�ء�

//////////////////////////////////////////////////////////////////////////
// 6.6.2 Maps �� Multimaps �Ĳ�������

// ���ɣ����ƺ�����
// �����ַ�ʽ���Զ�������׼��
// 1. �� template ��������֮����������£�����׼������ͱ��һ���֡����磺 std::map<float, std::string, std::greater<float>> coll;
// ����ͱ�ϵͳȷ����ֻ������׼����ͬ���������ܺϲ�����
// 2. �Թ��캯����������֮����������£��������һ��������׼���ͱ𡱲�Ϊ��ָ����ͬ������׼��Ҳ����˵���ͱ������������Ķ��󣨴���һ������׼�򣩵ĳ�ֵ��״̬��ͬ����
// ���ִ��ʱ�Ż������׼�򣬶�����Ҫ�õ���ͬ������׼�򣨵������ͱ������ͬ�����˷�ʽ���������ó���
// ���͵����Ӿ�����ִ����ָ����key ���ͱ�Ϊ string��������׼��

// �Ǳ䶯�Բ���
// Ԫ�رȽ϶���ֻ�������ͱ���ͬ������������֮�������� key��value������׼�򶼱�������ͬ���ͱ𣬷�����������ͱ���Ĵ���

// �������Ѱ����
// ��Ա���� find() ������Ѱ����ĳ�� key �ĵ�һ��Ԫ�أ�������һ����������ָ���λ�á�

// ��ֵ
// ע����ֵ�����������������������ͬ�ͱ𡣾��ܡ��Ƚ�׼�򡱱�������ǲ�ͬ�ģ������ͱ������ͬ��

// ������������Ԫ�ش�ȡ
// ע�����������й����������ƣ�����ĵ�������˫������������ԣ��޷�ʹ����Щֻ�����������ȡ�������� STL �㷨��
// ����Ҫ���ǣ��� map �� multimap �У�����Ԫ�ص� key ������Ϊ���������Ԫ�ص�ʵ���ͱ��� pair<const Key, T>��
// ���������Ϊ��ȷ���㲻����Ϊ���Ԫ�ص� key ���ƻ��Ѿ��źõ�Ԫ�ش���
// �����㲻�ܶ����ǵ��� remove()����Ϊ remove() ʵ��������һ������ֵ���Ǳ��Ƴ���Ԫ�ء�
// ���Ҫ�Ƴ�Ԫ�أ���ֻ��ʹ�� map �� multimap ���ṩ�ĳ�Ա������

// ע�������һ���øı���Ԫ�ص� key��ֻ��һ��·����һ����value����ͬ����Ԫ���滻����Ԫ�ء�
// ������һ������������

//template <class Cont>
//inline
//bool replace_key(Cont& c,
//				 const typename Cont::key_type& old_key,
//				 const typename Cont::key_type& new_key)
//{
//	typename Cont::iterator pos;
//	pos = c.find(old_key);
//	
//	if(pos != c.end())
//	{
//		// insert new element with value of old element
//		c.insert(typename Cont::value_type(new_key, pos->second));
//
//		// remove old element
//		c.erase(pos);
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

void f()
{
	typedef map<string, float> StringFloatMap;
	StringFloatMap coll;

	// ���ֲ�ͬ��ʽ�� value ���� map
	coll.insert(StringFloatMap::value_type("Hello", 1.0f));
	coll.insert(pair<string, float>("World", 2.0f));		// use implicit conversion
//	coll.insert(pair<const string, float>("World", 2.0f));	// use no implicit conversion
	coll.insert(make_pair("Hungry", 3.0f));

	for (StringFloatMap::iterator pos = coll.begin(); pos != coll.end(); ++pos)
		cout << pos->first << " " << pos->second << endl;

	// �ı�Ԫ�� key
	//MyLib::replace_key(coll, "World", "Witcher");

	// �ı�Ԫ�� key���������Ч����ͬ
	coll["Witcher"] = coll["World"];
	coll.erase("World");


	for (StringFloatMap::iterator pos = coll.begin(); pos != coll.end(); ++pos)
		cout << pos->first << " " << pos->second << endl;
}

void f2()
{
	// �Ƴ�ӵ��ĳ�� value ��Ԫ��
	typedef map<string, float> StringFloatMap;
	StringFloatMap coll;
	coll.insert(make_pair("Hello", 1.2f));
	coll.insert(make_pair("World", 1.3f));
	coll.insert(make_pair("Bobo", 2.2f));

	for (StringFloatMap::iterator pos = coll.begin(); pos != coll.end();)
	{
		if (pos->second == 1.3f)
			pos = coll.erase(pos);	// erase ������һԪ�ص�λ��
		else
			++pos;
	}

	for (StringFloatMap::iterator pos = coll.begin(); pos != coll.end(); ++pos)
		cout << pos->first << " " << pos->second << endl;
}

//////////////////////////////////////////////////////////////////////////
// 6.6.3 �� Maps ��Ϊ����ʽ���� Associated Arrays

// m[key] ����һ�� reference��ָ���ֵΪ key ��Ԫ�ء������Ԫ����δ���ڣ��Ͱ����Ԫ�ء�
// �ŵ㣺����͸��������Ľӿڶ��� map ������Ԫ��
// ȱ�㣺����ܻ᲻С��������Ԫ�أ�ͬʱ����ע�⣬���ְ��巽ʽ��һ��� maps ���巽ʽ��������
// ԭ������Ԫ�ر�����ʹ�� default ���캯����ʵֵ��ʼ�����������ֵ�����ֱ������� value �����ˡ�

void f3()
{
	typedef map<string, float> StringFloatMap;
	StringFloatMap coll;
	coll["Hello"] = 1.2f;	// first insert "Hello"/float(), then it assign 1.2f
	coll["World"] = 1.3f;
	coll["Bobo"] = 2.2f;

	for (StringFloatMap::iterator pos = coll.begin(); pos != coll.end(); ++pos)
		cout << pos->first << " " << pos->second << endl;
}

//////////////////////////////////////////////////////////////////////////
// 6.6.4 �쳣����
// �� sets �� multisets һ��

//////////////////////////////////////////////////////////////////////////
// 6.6.5 Maps �� Multimaps ����ʵ��

// �� Map ��������ʽ����
// ������ӽ� map ����һ������ʽ������ʹ�ã�������ӳ��Ʊ���顣Ԫ�صļ�ֵ�ǹ�Ʊ���ƣ�ʵֵ�ǹ�Ʊ�۸�
void f4()
{
	typedef map<string, float> StringFloatMap;

	StringFloatMap stocks;

	stocks["BASF"] = 369.50f;
	stocks["VW"] = 413.50f;
	stocks["Daimler"] = 819.00f;
	stocks["BMW"] = 834.00f;
	stocks["Siemens"] = 842.20f;

	// print all elements
	for (StringFloatMap::iterator pos = stocks.begin(); pos != stocks.end(); ++pos)
		cout << "stock: " << pos->first << "\t" << "price: " << pos->second << endl;
	cout << endl;

	// all prices doubled
	for (StringFloatMap::iterator pos = stocks.begin(); pos != stocks.end(); ++pos)
		pos->second *= 2;

	// print all elements
	for (StringFloatMap::iterator pos = stocks.begin(); pos != stocks.end(); ++pos)
		cout << "stock: " << pos->first << "\t" << "price: " << pos->second << endl;
	cout << endl;

	// rename key from "VW" to "Volkswagen"
	stocks["Volkswagen"] = stocks["VW"];
	stocks.erase("VW");

	// print all elements
	for (StringFloatMap::iterator pos = stocks.begin(); pos != stocks.end(); ++pos)
		cout << "stock: " << pos->first << "\t" << "price: " << pos->second << endl;
	cout << endl;

	/*
	stock: BASF     price: 369.5
	stock: BMW      price: 834
	stock: Daimler  price: 819
	stock: Siemens  price: 842.2
	stock: VW       price: 413.5

	stock: BASF     price: 739
	stock: BMW      price: 1668
	stock: Daimler  price: 1638
	stock: Siemens  price: 1684.4
	stock: VW       price: 827

	stock: BASF     price: 739
	stock: BMW      price: 1668
	stock: Daimler  price: 1638
	stock: Siemens  price: 1684.4
	stock: Volkswagen       price: 827

	�밴���������. . .
	*/
}

// �� Multimap �����ֵ�
// �����������չʾ��ν� multimap ����һ���ֵ���ʹ��

void f5()
{
	// define multimap type as string/string dictionary
	typedef multimap<string, string> StrStrMMap;

	// create empty dictionary
	StrStrMMap dict;

	// insert some elements in random order
	dict.insert(make_pair("day", "Tag"));
	dict.insert(make_pair("strange", "fremd"));
	dict.insert(make_pair("car", "Auto"));
	dict.insert(make_pair("smart", "elegant"));
	dict.insert(make_pair("trait", "Merkmal"));
	dict.insert(make_pair("strange", "seltsam"));
	dict.insert(make_pair("smart", "raffiniert"));
	dict.insert(make_pair("smart", "klug"));
	dict.insert(make_pair("clever", "raffiniert"));

	// print all elements
	StrStrMMap::iterator pos;
	cout.setf(ios::left, ios::adjustfield);
	cout << ' ' << setw(10) << "english "
		<< "german " << endl;
	cout << setfill('-') << setw(20) << ""
		<< setfill(' ') << endl;
	for (pos = dict.begin(); pos != dict.end(); ++pos)
	{
		cout << ' ' << setw(10) << pos->first.c_str()
			<< pos->second << endl;
	}
	cout << endl;

	// print all values for key "smart"
	string word("smart");
	cout << word << ": " << endl;
	for (pos = dict.lower_bound(word); pos != dict.upper_bound(word); ++pos)
		cout << "    " << pos->second << endl;

	// print all keys for value "raffiniert"
	word = "raffiniert";
	cout << word << ": " << endl;
	for (pos = dict.begin(); pos != dict.end(); ++pos)
	{
		if (pos->second == word)
			cout << "    " << pos->first << endl;
	}

	/*
	 english   german
	--------------------
	 car       Auto
	 clever    raffiniert
	 day       Tag
	 smart     elegant
	 smart     raffiniert
	 smart     klug
	 strange   fremd
	 strange   seltsam
	 trait     Merkmal

	smart:
		elegant
		raffiniert
		klug
	raffiniert:
		clever
		smart
	�밴���������. . .
	*/
}

// ��Ѱ����ĳ�ض�ʵֵ��Ԫ��
// ��������ӻ�չʾ���ʹ��ȫ�� find_if() �㷨����Ѱ����ĳ�ض� value ��Ԫ��

// function object to check the value of a map element
template<class K, class V>
class value_equals {
private:
	V value;
public:
	value_equals(const V& v)
		:value(v)
	{ }

	bool operator()(pair<const K, V> elem)
	{
		return elem.second == value;
	}
};

void f6()
{
	typedef map<float, float> FloatFloatMap;
	FloatFloatMap coll;
	FloatFloatMap::iterator pos;

	// fill container
	coll[1] = 7;
	coll[2] = 4;
	coll[3] = 2;
	coll[4] = 3;
	coll[5] = 6;
	coll[6] = 1;
	coll[7] = 3;

	// search an element with key 3.0f
	pos = coll.find(3.0f);
	if (pos != coll.end())
		cout << pos->first << ": " << pos->second << endl;

	// search an element with value 3.0f
	// use lambda
	pos = find_if(coll.begin(), coll.end(), 
				  [](const FloatFloatMap::value_type& elem) { return elem.second == 3.0f; });
	// use function object
	//pos = find_if(coll.begin(), coll.end(), 
	//			  value_equals<float, float>(3.0f));
	if (pos != coll.end())
		cout << pos->first << ": " << pos->second << endl;
}

//////////////////////////////////////////////////////////////////////////
// 6.6.6 �ۺ�ʵ��

// չʾ�����¼��ɣ�
// 1. ���ʹ�� maps
// 2. ���׫д��ʹ�÷º��� functor or function object
// 3. �����ִ���ڶ�������׼��
// 4. ����ڡ����ں���Сд��������±Ƚ��ַ���

class RunTimeStringCmp {
public:
	enum cmp_mode { normal, nocase };
private:
	const cmp_mode mode;

	static bool nocase_compare(char c1, char c2)
	{
		return toupper(c1) < toupper(c2);
	}

public:
	RunTimeStringCmp(cmp_mode m = normal) : mode(m)
	{
	}

	bool operator()(const string& s1, const string& s2) const
	{
		if (mode == normal)
			return s1 < s2;
		else
		{
			return lexicographical_compare(s1.begin(), s1.end(),
										   s2.begin(), s2.end(),
										   nocase_compare);
		}
	}
};

typedef map<string, string, RunTimeStringCmp> StringStringMap;

void fillAndPrint(StringStringMap& coll)
{
	// fill insert elements in random order
	coll["Deutschland"] = "Germany";
	coll["deutsch"] = "German";
	coll["Haken"] = "snag";
	coll["arbeiten"] = "work";
	coll["Hund"] = "dog";
	coll["gehen"] = "go";
	coll["Unternehmen"] = "enterprise";
	coll["unternehmen"] = "undertake";
	coll["gehen"] = "walk";
	coll["Bestatter"] = "undertaker";

	// print elements
	StringStringMap::iterator pos;
	cout.setf(ios::left, ios::adjustfield);
	for (pos = coll.begin(); pos != coll.end(); ++pos)
	{
		cout << setw(15) << pos->first.c_str() << " "
			<< pos->second << endl;
	}
	cout << endl;
}

void f7()
{
	StringStringMap coll1;
	fillAndPrint(coll1);
	
	RunTimeStringCmp ignorecase(RunTimeStringCmp::nocase);

	StringStringMap coll2(ignorecase);
	fillAndPrint(coll2);

	/*
	Bestatter       undertaker
	Deutschland     Germany
	Haken           snag
	Hund            dog
	Unternehmen     enterprise
	arbeiten        work
	deutsch         German
	gehen           walk
	unternehmen     undertake

	arbeiten        work
	Bestatter       undertaker
	deutsch         German
	Deutschland     Germany
	gehen           walk
	Haken           snag
	Hund            dog
	Unternehmen     undertake

	�밴���������. . .
	*/
}
}  // !CH_6_6_MAPS_H