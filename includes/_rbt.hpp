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
			_emptyTree(_root);
		}

		rbnode_t* insert(T key) {
			return _insert(key);
		}

		rbnode_t* search(T key) {
			_null.key = key;
			_search(_root, key);
		}

		void	remove(T key) {
			_root = _remove(_root, key);
		}

		void	emptyTree(void) {
			_emptyTree(_root);
		}
#ifdef BSTTEST
		void inorder_print(void) {
			_inorder_print(_root);
		}

		std::list<rbnode_t*> inorder_list(void) {
			std::list<rbnode_t*> result;
			_inorder_list(_root, result);
			return result;
		}
#endif

	private:
		typedef typename Allocator::template rebind< RBNode<T> >::other	_Node_alloc; // templated typedef would not work without ::template
		typedef															void(RBT::*rotateFuncP)(rbnode_t*);
		typedef															bool(RBT::*testFuncP)(rbnode_t*);
		typedef 														RBNode<T>*(RBNode<T>::*getFuncP)(void);
		typedef 														void(RBNode<T>::*setFuncP)(RBNode<T>*);
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

		void	_rotateOperation(rbnode_t* x, getFuncP getChild1, getFuncP getChild2,
					setFuncP setChild1, setFuncP setChild2) {
			rbnode_t*	y = (x->*getChild2)();
			(x->*setChild2)((y->*getChild1)());  // 

			y->setParent(x->getParent());

			_transplant(x, y);
			(y->*setChild1)(x);
		}

		void	_leftRotate(rbnode_t* x) {
			_rotateOperation(x, &RBNode<T>::getLeft, &RBNode<T>::getRight, &RBNode<T>::setLeft, &RBNode<T>::setRight);
		}

		void	_rightRotate(rbnode_t* y) {
			_rotateOperation(y, &RBNode<T>::getRight, &RBNode<T>::getLeft, &RBNode<T>::setRight, &RBNode<T>::setLeft);
		}

		void	_insertFixupOperation(rbnode_t* newNode, testFuncP isXChild,
					rotateFuncP rotateFunc1, rotateFuncP rotateFunc2) {
			rbnode_t*	uncle = newNode->getUncle();
			if (uncle->getColor() == ft::RED) {
				newNode->getParent()->setColor(ft::BLACK);
				newNode->setColor(ft::BLACK);
				newNode->getGrandParent()->setColor(ft::RED);
				newNode = newNode->getGrandParent();
			}
			else  {
				if ((this->*isXChild)(newNode)) {
					newNode = newNode->getParent();
					(this->*rotateFunc1)(newNode);
				}
				newNode->getParent()->setColor(ft::BLACK);
				newNode->getGrandParent()->setColor(ft::RED);
				(this->*rotateFunc2)(newNode->getGrandParent());
			}
		}

		rbnode_t*	_insertFixup(rbnode_t* newNode) {
			while (newNode->getParent()->getColor() == ft::RED)
			{
				if (_isLeftChild(newNode->getParent()))
					_insertFixupOperation(newNode, &RBT::_isRightChild, &RBT::_leftRotate, &RBT::_rightRotate);
				else
					_insertFixupOperation(newNode, &RBT::_isLeftChild, &RBT::_rightRotate, &RBT::_leftRotate);
			}
			_root->setColor(ft::BLACK);
			return newNode;
		}

		rbnode_t*	newRBNode(T Key) {
			rbnode_t	tmp(Key, &_null);
			rbnode_t*	newAddr = NULL;
			newAddr = _nalloc.allocate(1);
			_nalloc.construct(newAddr, tmp);
			return newAddr;
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

		void		_transplant(rbnode_t* dest, rbnode_t* src) {
			if (_isRoot(dest->getParent()))
				_root = src;
			else if (_isLeftChild(dest))
				dest->getParent()->setLeft(src);
			else
				dest->getParent()->setRight(src);
			// src->setParent(dest->getParent());
		}

		void	_removeFixup(rbnode_t* transplantedNode) {
			while (!_isRoot(transplantedNode) && transplantedNode->getColor() != ft::BLACK) {
				if (_isLeftChild(transplantedNode)) {
					rbnode_t*	sibling = transplantedNode->getSibling();
					if (sibling->getColor() == ft::RED) {
						sibling->setColor(ft::BLACK);
						transplantedNode->getParent()->setColor(ft::RED);
						_leftRotate(transplantedNode->getParent());
						sibling = transplantedNode->getParent()->getRight();
					}
					if (sibling->getLeft()->getColor() == ft::BLACK && sibling->getRight()->getColor() == ft::BLACK) {
						sibling->setColor(ft::RED);
						transplantedNode = transplantedNode->getParent();
					}
					else {
						if (sibling->getRight()->getColor() == ft::BLACK) {
							sibling->getLeft()->setColor(ft::BLACK);
							sibling->setColor(ft::RED);
							_rightRotate(sibling);
							sibling = sibling->getParent()->getRight();
						}
						sibling->setColor(transplantedNode->getParent()->getColor());
						transplantedNode->getParent()->setColor(ft::BLACK);
						sibling->getRight()->setColor(ft::BLACK);
						_leftRotate(transplantedNode->getParent());
						transplantedNode = _root;
					}
				}
				else {
					rbnode_t*	sibling = transplantedNode->getSibling();
					if (sibling->getColor() == ft::RED) {
						sibling->setColor(ft::BLACK);
						transplantedNode->getParent()->setColor(ft::RED);
						_rightRotate(transplantedNode->getParent());
						sibling = transplantedNode->getParent()->getLeft();
					}
					if (sibling->getRight()->getColor() == ft::BLACK && sibling->getLeft()->getColor() == ft::BLACK) {
						sibling->setColor(ft::RED);
						transplantedNode = transplantedNode->getParent();
					}
					else {
						if (sibling->getLeft()->getColor() == ft::BLACK) {
							sibling->getRight()->setColor(ft::BLACK);
							sibling->setColor(ft::RED);
							_leftRotate(sibling);
							sibling = sibling->getParent()->getLeft();
						}
						sibling->setColor(transplantedNode->getParent()->getColor());
						transplantedNode->getParent()->setColor(ft::BLACK);
						sibling->getLeft()->setColor(ft::BLACK);
						_RightRotate(transplantedNode->getParent());
						transplantedNode = _root;
					}
				}
			}
			transplantedNode->setColor(ft::BLACK);
		}

		void	_remove(rbnode_t* toDelete) {
			rbnode_t*	nearestGreaterNode = toDelete;
			nodeColor	ogColor = toDelete->getColor();
			rbnode_t*	transplantedNode = &_null;

			if (_leftIsLeaf(toDelete)) {
				transplantedNode = toDelete->getRight();
				_transplant(toDelete, transplantedNode);
			}
			else if (_rightIsLeaf(toDelete)) {
				transplantedNode = toDelete->getLeft();
				_transplant(toDelete, transplantedNode);
			}
			else {
				nearestGreaterNode = _min(toDelete->getRight());
				ogColor = nearestGreaterNode->getColor();
				transplantedNode = nearestGreaterNode->getRight();
				if (nearestGreaterNode->getParent() == toDelete)
					transplantedNode->setParent(nearestGreaterNode);
				else {
					_transplant(nearestGreaterNode, transplantedNode);
					nearestGreaterNode->setRight(transplantedNode);
				}
				_transplant(toDelete, nearestGreaterNode);
				nearestGreaterNode->setLeft(toDelete->getLeft());
				nearestGreaterNode->setColor(toDelete->getColor());
			}
			if (ogColor == ft::BLACK)
				_removeFixup(transplantedNode);
			_nalloc.destroy(toDelete);
			_nalloc.deallocate(toDelete, 1);
			_null.setParent(&_null); 
		}

		void	_remove(T key) {
			rbnode_t*	toDelete = _search(_root, key);
			if (toDelete)
				_remove(toDelete);
		}

		rbnode_t*	_min(rbnode_t* node) const {
			if (!_leftIsLeaf(node))
				return _min(node->getLeft());
			return node;
		}

		rbnode_t*	_max(rbnode_t* node) const {
			if (!_rightIsLeaf(node))
				return _min(node->getRight());
			return node;
		}

		void	_emptyTree(rbnode_t* node) {
			if (_isLeaf(node))
				return;
			if (!_leftIsLeaf(node))
				_emptyTree(node->getLeft());
			if (!_rightIsLeaf(node))
				_emptyTree(node->getRight());
			_nalloc.destroy(node);
			_nalloc.deallocate(node, 1);
		}

#ifdef BSTTEST
		void	_inorder_print(rbnode_t* node) const {
			if (_isLeaf(node))
				return;
			_inorder_print(node->getLeft());
			std::cout << node->key << " ";
			_inorder_print(node->getRight());
		}

		void	_inorder_list(rbnode_t* node, std::list<rbnode_t*>& lst) {
			if (_isLeaf(node))
				return ;
			_inorder_list(node->getLeft(), lst);
			lst.push_back(node);
			_inorder_list(node->getRight(), lst);
		}
#endif

	};
}

#endif