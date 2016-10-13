

#ifndef EASYFIND_H
# define EASYFIND_H

#include <algorithm>

template <typename T>
int		*easyfind(T const &container, int val)
{
	return std::find(container, container + container.size(), val);
}

#endif