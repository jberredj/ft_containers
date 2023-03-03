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
 
		rbnode_t*	_search(rbnode_t* node, T key) const {
			if (key < node->key)
				return _search(node->getLeft(), key);
			else if (key > node->key)
				return _search(node->getRight(), key);
			if (_isLeaf(node))
				return NULL;
			return node;
		}

		void	_rotateSwapNode(rbnode_t* dest, rbnode_t* src) {
			if (_isRoot(dest->getParent()))
				_root = src;
			else if (_isLeftChild(dest))
				dest->getParent()->setLeft(src);
			else
				dest->getParent()->setRight(src);
		}

		void	_leftRotate(rbnode_t* x) {
			rbnode_t*	y = x->getRight();
			x->setRight(y->getLeft());  // 

			y->setParent(x->getParent());

			_rotateSwapNode(x, y);
			y->setLeft(x); 
		}

		void	_rightRotate(rbnode_t* y) {
			rbnode_t*	x = y->getLeft();
			y->setLeft(x->getRight());

			x->setParent(y->getParent());

			_rotateSwapNode(y, x);
			x->setRight(y); 
		}

		rbnode_t*	newRBNode(T Key) {
			rbnode_t	tmp(Key, &_null);
			rbnode_t*	newAddr = NULL;
			newAddr = _nalloc.allocate(1);
			_nalloc.construct(newAddr, tmp);
			return newAddr;
		}

		rbnode_t*	_insertFixup(rbnode_t* newNode) {
			while (newNode->getParent()->getColor() == ft::RED)
			{
				if (_isLeftChild(newNode->getParent())) {
					rbnode_t*	uncle = newNode->getUncle();
					if (uncle->getColor() == ft::RED) {
						newNode->getParent()->setColor(ft::BLACK);
						newNode->setColor(ft::BLACK);
						newNode->getGrandParent()->setColor(ft::RED);
						newNode = newNode->getGrandParent();
					}
					else  {
						if (_isRightChild(newNode)) {
							newNode = newNode->getParent();
							_leftRotate(newNode);
						}
						newNode->getParent()->setColor(ft::BLACK);
						newNode->getGrandParent()->setColor(ft::RED);
						_rightRotate(newNode->getGrandParent());
					}
				}
				else {
					rbnode_t*	uncle = newNode->getUncle();
					if (uncle->getColor() == ft::RED) {
						newNode->getParent()->setColor(ft::BLACK);
						newNode->setColor(ft::BLACK);
						newNode->getGrandParent()->setColor(ft::RED);
						newNode = newNode->getGrandParent();
					}
					else  {
						if (_isLeftChild(newNode)) {
							newNode = newNode->getParent();
							_rightRotate(newNode);
						}
						newNode->getParent()->setColor(ft::BLACK);
						newNode->getGrandParent()->setColor(ft::RED);
						_leftRotate(newNode->getGrandParent());
					}
				}
			}
			_root->setColor(ft::BLACK);
			return newNode;
		}

		rbnode_t*	_insert( T key) {
			rbnode_t*	parent = &_null;
			rbnode_t*	crawler = _root;
			while (_isNotLeaf(crawler))
			{
				parent = crawler;
				if (key < crawler->key)
					crawler = crawler->getLeft();
				else if (key > crawler->key)
					crawler = crawler->getRight();
				else
					return crawler;
			}
			rbnode_t*	newNode = newRBNode(key);
			if (_isNull(parent))
				_root = newNode;
			else if (key < parent->key)
				parent->setLeft(newNode);
			else
				parent->setRight(newNode);
			return	_insertFixup(newNode);
		}

	};
}

#endif