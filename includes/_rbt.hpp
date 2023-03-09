#ifndef _RBT_HPP
#define _RBT_HPP
#include "_node.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#ifdef BSTTEST
#include <exception>
#include <list>
#endif

namespace ft
{
	template <typename T, class Compare = std::less<T>, class Allocator = std::allocator<RBNode<T> > >
	class RBT
	{
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef RBNode<value_type> rbnode_t;

		RBT() : _root(&_null), _null(RBNode<T>()) {}
		~RBT()
		{
			_emptyTree(_root);
		}

		rbnode_t& insert(T key)
		{
			return _insert(key);
		}

		rbnode_t* search(T key)
		{
			_null.key = key;
			return _search(_root);
		}

		void remove(T key)
		{
			_remove(_root, key);
		}

		void emptyTree(void)
		{
			_emptyTree(_root);
		}
#ifdef BSTTEST
		void inorder_print(void)
		{
			_inorder_print(_root);
		}

		std::list<rbnode_t *> inorder_list(void)
		{
			std::list<rbnode_t *> result;
			_inorder_list(_root, result);
			return result;
		}

#endif

	private:
		typedef typename Allocator::template rebind<RBNode<T> >::other _Node_alloc; // templated typedef would not work without ::template
		typedef void (RBT::*rotateFuncP)(rbnode_t &);
		typedef bool (RBNode<T>::*testFuncP)(void) const;
		typedef RBNode<T> *(RBNode<T>::*getFuncP)(void) const;
		typedef void (RBNode<T>::*setFuncP)(RBNode<T> *);
		allocator_type _alloc;
		_Node_alloc _nalloc;
		rbnode_t *_root;
		rbnode_t _null;

		rbnode_t *_search(rbnode_t* node) const
		{
			while (node->key != _null.key)
			{
				if (_null.key < node->key)
					node = node->left;
				else
					node = node->right;
			}
			if (node->isNull())
				return NULL;
			return node;
		}

		// Based on leftRotate implementation, by default Child1 is Left
		// We use function pointer to avoid duplicate code (it sometimes matter to me, sometimes not)
		void _rotateOperation(rbnode_t& x, getFuncP getChild1, getFuncP getChild2,
							  setFuncP setChild1, setFuncP setChild2)
		{
			rbnode_t& y = *(x.*getChild2)();
			(x.*setChild2)((y.*getChild1)()); //
			if ((y.*getChild1)()->isNotLeaf())
				(y.*getChild1)()->parent = &x;
			y.parent = x.parent;
			if (x.isRoot())
				_root = &y;
			else if (x.isLeftChild())
				x.parent->left = &y;
			else
				x.parent->right =&y;
			(y.*setChild1)(&x);
			x.parent = &y;
		}

		void _leftRotate(rbnode_t& x)
		{
			_rotateOperation(x, &RBNode<T>::getLeft, &RBNode<T>::getRight, &RBNode<T>::setLeft, &RBNode<T>::setRight);
		}

		void _rightRotate(rbnode_t& y)
		{
			_rotateOperation(y, &RBNode<T>::getRight, &RBNode<T>::getLeft, &RBNode<T>::setRight, &RBNode<T>::setLeft);
		}

		// Same "optimisation" as for RotateOperation
		rbnode_t* _insertFixupOperation(rbnode_t *newNode, testFuncP isXChild,
								   rotateFuncP rotateFunc1, rotateFuncP rotateFunc2)
		{
			rbnode_t *uncle = newNode->uncle();
			if (uncle->isRed())
			{
				newNode->parent->color = ft::BLACK;
				uncle->color = ft::BLACK;
				newNode->grandParent()->color = ft::RED;
				newNode = newNode->grandParent();
			}
			else
			{
				if ((newNode->*isXChild)())
				{
					newNode = newNode->parent;
					(this->*rotateFunc1)(*newNode);
				}
				newNode->parent->color = ft::BLACK;
				newNode->grandParent()->color = ft::RED;
				(this->*rotateFunc2)(*newNode->grandParent());
			}
			return newNode;
		}

		void _insertFixup(rbnode_t *newNode)
		{
			while (newNode->parent->isRed())
			{
				if (newNode->parent->isLeftChild())
					newNode = _insertFixupOperation(newNode, &RBNode<T>::isRightChild, &RBT::_leftRotate, &RBT::_rightRotate);
				else
					newNode = _insertFixupOperation(newNode, &RBNode<T>::isLeftChild, &RBT::_rightRotate, &RBT::_leftRotate);
			}
			_root->color = ft::BLACK;
		}

		rbnode_t* newRBNode(T Key)
		{
			rbnode_t tmp(Key, _null);
			rbnode_t *newAddr = NULL;
			newAddr = _nalloc.allocate(1);
			_nalloc.construct(newAddr, tmp);
			return newAddr;
		}

		// newNode is alloc after the search here, intro to algo provide a node to insert to this function instead of a 
		// key value. I did this change to prevent useless alloc/destroy.
		rbnode_t& _insert(T key)
		{
			rbnode_t*	parent = &_null;
			rbnode_t*	crawler = _root;
			while (crawler->isNotLeaf())
			{
				parent = crawler;
				if (key < crawler->key)
					crawler = crawler->left;
				else if (key > crawler->key)
					crawler = crawler->right;
				else
					return *crawler; // This return is not in Intro to Algo, it prevent duplicate insert.
			}
			rbnode_t* newNode = newRBNode(key);
			newNode->parent = parent;
			if (parent->isNull())
				_root = newNode;
			else if (key < parent->key)
				parent->left = newNode;
			else
				parent->right = newNode;
			_insertFixup(newNode);
			return *newNode;
		}

		void _transplant(rbnode_t *dest, rbnode_t *src)
		{
			if (dest->isRoot())
				_root = src;
			else if (dest->isLeftChild())
				dest->parent->left = src;
			else
				dest->parent->right = src;
			src->parent = dest->parent;
		}

		rbnode_t*	_removeFixupOperation(rbnode_t* transplantedNode, rotateFuncP rotateFunc1, rotateFuncP rotateFunc2,
			getFuncP getChild1, getFuncP getChild2)
		{
			rbnode_t*	sibling = transplantedNode->getSibling();
			if (sibling->isRed()) {
				sibling->color = ft::BLACK;
				transplantedNode->parent->color = ft::RED;
				(this->*rotateFunc1)(transplantedNode->parent);
				sibling = (transplantedNode->parent->*getChild2)(); // transplantedNode->sibling() might work TODO: Test this
			}
			if ((sibling->*getChild1)()->isBlack() && (sibling->*getChild2)()->isBlack()) {
				sibling->color = ft::RED;
				transplantedNode = transplantedNode->parent;
			}
			else {
				if (sibling->right->isBlack()) {
					sibling->left->color = ft::BLACK;
					sibling->color = ft::RED;
					(this->*rotateFunc2)(sibling);
					sibling = (transplantedNode->parent->*getChild2)(); // transplantedNode->sibling() might work TODO: Test this
				}
				sibling->color = transplantedNode->parent->color;
				transplantedNode->parent->color = ft::BLACK;
				(sibling->*getChild2)()->color = ft::BLACK;
				(this->*rotateFunc1)(transplantedNode->parent);
				transplantedNode = _root;
			}
			return transplantedNode;
	}

		void	_removeFixup(rbnode_t* transplantedNode) {
			while (transplantedNode->isNotRoot() && transplantedNode->isBlack()) {
				if (transplantedNode->isLeftChild()) {
					transplantedNode = _removeFixupOperation(transplantedNode, &RBT::_leftRotate, &RBT::_rightRotate,
						&RBNode<T>::getLeft, &RBNode<T>::getRight);
				}
				else {
					transplantedNode = _removeFixupOperation(transplantedNode, &RBT::_rightRotate, &RBT::_leftRotate,
						&RBNode<T>::getRight, &RBNode<T>::getLeft);
				}
			}
			transplantedNode->setColor(ft::BLACK);
		}

		void _remove(rbnode_t *toDelete)
		{
			rbnode_t *nearestGreaterNode = toDelete;
			nodeColor ogColor = toDelete->color;
			rbnode_t *transplantedNode = &_null;

			if (toDelete->leftChildIsLeaf())
			{
				transplantedNode = toDelete->right;
				_transplant(toDelete, transplantedNode);
			}
			else if (toDelete->rightChildIsLeaf())
			{
				transplantedNode = toDelete->left;
				_transplant(toDelete, transplantedNode);
			}
			else
			{
				nearestGreaterNode = _min(toDelete->right);
				ogColor = nearestGreaterNode->color;
				transplantedNode = nearestGreaterNode->right;
				if (nearestGreaterNode->getParent == toDelete) // nearestGreaterNode.isChildOf(toDelete) might work TODO: Test this
					transplantedNode->parent = nearestGreaterNode;
				else
				{
					_transplant(nearestGreaterNode, transplantedNode);
					nearestGreaterNode->right = toDelete->right;
					nearestGreaterNode->right->parent = nearestGreaterNode;
				}
				_transplant(toDelete, nearestGreaterNode);
				nearestGreaterNode->left = toDelete->left;
				nearestGreaterNode->left->parent = nearestGreaterNode;
				nearestGreaterNode->color = toDelete->color;
			}
			if (ogColor == ft::BLACK)
				_removeFixup(transplantedNode);
			_nalloc.destroy(toDelete);
			_nalloc.deallocate(toDelete, 1);
			_null.setParent(&_null);
		}

		void _remove(T key)
		{
			_null.key = key;
			rbnode_t *toDelete = _search(_root);
			if (toDelete)
				_remove(toDelete);
		}

		rbnode_t *_min(rbnode_t *node) const
		{
			if (node->leftChildIsNotLeaf())
				return _min(node->left);
			return node;
		}

		rbnode_t *_max(rbnode_t *node) const
		{
			if (node->rightChildIsNotLeaf())
				return _min(node->right);
			return node;
		}

		void _emptyTree(rbnode_t *node)
		{
			if (node->isLeaf())
				return;
			if (node->leftChildIsNotLeaf())
				_emptyTree(node->left);
			if (node->rightChildIsNotLeaf())
				_emptyTree(node->right);
			_nalloc.destroy(node);
			_nalloc.deallocate(node, 1);
		}

#ifdef BSTTEST
		void _inorder_print(rbnode_t *node) const
		{
			if (node->isLeaf())
				return;
			_inorder_print(node->left);
			std::cout << node->key << (static_cast<bool>(node->color) ? "B" : "R") << " ";
			_inorder_print(node->right);
		}

		void _inorder_list(rbnode_t *node, std::list<rbnode_t *> &lst)
		{
			if (node->isLeaf())
				return;
			_inorder_list(node->left, lst);
			lst.push_back(node);
			_inorder_list(node->right, lst);
		}


#endif
	};
}

#endif
