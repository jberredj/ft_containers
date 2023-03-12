#ifndef _MAP_ITERATOR_HPP
# define _MAP_ITERATOR_HPP
# include <memory>
# include <iterator> //  for std::bidirectional_iterator_tag
# include "_iterator.hpp"


namespace ft
{
	template <class Value>
	class mapIterator : public ft::iterator<std::bidirectional_iterator_tag, Value> {
	private:
		typedef ft::iterator<std::bidirectional_iterator_tag, typename Value::value_type>	_iterator;
	public:
		typedef Value			node_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef typename _iterator::value_type	value_type;
		typedef typename _iterator::difference_type	difference_type;
		typedef typename _iterator::reference	reference;
		typedef typename _iterator::pointer	pointer;
		typedef const reference	const_reference;
		node_type*				_pNode;

		mapIterator(void): _pNode(NULL) {}
		mapIterator(node_type* node): _pNode(node) {}
		mapIterator(const_reference it): _pNode(it._pNode) {}
		~mapIterator(void) {}

	reference	operator=(const_reference rhs)
		{
			_pNode = rhs._pNode;
			return *this;
		}

		reference	operator*(void) const { return _pNode->key; }
		pointer		operator->(void) const { return &(operator*()); }
		
		reference	operator++(void)
		{
			_pNode = _pNode->successor();
			return *this;
		}
		mapIterator	operator++(int) 
		{
			mapIterator	tmp = *this;
			++(*this);
			return tmp;
		}

		reference	operator--(void)
		{
			_pNode = _pNode->predecessor();
			return *this;
		}
		mapIterator	operator--(int) 
		{
			mapIterator	tmp = *this;
			--(*this);
			return tmp;
		}

		bool	operator==(const_reference rhs) const
		{
			return _pNode == rhs._pNode;
		}
	};
}

#endif