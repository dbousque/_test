

#ifndef EASYFIND_H
# define EASYFIND_H

#include <algorithm>

template <typename T>
typename T::iterator easyfind(T &container, int val)
{
	return std::find(container.begin(), container.end(), val);
}

#endif