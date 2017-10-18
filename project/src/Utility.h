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