#pragma once
/*

chapter 7.9 Unordered Containers <The C++ Standard Library 2nd Edition>

The hash table, one important data structure for collections, was not part of the first version of the
C++ standard library. They were not part of the original STL and the committee decided that the
proposal for their inclusion in C++98 came too late. (At some point you have to stop introducing
features and focus on the details. Otherwise, you never finish the work.) However, with TR1,
containers with the characteristics of hash tables finally came into the standard.

Unordered Set/Multiset #include <unordered_set>
Unordered Map/Multimap #include <unordered_map>



2017.10.29

*/

#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>
#include <complex>
#include <numeric>

#include "hashval.h"
#include "Utility.h"
#include "buckets.h"

using namespace std;

namespace CH_7_9_H
{
/*
There, the types are defined as class templates inside namespace std:

namespace std
{
template <typename T,
	typename Hash = hash<T>,
	typename EqPred = equal_to<T>,
	typename Allocator = allocator<T> >
	class unordered_set;
template <typename T,
	typename Hash = hash<T>,
	typename EqPred = equal_to<T>,
	typename Allocator = allocator<T> >
	class unordered_multiset;
template <typename Key, typename T,
	typename Hash = hash<T>,
	typename EqPred = equal_to<T>,
	typename Allocator = allocator<pair<const Key, T> > >
	class unordered_map;
template <typename Key, typename T,
	typename Hash = hash<T>,
	typename EqPred = equal_to<T>,
	typename Allocator = allocator<pair<const Key, T> > >
	class unordered_multimap;
}

For unordered maps and multimaps, the first template parameter is the type of the element’s key,
and the second template parameter is the type of the element’s associated value. The elements of
an unordered map or an unordered multimap may have any types Key and T that meet the following
two requirements:

1. Both key and value must be copyable or movable.
2. The key must be comparable with the equivalence criterion.

The optional second/third template parameter defines the hash function. If a special hash function
is not passed, the default hash function hash<> is used, which is provided as a function object in
<functional> for all integral types, all floating-point types, pointers, strings, and some special
types.14 For all other value types, you must pass your own hash function, which is explained in
Section 7.9.2, and Section 7.9.7.

*/

//////////////////////////////////////////////////////////////////////////
// 7.9.1 Abilities of Unordered Containers

/*
All standardized unordered container classes are implemented as hash tables

a few of the specified abilities of unordered containers are based on the following assumptions

1. The hash tables use the “chaining” approach, whereby a hash code is associated with a linked
list. (This technique, also called “open hashing” or “closed addressing,” should not be confused
with “open addressing” or “closed hashing.”)

2. Whether these linked lists are singly or doubly linked is open to the implementers. For this
reason, the standard guarantees only that the iterators are “at least” forward iterators.

3. Various implementation strategies are possible for rehashing:
– With the traditional approach, a complete reorganization of the internal data happens from
time to time as a result of a single insert or erase operation.
– With incremental hashing, a resizing of the number of bucket or slots is performed gradually,
which is especially useful in real-time environments, where the price of enlarging a hash table
all at once can be too high.

The major advantage of using a hash table internally is its incredible running-time behavior.
Assuming that the hashing strategy is well chosen and well implemented, you can guarantee amor-
tized constant time for insertions, deletions, and element search (“amortized” because the occasional
rehashing happens that occurs can be a large operation with a linear complexity).

Unordered containers also have some disadvantages over ordinary associative containers:
Unordered containers don’t provide operators <, >, <=, and >= to order multiple instances of
these containers. However, == and != are provided (since C++11).
- lower_bound() and upper_bound() are not provided.
- Because the iterators are guaranteed only to be forward iterators, reverse iterators, including
rbegin(), rend(), crbegin(), and crend(), are not supported, and you can’t use algorithms
that require bidirectional iterators, or at least this is not portable.

As a programmer, you can specify parameters that influence the behavior of the hash table:

- You can specify the minimum number of buckets.
- You can (and sometimes have to) provide your own hash function.
- You can (and sometimes have to) provide your own equivalence criterion: a predicate that is used
to find the right element among all entries in the bucket lists.
- You can specify a maximum load factor, which leads to automatic rehashing when it is exceeded.
- You can force rehashing.

Note that rehashing is possible only after a call to insert(), rehash(), reserve(), or clear().
This is a consequence of the guarantee that erase() never invalidates iterators, references, and
pointers to the elements. Thus, if you delete hundreds of elements, the bucket size will not change.
But if you insert one element afterward, the bucket size might shrink.

Also note that in containers that support equivalent keys — unordered multisets and multimaps
— elements with equivalent keys are adjacent to each other when iterating over the elements of the
container. Rehashing and other operations that internally change the order of elements preserve the
relative order of elements with equivalent keys.
*/

//////////////////////////////////////////////////////////////////////////
// 7.9.2 Creating and Controlling Unordered Containers
/*
Create, Copy, Destroy

For construction, you have multiple abilities to pass arguments. On one hand, you can pass values
 as initial elements:
 1. An existing container of the same type(copy constructor)
 2. All elements of a range [begin, end)
 3. All elements of an initializer list

 On the other hand, you can pass arguments that influence the behavior of the unordered container:
 1. The hash function (either as template or as constructor argument)
 2. The equivalence criterion (either as template or as constructor argument)
 3. The initial number of buckets (as constructor argument)

Note:
The argument for max_load_factor() has to be a float. In general, a value between 0.7 and
0.8 provides a good compromise between speed and memory consumption. Note that the default
maximum load factor is 1.0, which means that, usually, collisions apply before rehash happens. For
this reason, if speed is an issue, you should always explicitly set the maximum load factor.
*/

void f()
{
	unordered_set<int> coll;
	coll.max_load_factor(0.7f);
	cout << coll.max_load_factor() << endl;
}

/*
Layout Operations

Unordered containers also provide operations to query and influence the internal layout.

Besides max_load_factor(), the member functions rehash() and reserve() are important.
They provide the functionality to rehash an unordered container (i.e., change the number of buckets)
with a slightly different interface:

coll.rehash(100);	// prepare for max(100 * max_load_factor(), size()) elements
coll.reserve(100);	// prepare for max(100, size()) elements (since C++11)

With bucket_count(), you can query the number of buckets an unordered container currently has.

*/

/*
Providing Your Own Hash Functions

All hash tables use a hash function, which maps the values of the elements that you put into the
container to a specific bucket. The goal is that two equal values always yield the same bucket index,
whereas for different values, different bucket entries ideally should be processed. For any range of
passed values, the hash function should provide a good distribution of hash values.

The hash function has to be a function or a function object that takes a value of the element type
as parameter and returns a value of type std::size_t. Thus, the current number of buckets is not
taken into account. Mapping the return value to the range of valid bucket indexes is done internally
in the container. Thus, your goal is to provide a function that maps the different element values
equally distributed in the range [0,size_t).

Here is an example of how to provide your own hash function:

	#include <functional>

	class Customer{
		...
	};

	class CustomerHash{
	public:
		std::size_t operator() (const Custromer& c) const
		{
			return ...
		}
	};

	std::unordered_set<Customer, CustomerHash> custset;

Here, CustomerHash is a function object that defines the hash function for class Customer.


Instead of passing a function object to the type of the container, you can also pass a hash function
as construction argument. Note, however, that the template type for the hash function must be set
accordingly:

	std::size_t customer_hash_func(const Customer& c)
	{
		return ...
	}

	std::unordered_set<Customer, std::size_t(*)(const Customer)> custset(20, customer_hash_func);

Here, customer_hash_func() is passed as second constructor argument with its type “pointer to
a function taking a Customer and returning a std::size_t” passed as second template argument.

If a special hash function is not passed, the default hash function hash<> is used, which is
provided as a function object in <functional> for “common” types: all integral types, all floatingpoint
types, pointers, strings, and some special types(error_code, thread::id, bitset<>, and vector<bool>).
For all other types, you have to provide your own hash function.

Providing a good hash function is trickier than it sounds. As a rule of thumb, you might use the
default hash functions to specify your own hash functions. A naive approach would be to simply add
all hash values for those attributes that are relevant for the hash function. For example:

	class CustomerHash {
	public:
		std::size_t operator() (const Customer& c) const
		{
			return std::hash<std::string>()(c.fname) +
				std::hash<std::string>()(c.lname) +
				std::hash<long>()(c.no);
		}
	};

Note, however, that experts will claim that this is still a poor hash function and that providing a
good hash function can be very tricky, In addition, providing such a hash function doesn’t seem as
easy as it should be.

A better approach is the following, which uses a hash function provided by Boost (see [Boost])
and a more convenient interface:

	#include <functional>

	// from boost (functional/hash):
	// see http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html
	template <typename T>
	inline void hash_combine(std::size_t& seed, const T& val)
	{
		seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	// auxiliary generic functions to create a hash value using a seed
	template <typename T>
	inline void hash_val(std::size_t& seed, const T& val)
	{
		hash_combine(seed, val);
	}
	template <typename T, typename... Types>
	inline void hash_val(std::size_t& seed,
						 const T& val, const Types&... args)
	{
		hash_combine(seed, val);
		hash_val(seed, args...);
	}

	// auxiliary generic function to create a hash value out of a heterogeneous list of arguments
	template <typename... Types>
	inline std::size_t hash_val(const Types&... args)
	{
		std::size_t seed = 0;
		hash_val(seed, args...);
		return seed;
	}
*/

/*
A convenience function implemented using variadic templates (see Section 3.1.9, page 26) allows
calling hash_val() with an arbitrary number of elements of any type to process a hash value out of
all these values. For example:
*/

class Customer_1 {
public:
	string first_name;
	string last_name;
	int cno;
	Customer_1(string& first_name_, string& last_name_, int cno_) :
		first_name(first_name_), last_name(last_name_), cno(cno_)
	{
	}
};

class CustomerHash_1 {
public:
	size_t operator()(const Customer_1& c) const
	{
		return hash_val(c.first_name, c.last_name, c.cno);
	}
};

class CustomerEqual_1 {
public:
	bool operator()(const Customer_1& c1, const Customer_1& c2) const
	{
		return c1.cno == c2.cno;
	}
};

void f3()
{
	unordered_set<Customer_1, CustomerHash_1, CustomerEqual_1> custset;
}

/*
In any case, to verify the effect of your own hash function,
you may use the bucket interface
*/


/*
Providing Your Own Equivalence Criterion

As the third/fourth template parameter of the unordered container types, you can pass the equivalence
criterion, a predicate that is used to find equal values in the same bucket.

For this reason, the most convenient approach to providing a valid equivalence criterion is to provide 
operator == for your own type if it is not predefined either as member or as global function. For example:

	class Customer{
		...
	};

	bool operator== (const Customer& c1, const Customer& c2)
	{
		...
	}

	std::unordered_multiset<Customer, CustomerHash> custmset;
	std::unordered_multimap<Customer, String, CustomerHash> custmap;

Instead, however, you can also provide your own equivalence criterion as the following example
demonstrates:

	#include <functional>

	class Customer{
		...
	};

	class CustomerEqual{
	public:
		bool operator() (const Customer& c1, const Customer& c1)
		{
			return ...
		}
	};

	std::unordered_multiset<Customer, CustomerHash, CustomerEqual> custmset;
	std::unordered_multimap<Customer, String, CustomerHash, CustomerEqual> custmap;

Here, for type Customer, a function object is defined in which you have to implement operator()
so that it compares two elements (or two keys for maps) and returns a Boolean value indicating
whether they are equal.

Whenever values are considered to be equal according to the current equivalence criterion, they
should also yield the same hash values according to the current hash function. For this reason,
an unordered container that is instantiated with a nondefault equivalence predicate usually needs a
nondefault hash function as well.
*/

//////////////////////////////////////////////////////////////////////////
// 7.9.3 Other Operations for Unordered Containers

// Nonmodifying Operations
// c.empty(), c.size(), c1 == c2, c1 != c2
// Note again that for comparisons, only operators == and != are provided for unordered containers.
// In worst - case scenarios, they might, however, provide quadratic complexity.

// Special Search Operations
/*
Unordered containers are optimized for fast searching of elements. To benefit from this behavior, the
containers provide special search functions. These functions are special versions of
general algorithms that have the same name. You should always prefer the optimized versions for
unordered containers to achieve constant complexity instead of the linear complexity of the general
algorithms, provided that the hash values are evenly distributed.

c.count(), c.find(), c.equal_range()
*/

// Assignments
/*
For these operations, both containers must have the same type. In particular, the type of the hash
functions and the equivalence criteria must be the same, although the functions themselves may be
different. If the functions are different, they will also get assigned or swapped.

c = c2
c = rv
c = initialist
c1.swap(c2)
swap(c1, c2)
*/

// Iterator Functions and Element Access
/*
For unordered (multi)sets, all elements are considered constant from an iterator’s point of view.
For unordered (multi)maps, the key of all elements is considered to be constant. 

This is necessary to ensure that you can’t compromise the position of the elements by changing their values.
For example, you can’t call the remove() algorithm, because it “removes” by overwriting “removed” 
elements with the following elements.
*/

// Inserting and Removing Elements
/*
	// 4 ways to pass a value into an unordered map or multimap

	unordered_map<string, float> coll;
	
	// 1. use an initializer list
	coll.insert({ "otto", 22.3f });

	// 2. use value_type
	coll.insert(unordered_map<string, float>::value_type("otto", 22.3f));
	coll.insert(decltype(coll)::value_type("otto", 22.3f));

	// 3. use pair<>
	coll.insert(pair<string, float>("otto", 22.3f));
	coll.insert(pair<const string, float>("otto", 22.3f));

	// 4. use make_pair()
	coll.insert(make_pair("otto", 22.3f));
*/

void f5()
{
	unordered_map<string, float> coll;
	// checks whether the insertion was successful
	if (coll.insert(make_pair("otto", 22.3f)).second)
		cout << "OK, could insert otto/22.3f" << endl;
	else
		cout << "Oops, could not insert otto/22.3f "
		<< "(Key otto already exists)" << endl;

	/*
	Note again that when using emplace() to insert a new element by passing the values for its construction,
	you have to pass two lists of arguments: one for the key and one for the element. The most	convenient 
	way to do this is as follows:
	*/
	unordered_multimap<string, complex<float>> m;
	m.emplace(piecewise_construct, // pass tuple elements as arguments
			  make_tuple("hello"), // elements for the key
			  make_tuple(3.4, 7.8)); // elements for the value
	// or in this way
	m.emplace("hello", complex<float>(3.4, 7.9));


	for (decltype(m)::iterator i = m.begin(); i != m.end(); ++i)
	{
		cout << i->first << " " << i->second << endl;
	}
}

//////////////////////////////////////////////////////////////////////////
// 7.9.4 The Bucket Interface

void f6()
{
	unordered_multimap<string, complex<float>> m;
	m.insert({ "Hello", complex<float>(1.2f, 3.4f) });
	m.insert({ "Hello", complex<float>(3.2f, 4.1f) });
	m.insert({ "World", complex<float>(3.2f, 4.1f) });
	m.insert({ "Nice", complex<float>(3.9f, 1.0f) });
	m.insert({ "Mice", complex<float>(3.2f, 4.1f) });

	cout << "m.bucket_count() = "<< m.bucket_count() << endl;
	int n = m.bucket(string("Hello"));
	cout << "m.bucket_size( "<<n <<" ) = " << m.bucket_size(n) << endl;

	cout << "In bucket " << n << ", elements are: " << endl;
	for (decltype(m)::iterator i = m.begin(n); i != m.end(n); ++i)
	{
		cout << i->first << " " << i->second << endl;
	}

	/*
	m.bucket_count() = 8
	m.bucket_size( 3 ) = 3
	In bucket 3, elements are:
	World (3.2,4.1)
	Hello (1.2,3.4)
	Hello (3.2,4.1)
	请按任意键继续. . .
	*/
}

//////////////////////////////////////////////////////////////////////////
// 7.9.5 Using Unordered Maps as Associative Arrays

// c[key], c.at(key)

//////////////////////////////////////////////////////////////////////////
// 7.9.6 Exception Handling

//////////////////////////////////////////////////////////////////////////
// 7.9.7 Examples of Using Unordered Containers

// The following program demonstrates the fundamental abilities of unordered containers, using an
// unordered set :
void f7()
{
	// create and initialize unordered set
	unordered_set<int> coll = { 1,2,3,5,7,11,13,17,19,77 };

	// print elements
	// - elements are in arbitrary order
	cout << "coll: ";
	PRINT_ELEMENTS(coll);
	cout << endl;

	// insert some additional elements
	// - might cause rehashing and create different order
	coll.insert({ -7,17,33,-11,17,19,1,13 });

	cout << "coll: ";
	PRINT_ELEMENTS(coll);
	cout << endl;

	// remove element with specific value
	coll.erase(33);

	// insert sum of all existing values
	coll.insert(accumulate(coll.begin(), coll.end(), 0));

	// check if value 19 is in the set
	if (coll.find(19) != coll.end())
	{
		cout << "19 is available" << endl;
	}

	// remove all negative values
	for (decltype(coll)::iterator pos = coll.begin(); pos != coll.end();)
	{
		if (*pos < 0)
			pos = coll.erase(pos);
		else
			++pos;
	}

	cout << "coll: ";
	PRINT_ELEMENTS(coll);
	cout << endl;

	/*
	As long as you only insert, erase, and find elements with a specific value, unordered containers
	provide the best running-time behavior because all these operations have amortized constant complexity.
	However, you can’t make any assumption about the order of the elements. For example, the
	program might have the following output:
	
	77 11 1 13 2 3 5 17 7 19
	-11 1 2 3 -7 5 7 77 33 11 13 17 19
	-11 1 2 3 -7 5 7 77 11 13 17 19 137
	19 is available
	1 2 3 5 7 77 11 13 17 19 137

	*/
}

// When using an unordered multiset rather than an unordered set, duplicates are allowed. For
// example, the following program :

void f8()
{
	unordered_multiset<int> coll = { 1,2,3,5,7,11,13,17,19,77 };

	cout << "coll: ";
	PRINT_ELEMENTS(coll);
	cout << endl;

	coll.insert({ -7,17,33,-11,17,19,1,13 });

	cout << "coll: ";
	PRINT_ELEMENTS(coll);
	cout << endl;

	// remove all elements with specific value
	coll.erase(17);

	// remove one of the elements with specific value
	auto pos = coll.find(13);
	if (pos != coll.end())
		coll.erase(pos);

	cout << "coll: ";
	PRINT_ELEMENTS(coll);
	cout << endl;

	/*
	
	coll: 17 1 2 19 11 3 77 13 5 7
	coll: 17 17 17 1 1 2 19 19 11 3 77 13 13 5 7 -7 33 -11
	coll: 1 1 2 19 19 11 3 77 13 5 7 -7 33 -11
	请按任意键继续. . .
	
	*/
}

// Example of Providing Your Own Hash Function and Equivalence Criterion

// The following example shows how to define and specify a hash function and an equivalence criterion
// for a type Customer, which is used as element type of an unordered set :
// hashfunc1.h

// Using Lambdas as Hash Function and Equivalence Criterion

// You can even use lambdas to specify the hash function and/or the equivalence criterion. For example:
// hashfunc2.h

// Example of Using the Bucket Interface

void f9()
{
	// create and initialize an unordered set
	std::unordered_set<int> intset = { 1,2,3,5,7,11,13,17,19 };
	printHashTableState(intset);

	// insert some additional values (might cause rehashing)
	intset.insert({ -7,17,33,4 });
	printHashTableState(intset);
}

void f10()
{
	std::unordered_multimap<string, string> dict = {
		{ "day","Tag" },
		{ "strange","fremd" },
		{ "car","Auto" },
		{ "smart","elegant" },
		{ "trait","Merkmal" },
		{ "strange","seltsam" }
	};
	printHashTableState(dict);

	// insert some additional values (might cause rehashing)
	dict.insert({ { "smart","raffiniert" },
	{ "smart","klug" },
	{ "clever","raffiniert" }
	});
	printHashTableState(dict);

	// modify maximum load factor (might cause rehashing)
	dict.max_load_factor(0.7f);
	printHashTableState(dict);
}

//////////////////////////////////////////////////////////////////////////
// 7.11 Implementing Reference Semantics
/*
In general, STL container classes provide value semantics and not reference semantics. Thus, the
containers create internal copies of the elements they contain and return copies of those elements.

To summarize, if you want reference semantics in STL containers — whether because
copying elements is expensive or because identical elements will be shared by different collections
— you should use a smart pointer class that avoids possible errors. In addition, using a reference
wrapper is possible.
*/

// Using Shared Pointers
// refsem1.h

// Using the Reference Wrapper
// TODO

//////////////////////////////////////////////////////////////////////////
// 7.12 When to Use Which Container



}  // !CH_7_9_H
