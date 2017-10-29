#pragma once
/*

chapter 6.6 Maps 和 Multimaps

Map 和 multimap 将 key/value pair （键值/实值 对组）当做元素，进行管理。
它们可以根据 key 的排序准则自动将元素排序。

Map 和 multimap 的元素型别 key 和 T，必须满足一下两个条件：
1. key/value 必须具备 assignable 和 copyable 性质。
2. 对于排序准则而言，key 必须是 comparable的。

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
// 6.6.1 Maps 和 Multimaps 的能力

// maps/multimaps 通常以平衡二叉树完成。
// Maps 和 multimaps 根据元素的 key 自动对元素进行排序。这么一来，根据已知的 key 来搜寻某个元素时就能有很好的性能，
// 而根据已知 value 来搜寻元素时，性能就很糟糕。
// “自动排序”这一性质使得 map 和 multimap 身上有了一条重要的限制：你不可以直接改变元素的 key。因为这会破坏正确次序。
// 要修改元素的 key，你必须先移除拥有该 key 的元素，然后插入拥有新的 key/value 的元素。

//////////////////////////////////////////////////////////////////////////
// 6.6.2 Maps 和 Multimaps 的操作函数

// 生成，复制和销毁
// 有两种方式可以定义排序准则：
// 1. 以 template 参数定义之。这种情况下，排序准则就是型别的一部分。例如： std::map<float, std::string, std::greater<float>> coll;
// 因此型别系统确保“只有排序准则相同的容器才能合并”。
// 2. 以构造函数参数定义之。这种情况下，你可以有一个“排序准则型别”并为它指定不同的排序准则（也就是说让型别所产生出来的对象（代表一个排序准则）的初值或状态不同）。
// 如果执行时才获得排序准则，而且需要用到不同的排序准则（但数据型别必须相同），此方式方可排上用场。
// 典型的例子就是在执行期指定“key 的型别为 string”的排序准则。

// 非变动性操作
// 元素比较动作只能用于型别相同的容器。换言之，容器的 key、value、排序准则都必须有相同的型别，否则编译会产生型别方面的错误。

// 特殊的搜寻动作
// 成员函数 find() 用来搜寻具有某个 key 的第一个元素，并返回一个迭代器，指向该位置。

// 赋值
// 注：赋值操作的两端容器必须具有相同型别。尽管“比较准则”本身可能是不同的，但其型别必须相同。

// 迭代器函数和元素存取
// 注：和其他所有关联容器类似，这里的迭代器是双向迭代器。所以，无法使用那些只能用于随机存取迭代器的 STL 算法。
// 更重要的是，在 map 和 multimap 中，所有元素的 key 都被视为常数。因此元素的实质型别是 pair<const Key, T>。
// 这个限制是为了确保你不会因为变更元素的 key 而破坏已经排好的元素次序。
// 例如你不能对它们调用 remove()，因为 remove() 实际上是以一个参数值覆盖被移除的元素。
// 如果要移除元素，你只能使用 map 或 multimap 所提供的成员函数。

// 注：如果你一定得改变你元素的 key，只有一条路：以一个“value”相同的新元素替换掉旧元素。
// 下面是一个泛化函数。

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

	// 三种不同方式将 value 传入 map
	coll.insert(StringFloatMap::value_type("Hello", 1.0f));
	coll.insert(pair<string, float>("World", 2.0f));		// use implicit conversion
//	coll.insert(pair<const string, float>("World", 2.0f));	// use no implicit conversion
	coll.insert(make_pair("Hungry", 3.0f));

	for (StringFloatMap::iterator pos = coll.begin(); pos != coll.end(); ++pos)
		cout << pos->first << " " << pos->second << endl;

	// 改变元素 key
	//MyLib::replace_key(coll, "World", "Witcher");

	// 改变元素 key，与上面的效果相同
	coll["Witcher"] = coll["World"];
	coll.erase("World");


	for (StringFloatMap::iterator pos = coll.begin(); pos != coll.end(); ++pos)
		cout << pos->first << " " << pos->second << endl;
}

void f2()
{
	// 移除拥有某个 value 的元素
	typedef map<string, float> StringFloatMap;
	StringFloatMap coll;
	coll.insert(make_pair("Hello", 1.2f));
	coll.insert(make_pair("World", 1.3f));
	coll.insert(make_pair("Bobo", 2.2f));

	for (StringFloatMap::iterator pos = coll.begin(); pos != coll.end();)
	{
		if (pos->second == 1.3f)
			pos = coll.erase(pos);	// erase 返回下一元素的位置
		else
			++pos;
	}

	for (StringFloatMap::iterator pos = coll.begin(); pos != coll.end(); ++pos)
		cout << pos->first << " " << pos->second << endl;
}

//////////////////////////////////////////////////////////////////////////
// 6.6.3 将 Maps 视为关联式数组 Associated Arrays

// m[key] 返回一个 reference，指向键值为 key 的元素。如果该元素尚未存在，就安插该元素。
// 优点：可以透过更方便的接口对着 map 安插新元素
// 缺点：你可能会不小心误置新元素，同时，请注意，这种安插方式比一般的 maps 安插方式来的慢。
// 原因是新元素必须先使用 default 构造函数将实值初始化，而这个初值马上又被真正的 value 覆盖了。

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
// 6.6.4 异常处理
// 与 sets 和 multisets 一样

//////////////////////////////////////////////////////////////////////////
// 6.6.5 Maps 和 Multimaps 运用实例

// 将 Map 当做关联式数组
// 这个例子将 map 当成一个关联式数组来使用，用来反映股票行情。元素的键值是股票名称，实值是股票价格。
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

	请按任意键继续. . .
	*/
}

// 将 Multimap 当做字典
// 下面这个例子展示如何将 multimap 当成一个字典来使用

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
	请按任意键继续. . .
	*/
}

// 搜寻具有某特定实值的元素
// 下面的例子会展示如何使用全局 find_if() 算法来搜寻具有某特定 value 的元素

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
// 6.6.6 综合实例

// 展示了如下技巧：
// 1. 如何使用 maps
// 2. 如何撰写和使用仿函数 functor or function object
// 3. 如何在执行期定义排序准则
// 4. 如何在“不在乎大小写”的情况下比较字符串

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

	请按任意键继续. . .
	*/
}
}  // !CH_6_6_MAPS_H