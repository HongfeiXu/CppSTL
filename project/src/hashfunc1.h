#pragma once

#include <unordered_set>
#include <string>
#include <iostream>
#include "Utility.h"
#include "hashval.h"

using namespace std;

namespace HASHFUNC1_H
{
class Customer {
private:
	string fname;
	string lname;
	long no;
public:
	Customer(const string& fname_, const string& lname_, const long no_)
		: fname(fname_), lname(lname_), no(no_)
	{
	}
	friend ostream& operator << (ostream& strm, const Customer& c)
	{
		return strm << "[" << c.fname << "," << c.lname << ","
			<< c.no << "]";
	}
	friend class CustomerHash;
	friend class CustomerEqual;

	//bool operator== (const Customer& c2) const
	//{
	//	return no == c2.no;
	//}
};



class CustomerHash {
public:
	size_t operator() (const Customer& c) const
	{
		return hash_val(c.fname, c.lname, c.no);
	}
};

class CustomerEqual {
public:
	bool operator() (const Customer& c1, const Customer& c2) const
	{
		return c1.no == c2.no;
	}
};

/*
As you can see, the equivalence function does not necessarily have to evaluate the same values as
the hash function. However, as written, it should be guaranteed that values that are equal according
the equivalence criterion yield the same hash value (which indirectly is the case here assuming that
customer numbers are unique).
*/
void f()
{
	unordered_set<Customer, CustomerHash, CustomerEqual> custset;
	custset.insert(Customer("nico", "josuttis", 42));

	PRINT_ELEMENTS(custset);
	cout << endl;
}



}  // !HASHFUNC1_H