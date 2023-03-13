#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <cstddef>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "enable_if.hpp"
#include "equal.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T>>
	class vector
	{
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef typename ft::random_access_iterator<value_type> iterator;
		typedef typename ft::cRandom_access_iterator<value_type> const_iterator;
		typedef typename ft:reverse_iterator<iterator> reverse_iterator;
		typedef typename ft:reverse_iterator<const_iterator> const_reverse_iterator;
	private:
		allocator_type	_alloc;
		pointer			_array;
		size_type		_size;
		size_type		_capacity;
	public:
		
	};
}

#endif