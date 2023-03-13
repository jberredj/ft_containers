#ifndef MAP_HPP
#define MAP_HPP
#include <functional>
#include <memory>
#include <cstddef>
#include "_rbt.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include <iostream>

namespace ft
{
	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
	private:
		typedef RBT<ft::pair<const Key, T>, Compare, typename Allocator::template rebind<T>::other> _tree_t;

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef typename _tree_t::iterator iterator;
		typedef typename _tree_t::const_iterator const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			bool operator()(const value_type &lhs, const value_type &rhs) const
			{
				return comp(lhs.first, rhs.first);
			}
		};

	private:
		value_compare _val_comp;
		allocator_type _alloc;
		key_compare _key_comp;

		_tree_t _tree;

	public:
		// the 2 first constructor are handled by this one
		map() : _val_comp(key_compare()), _alloc(allocator_type()), _key_comp(key_compare()),
				_size(0), _tree(allocator_type(), key_compare()) {}
		explicit map(const Compare &comp, const Allocator &alloc = Allocator()) : _val_comp(comp), _alloc(alloc), _key_comp(comp), _size(0), _tree(alloc, comp) {}

		template <class InputIt>
		map(InputIt first, InputIt last, const key_compare &key_comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _val_comp(key_comp), _alloc(alloc), _key_comp(key_comp), _size(0),
			  _tree(_alloc, _key_comp)
		{
			insert(first, last);
		}
		map(const map<Key, T, Compare, Allocator> &other)
			: _val_comp(other._key_comp), _alloc(other._alloc),
			  _key_comp(other._key_comp), _size(other._size), _tree(other._tree) {}

		~map() { clear(); }

		reference operator=(const_reference rhs)
		{
			clear();
			_alloc = rhs._alloc;
			_key_comp = rhs._key_comp;
			_size = rhs._size;
			_tree = rhs._tree;
			return *this;
		}

		allocator_type get_allocator() const { return _alloc; }

		iterator begin() { return iterator(_tree.min(), _tree.getRoot()); }
		const_iterator begin() const { return const_iterator(_tree.min(), _tree.getRoot()); }
		iterator end() { return iterator(_tree.getNull(), _tree.getRoot()); }
		const_iterator end() const { return const_iterator(_tree.getNull(), _tree.getRoot()); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		T &at(const Key &key)
		{
			iterator it = find(key);
			if (find(key) == end())
				throw ::std::out_of_range("ft::map::at");
			return (find(key)->second);
		}

		const T &at(const Key &key) const { return at(key); }

		T &operator[](const key_type &x)
		{
			return ((insert(ft::make_pair(x, T()))).first)->second;
		}

		bool empty(void) const { return _tree.getRoot() == _tree.getNull(); }

		size_type size(void) const { return _tree.size(); }
		size_type max_size(void) const { return _tree.max_size(); }

		void clear(void) { _tree.emptyTree(); }

		ft::pair<iterator, bool> insert(const value_type &value)
		{
			iterator newPair = iterator(&_tree.insert(value), _tree.getRoot());
			return ft::pair<iterator, bool>(newPair, _tree.insertSucceed());
		}

		iterator insert(iterator pos, const value_type &value)
		{
			(void)pos;
			return iterator(&_tree.insert(value), _tree.getRoot());
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

		void erase(iterator pos)
		{
			if (pos != end())
				_tree.remove(*pos);
		}

		size_type erase(const key_type &key)
		{
			iterator it = find(key);
			if (it == end())
				return 0;
			erase(it);
			return 1;
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
			{
				iterator tmp = first;
				++tmp;
				erase(first);
				first = tmp;
			}
		}

		void swap(map &other)
		{
			value_compare val_comp = other._val_comp;
			allocator_type alloc = other._alloc;
			key_compare key_comp = other._key_comp;
			size_t size = other._size;

			other._val_comp = _val_comp;
			other._alloc = _alloc;
			other._key_comp = _key_comp;
			other._size = _size;

			_val_comp = val_comp;
			_alloc = alloc;
			_key_comp = key_comp;
			_size = size;
			_tree.swap(other._tree);
		}

		size_type count(const key_type &key) const
		{
			if (find(key) != end())
				return 1;
			return 0;
		}

		iterator find(const key_type &key)
		{
			value_type newPair = ft::make_pair(key, mapped_type());
			return iterator(_tree.search(newPair), _tree.getRoot());
		}

		const_iterator find(const key_type &key) const
		{
			value_type newPair = ft::make_pair(key, mapped_type());
			return const_iterator(_tree.search(newPair), _tree.getRoot());
		}

		ft::pair<iterator, iterator> equal_range(const key_type &key)
		{
			return ft::pair<iterator, iterator>(iterator(lower_bound(key)), iterator(upper_bound(key)));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const
		{
			return ft::pair<const_iterator, const_iterator>(const_iterator(lower_bound(key)), const_iterator(upper_bound(key)));
		}

		iterator lower_bound(const key_type &key)
		{
			iterator it = begin();
			iterator endit = end();

			while (it != endit)
			{
				if (!(_key_comp((*it).first, key)))
					return it;
				++it;
			}
			return endit;
		}

		const_iterator lower_bound(const key_type &key) const
		{
			const_iterator cit = begin();
			const_iterator cendit = end();

			while (cit != cendit)
			{
				if (!(_key_comp((*cit).first, key)))
					return cit;
				++cit;
			}
			return cendit;
		}

		iterator upper_bound(const key_type &key)
		{
			iterator it = begin();
			iterator endit = end();

			while (it != endit)
			{
				if ((_key_comp(key, (*it).first)))
					return it;
				++it;
			}
			return endit;
		}

		const_iterator upper_bound(const key_type &key) const
		{
			const_iterator cit = begin();
			const_iterator cendit = end();

			while (cit != cendit)
			{
				if ((_key_comp(key, (*cit).first)))
					return cit;
				++cit;
			}
			return cendit;
		}

		key_compare key_comp() const { return _key_comp; }
		value_compare value_comp() const { return _val_comp; }
	};

	template <class _Key, class _T, class Compare, class Alloc>
	bool operator==(const map<_Key, _T, Compare, Alloc> &lhs, const map<_Key, _T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class _Key, class _T, class Compare, class Alloc>
	bool operator<(const map<_Key, _T, Compare, Alloc> &lhs, const map<_Key, _T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs <= rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs > rhs || lhs == rhs);
	}

	template <class _Key, class _T, class Compare, class Alloc>
	void swap(map<_Key, _T, Compare, Alloc> &lhs, map<_Key, _T, Compare, Alloc> &rhs) { lhs.swap(rhs); }

}

#endif