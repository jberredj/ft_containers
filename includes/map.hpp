#ifndef MAP_HPP
#define MAP_HPP
#include <functional>
#include <memory>
#include <cstddef>
#include "_rbt.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T>>>
	class map
	{
	private:
		typedef RBT<ft::pair<const Key, T>, Compare, Allocator::template rebind<T>::other> _tree_t;

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer pointer;
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

		size_t _size; // TODO: Since RBT allready track it's size, it is redundant
		_tree_t _tree;

	public:
		// the 2 first constructor are handled by this one
		map() : _val_comp(key_compare()), _alloc(allocator_type()), _key_comp(key_compare()),
				_size(0), _tree(_alloc, _key_comp) {}
		explicit map(const Compare &comp, const Allocator &alloc = Allocator()) : _val_comp(comp), _alloc(alloc), _key_comp(comp), _size(0), _tree(_alloc, _key_comp) {}

		template <class InputIt>
		map(InputIt first, InputIt last, const key_compare &key_comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _val_comp(key_comp), _alloc(alloc), _key_comp(key_comp), _size(0),
			  _tree(_alloc, _key_comp)
		{
			insert(first, last); // TODO: implement insert
		}
		map(const map<Key, T, Compare, Allocator> &other)
			: _val_comp(other._key_comp), _alloc(other._alloc),
			  _key_comp(other._key_comp), _size(other._size), _tree(other._tree) {}

		~map() { clear(); } // TODO: implement clear

		reference operator=(const reference rhs)
		{
			clear();
			_alloc = rhs._alloc;
			_key_comp = rhs._key_comp;
			_size = rhs._size;
			_tree = rhs._tree;
			return *this;
		}

		allocator_type get_allocator() const { return _alloc; }

		iterator begin() { return iterator(_tree.min()); }
		const_iterator begin() const { return const_iterator(_tree.min()); }
		iterator end() { return iterator(_tree.getNull()); }
		const_iterator end() const { return const_iterator(_tree.getNull()); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		T &at(const Key &key)
		{
			iterator it = find(key); // TODO: Implement find
			if (find(key) == end())
				throw ::std::out_of_range("ft::map::at");
			return (find(key)->second);
		}

		const T &at(const Key &key) const { return at(key); }

		T &operator[](const key_type &x)
		{
			return ((insert(ft::make_pair(x, T()))).first)->second;
		}

		bool empty(void) const {return _tree.getRoot() == _tree.getNull();}
		
		size_type	size(void) const {return _tree.size()}
		size_type	max_size(void) const {return _tree.max_size()}

		void clear(void) { _tree.emptyTree(); }
	};

}

#endif