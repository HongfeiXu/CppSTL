#pragma once

#include <unordered_set>
#include <string>
#include <iostream>
#include "hashval.h"
#include "Utility.h"

using namespace std;

namespace HASHFUNC2_H
{
class Customer {
private:
	string fname;
	string lname;
	long no;
public:
	Customer(const string& fn, const string& ln, long n)
		: fname(fn), lname(ln), no(n)
	{
	}
	string firstname() const
	{
		return fname;
	}
	string lastname() const
	{
		return lname;
	}
	long number() const
	{
		return no;
	}
	friend ostream& operator << (ostream& strm, const Customer& c)
	{
		return strm << "[" << c.fname << "," << c.lname << ","
			<< c.no << "]";
	}
};

/*
Note that you have to use decltype to yield the type of the lambda to be able to pass it as template
argument to the declaration of the unordered container. The reason is that for lambdas, no default
constructor and assignment operator are defined. Therefore, you also have to pass the lambdas to
the constructor. This is possible only as second and third arguments. Thus, you have to specify the
initial bucket size 10 in this case.
*/
void f()
{
	// lambda for user-defined hash function
	auto hash = [](const Customer& c) 
	{ 
		return hash_val(c.firstname(), c.lastname(), c.number());
	};

	// lambda for user-defined equality criterion
	auto eq = [](const Customer& c1, const Customer& c2)
	{
		return c1.number() == c2.number();
	};

	// create unordered set with user-defined behavior
	unordered_set<Customer, decltype(hash), decltype(eq)> custset(10, hash, eq);

	custset.insert(Customer("nico", "josuttis", 42));
	PRINT_ELEMENTS(custset);
	cout << endl;
}

}  // !HASHFUNC2_H