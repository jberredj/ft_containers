#ifndef _RBT_HPP
# define _RBT_HPP
# include "_node.hpp"
# include <cstddef>
# include <iostream>
# include <memory>
# ifdef BSTTEST
#  include <list>
# endif

namespace ft {
	template
    <typename T, class Compare = std::less<T>, class Allocator = std::allocator< RBNode<T> > >
	class RBT {
	public:
		typedef T						value_type;
		typedef Allocator				allocator_type;
		typedef RBNode<value_type>		rbnode_t;
		
		RBT() : _root(&_null), _null(RBNode<T>()) {}
		~RBT() {
		}

	private:
		typedef typename Allocator::template rebind< RBNode<T> >::other	_Node_alloc; // templated typedef would not work without ::template
		allocator_type													_alloc;
		_Node_alloc														_nalloc;
		rbnode_t*														_root;
		rbnode_t														_null;

		// Function to ease RBT operation function reading, some could be replaced by '!function()', but that would make the code harder to read

		bool		_isLeaf(rbnode_t* node) {return node == &_null;}
		bool		_isNotLeaf(rbnode_t* node) {return !_isLeaf(node);}
		bool		_leftIsLeaf(rbnode_t* node) {return _isLeaf(node->getLeft());}
		bool		_leftIsNotLeaf(rbnode_t* node) {return !_leftIsLeaf(node);}
		bool		_rightIsLeaf(rbnode_t* node) {return _isLeaf(node->getRight());}
		bool		_rightIsNotLeaf(rbnode_t* node) {return !_rightIsLeaf(node);}
		bool		_isRoot(rbnode_t* node) {return node == &_null;}
		bool		_isNull(rbnode_t* node) {return node == &_null;}
		bool		_isLeftChild(rbnode_t* node) {return (!_isRoot(node) && (node == node->getParent()->getLeft()));}
		bool		_isRightChild(rbnode_t* node) {return !_isLeftChild(node);}
 
	};
}

#endif