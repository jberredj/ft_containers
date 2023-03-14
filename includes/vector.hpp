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
	template <class T, class Allocator = std::allocator<T> >
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
		explicit vector(const Allocator &alloc = allocator_type()) : _alloc(alloc), _array(_alloc.allocate(0)), _size(0), _capacity(0) {}
		explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator())
			: _alloc(alloc), _array(_alloc.allocate(0)),
			  _size(0), _capacity(0)
		{
			assign(count, value);
		}
		template <class InputIt>
		vector(InputIt first, InputIt last, const Allocator &alloc = Allocator(),
			   typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = NULL)
			: _alloc(alloc), _array(_alloc.allocate(0)), _size(0), _capacity(0)
		{
			assign(first, last); // TODO: implement assign
		}

		vector(const vector &other)
			: _alloc(other._alloc), _array(_alloc.allocate(0)),
			  _size(0), _capacity(0)
		{
			assign(other.begin(), other.end());
		}

		~vector()
		{
			clear();
			_alloc.deallocate(_array, _capacity); // clear() will be in charge of destroy
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
		void assign(InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = NULL)
		{
			clear();
			insert(begin(), first, last);
		}

		allocator_type get_allocator() const { return _alloc; }

		const_reference at(size_type pos) const
		{
			if (pos > _size)
				throw std::out_of_range("ft::vector::at");

			return _array[pos];
		}

		reference at(size_type pos)
		{
			if (pos > _size)
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
		reverse_iterator rbegin(void) { return reverse_iterator(_array + _size); };
		const_reverse_iterator rbegin(void) const { return const_reverse_iterator(_array + _size); };
		reverse_iterator rend(void) { return reverse_iterator(_array); };
		const_reverse_iterator rend(void) const { return const_reverse_iterator(_array); };

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

			pointer newArray = _alloc.allocate(new_cap);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(&newArray[i], _array[i]);
				_alloc.destroy(&_array[i]);
			}

			_alloc.deallocate(_array, _capacity);
			_array = newArray;
			_capacity = new_cap;
		}

		void clear(void)
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_array + i);
			_size = 0;
		}

		iterator insert(iterator pos, const T &value)
		{
			difference_type index = pos - begin();
			insert(pos, 1, value);
			return begin() + index;
		}

		void insert(iterator pos, size_type count, const T &value)
		{
			pos = _reserve_keep_pos(pos, count);

			_rightShift(pos, count);
			for (iterator cur = pos; cur < pos + count; cur++)
				_alloc.construct(&(*cur), value);
			_size += count;
		}

		template <class InputIt>
		void insert(iterator pos, InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = NULL)
		{
			difference_type count = 0;
			InputIt it = first;
			count = std::distance(first, last);

			pos = _reserve_keep_pos(pos, count);
			_rightShift(pos, count);

			it = first;
			for (; it != last; pos++, it++)
			{
				_alloc.construct(&(*pos), *it);
			}
			_size += count;
		}

		iterator erase(iterator pos)
		{
			if (pos == end())
				return pos;

			_inorderDestroy(pos, pos + 1);
			if (pos < end() - 1)
				_leftShift(pos, 1);
			_size--;
			return pos;
		}

		iterator erase(iterator first, iterator last)
		{
			if (first == last)
				return first;

			_inorderDestroy(first, last);
			if (last < end())
				_leftShift(first, std::distance(first, last));
			_size -= (last - first);
			return first;
		}

		void push_back(const T &value) { insert(end(), value); }
		void pop_back() { erase(end() - 1); }

		void resize(size_type count, T value = T())
		{
			if (count < size())
				erase(begin() + count, end());
			else if (count > size())
				insert(end(), count - _size, value);
		}

		void swap(vector &other)
		{
			allocator_type tmpAlloc = other._alloc;
			T *tmpArray = other._array;
			size_type tmpSize = other._size;
			size_type tmpCapacity = other._capacity;

			other._alloc = _alloc;
			other._array = _array;
			other._size = _size;
			other._capacity = _capacity;

			_alloc = tmpAlloc;
			_array = tmpArray;
			_size = tmpSize;
			_capacity = tmpCapacity;
		}

	private:
		iterator _reserve_keep_pos(iterator pos, size_type count)
		{
			if (_size + count <= _capacity)
				return pos;
			difference_type index = pos - begin();
			reserve(std::max<size_type>(count + _size, 2 * _size));
			return begin() + index;
		}

		void _rightShift(iterator pos, size_type count)
		{
			if (!count)
				return;

			iterator new_pos = end() + count - 1;
			for (iterator it = end() - 1; it >= pos; it--, new_pos--)
			{
				_alloc.construct(&(*new_pos), *it);
				_alloc.destroy(&(*it));
			}
		}

		void _leftShift(iterator pos, size_type count)
		{
			for (iterator it = pos; it < end() - count; it++)
			{
				_alloc.construct(&(*it), *(it + count));
				_alloc.destroy(&(*(it + count)));
			}
		}

		void _inorderDestroy(iterator first, iterator last)
		{
			for (iterator it = first; it < last; it++)
			{
				_alloc.destroy(&(*it));
			}
		}
	};

	template <class T, class Allocator>
	bool operator==(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	template <class T, class Allocator>
	bool operator!=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Allocator>
	bool operator<(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Allocator>
	bool operator<=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Allocator>
	bool operator>(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Allocator>
	bool operator>=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Allocator>
	void swap(vector<T, Allocator> &lhs, vector<T, Allocator> &rhs)
	{
		lhs.swap(rhs);
	}

}

#endif