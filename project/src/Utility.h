#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

template <class T>		// T is a container type
inline void PRINT_ELEMENTS(const T& coll, char seperator = ' ')
{
	typename T::const_iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos)
	{
		std::cout << *pos << seperator;
	}
}

// 住：此函数只适用于 map 不适用于 multimap
namespace MyLib
{
template <class Cont>
inline bool replace_key(Cont& c,
						const typename Cont::key_type& old_key,
						const typename Cont::key_type& new_key)
{
	typename Cont::iterator pos;
	pos = c.find(old_key);

	if (pos != c.end())
	{
		// insert new element with value of old element
		c.insert(typename Cont::value_type(new_key, pos->second));

		// remove old element
		c.erase(pos);
		return true;
	}
	else
	{
		return false;
	}
}
}  // !MyLib
