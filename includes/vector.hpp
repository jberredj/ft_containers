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
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

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
			clear();
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

		iterator begin(void) { return iterator(_array); };
		const_iterator begin(void) const { return const_iterator(_array); };
		iterator end(void) { return iterator(_array + _size); };
		const_iterator end(void) const { return const_iterator(_array + _size); };
		reverse_iterator rbegin(void) { return reverse_iterator(begin()); };
		const_reverse_iterator rbegin(void) const { return const_reverse_iterator(begin()); };
		reverse_iterator rend(void) { return reverse_iterator(end()); };
		const_reverse_iterator rend(void) const { return const_reverse_iterator(end()); };

		bool empty(void) const { return _size == 0; }
		size_type size(void) const { return _size; }
		size_type max_size(void) const { return _alloc.max_size(); }
		size_type capacity(void) const { return _capacity; }

		void reserve(size_type new_cap)
		{
			if (max_size() < new_cap)
				throw std::length_error("vector::reserve");
			if (new_cap <= _capacity)
				return;

			T *newArray = _alloc.allocate(new_cap);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(newArray + i, _array + i);
				_alloc.destroy(_array + i);
			}

			_alloc.dealocate(_array, _capacity);
			_array = newArray;
			_capacity = new_cap;
		}

		void clear(void)
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_array + i);
			_size = 0;
		}
	};

}

#endif