#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <cstddef>
#include <exception>
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
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef typename ft::random_access_iterator<value_type> iterator;
		typedef typename ft::cRandom_access_iterator<value_type> const_iterator;
		typedef typename ft : reverse_iterator<iterator> reverse_iterator;
		typedef typename ft : reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		allocator_type _alloc;
		pointer _array;
		size_type _size;
		size_type _capacity;

	public:
		// giving default value to allocator make this constructor the default one
		explicit vector(const Allocator &alloc = allocator_type()) : _alloc(alloc), _array(NULL), _size(0), _capacity(0) {}
		explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator())
			: _alloc(alloc), _array(NULL),
			  _size(count), _capacity(count)
		{
			assign(count, value);
		}
		template <class InputIt>
		vector(InputIt first, InputIt last, const Allocator &alloc = Allocator()) : _alloc(alloc), _array(NULL), _size(0), _capacity(0) // TODO: Some implemetation uses enable_if<is_integral> figure out why
		{
			assign(first, last); // TODO: implement assign
		}

		vector(const vector &other)
		{
			assign(other.begin(), other.end());
		}

		~vector()
		{
			clear();							  // TODO: implement clear;
			_alloc.deallocate(_value, _capacity); // clear() will be in charge of destroy
		}

		vector &operator=(const vector &other)
		{
			assign(other.begin(), other.end());
			return *this;
		}

		void assign(size_type count, const T &value)
		{
			clear();
			insert(begin(), count, value); // TODO: implement insert
		}

		template <class InputIt>
		void assign(InputIt first, InputIt last)
		{
			clear();
			insert(begin(), first, last);
		}

		allocator_type get_allocator() const { return _alloc; }

		const_reference at(size_type pos) const
		{
			if (!(pos < _size))
				throw std::out_of_range("ft::vector::at");

			return _array[pos];
		}

		reference at(size_type pos)
		{
			if (!(pos < _size))
				throw std::out_of_range("ft::vector::at");

			return _array[pos];
		}

		reference operator[](size_type pos) { return *(_array + pos); }
		const_reference operator[](size_type pos) const { return *(_array + pos); }

		reference front(void) { return *_array; }
		const_reference front(void) const { return *_array; }

		reference back(void) { return *(_array + (_size - 1)); }
		const_reference back(void) const { return *(_array + (_size - 1)); }

		pointer data(void) { return _array; }
		const_pointer data(void) const { return _array; }
	};

}

#endif