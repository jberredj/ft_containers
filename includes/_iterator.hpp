#ifndef _ITERATOR_HPP
#define _ITERATOR_HPP
#include <cstddef>

namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *,
			  class Reference = T &>
	struct iterator
	{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};
}

#endif