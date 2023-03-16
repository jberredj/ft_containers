#ifndef _MAP_ITERATOR_HPP
#define _MAP_ITERATOR_HPP
#include <memory>
#include <iterator> //  for std::bidirectional_iterator_tag
#include "_iterator.hpp"

namespace ft
{
	template <class T>
	class mapCIterator;
	template <class T>
	class mapIterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
	private:
		typedef ft::iterator<std::bidirectional_iterator_tag, typename T::value_type> _iterator;

	public:
		typedef mapIterator iterator_type;
		typedef typename _iterator::value_type value_type;
		typedef typename _iterator::difference_type difference_type;
		typedef typename _iterator::reference reference;
		typedef typename _iterator::pointer pointer;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T node_type;
		node_type *_pNode;
		node_type *_pRoot;

		mapIterator(void) : _pNode(NULL), _pRoot(NULL) {}
		mapIterator(node_type *node, node_type *root) : _pNode(node), _pRoot(root) {}
		mapIterator(const mapIterator &it) : _pNode(it._pNode), _pRoot(it._pRoot) {}
		~mapIterator(void) {}

		mapIterator &operator=(const mapIterator &rhs)
		{
			_pNode = rhs._pNode;
			_pRoot = rhs._pRoot;
			return *this;
		}

		reference operator*(void) const { return _pNode->key; }
		pointer operator->(void) const { return &(operator*()); }

		mapIterator &operator++(void)
		{
			_pNode = _pNode->successor();
			return *this;
		}
		mapIterator operator++(int)
		{
			mapIterator tmp = *this;
			++(*this);
			return tmp;
		}

		mapIterator &operator--(void)
		{
			if (_pNode->isNull())
				_pNode = _pRoot->max();
			else
				_pNode = _pNode->predecessor();
			return *this;
		}
		mapIterator operator--(int)
		{
			mapIterator tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator==(const mapIterator &rhs) const
		{
			return _pNode == rhs._pNode;
		}

		bool operator!=(const mapIterator &rhs) const
		{
			return !(*this == rhs);
		}

		operator mapCIterator<node_type>(void) { return (mapCIterator<node_type>(_pNode, _pRoot)); }
	};

	template <class T>
	class mapCIterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
	private:
		typedef ft::iterator<std::bidirectional_iterator_tag, typename T::value_type const> _iterator;

	public:
		typedef mapCIterator iterator_type;
		typedef typename _iterator::value_type value_type;
		typedef typename _iterator::difference_type difference_type;
		typedef typename _iterator::reference reference;
		typedef typename _iterator::pointer pointer;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T node_type;
		node_type const *_pNode;
		node_type const *_pRoot;

		mapCIterator(void) : _pNode(NULL), _pRoot(NULL) {}
		mapCIterator(const node_type *node, const node_type *root) : _pNode(node), _pRoot(root) {}
		mapCIterator(const mapIterator<node_type> &it) : _pNode(it._pNode), _pRoot(it._pRoot) {}
		mapCIterator(const mapCIterator &cit) : _pNode(cit._pNode), _pRoot(cit._pRoot) {}
		~mapCIterator(void) {}

		mapCIterator &operator=(const mapCIterator &rhs)
		{
			_pRoot = rhs._pRoot;
			_pNode = rhs._pNode;
			return *this;
		}

		reference operator*(void) const { return _pNode->key; }
		pointer operator->(void) const { return &(operator*()); }

		mapCIterator &operator++(void)
		{
			_pNode = _pNode->successor();
			return *this;
		}
		mapCIterator operator++(int)
		{
			mapCIterator tmp = *this;
			++(*this);
			return tmp;
		}

		mapCIterator &operator--(void)
		{
			if (_pNode->isNull())
				_pNode = _pRoot->max();
			else
				_pNode = _pNode->predecessor();
			return *this;
		}
		mapCIterator operator--(int)
		{
			mapCIterator tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator==(const mapCIterator &rhs) const
		{
			return _pNode == rhs._pNode;
		}

		bool operator!=(const mapCIterator &rhs) const
		{
			return !(*this == rhs);
		}
	};
}

#endif