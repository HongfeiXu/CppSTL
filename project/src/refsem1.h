#pragma once

#include <iostream>
#include <string>
#include <set>
#include <deque>
#include <algorithm>
#include <memory>

namespace REFSEM1_H
{
class Item {
private:
	std::string name;
	float price;
public:
	Item(const std::string& n, float p = 0) : name(n), price(p)
	{
	}
	std::string getName() const
	{
		return name;
	}
	void setName(const std::string& n)
	{
		name = n;
	}
	float getPrice() const
	{
		return price;
	}
	void setPrice(float p)
	{
		price = p;
	}
};

template <typename Coll>
void printItems(const std::string& msg, const Coll& coll)
{
	std::cout << msg << std::endl;
	for (const auto& elem : coll)
	{
		std::cout << ' ' << elem->getName() << ": "
			<< elem->getPrice() << std::endl;
	}
}

void f()
{
	using namespace std;
	// two different collections sharing Items
	typedef shared_ptr<Item> ItemPtr;
	set<ItemPtr> allItems;
	deque<ItemPtr> bestsellers;

	// insert objects into the collections
	// - bestsellers are in both collections
	bestsellers = { ItemPtr(new Item("Kong Yize",20.10)),
		ItemPtr(new Item("A Midsummer Night��s Dream",14.99)),
		ItemPtr(new Item("The Maltese Falcon",9.88)) };
	allItems = { ItemPtr(new Item("Water",0.44)),
		ItemPtr(new Item("Pizza",2.22)) };
	allItems.insert(bestsellers.begin(), bestsellers.end());

	// print contents of both collections
	printItems("bestsellers:", bestsellers);
	printItems("all:", allItems);
	cout << endl;

	// double price of bestsellers
	for_each(bestsellers.begin(), bestsellers.end(),
			 [](shared_ptr<Item>& elem)
	{
		elem->setPrice(elem->getPrice() * 2);
	});

	// replace second bestseller by first item with name "Pizza"
	bestsellers[1] = *(find_if(allItems.begin(), allItems.end(),
					   [](shared_ptr<Item> elem)
	{
		return elem->getName() == "Pizza";
	}));

	// set price of first bestseller
	bestsellers[0]->setPrice(44.77);

	// print contents of both collections
	printItems("bestsellers:", bestsellers);
	printItems("all:", allItems);

	/*
	
	bestsellers:
	 Kong Yize: 20.1
	 A Midsummer Night��s Dream: 14.99
	 The Maltese Falcon: 9.88
	all:
	 A Midsummer Night��s Dream: 14.99
	 Kong Yize: 20.1
	 Water: 0.44
	 The Maltese Falcon: 9.88
	 Pizza: 2.22

	bestsellers:
	 Kong Yize: 44.77
	 Pizza: 2.22
	 The Maltese Falcon: 19.76
	all:
	 A Midsummer Night��s Dream: 29.98
	 Kong Yize: 44.77
	 Water: 0.44
	 The Maltese Falcon: 19.76
	 Pizza: 2.22
	�밴���������. . .
	
	*/
}

}   // !REFSEM1_H
