#ifndef _RBT_HPP
# define _RBT_HPP
# include <cstddef>
# include <iostream>
# ifdef BSTTEST
#  include <list>
# endif

namespace ft {
	enum nodeColor {RED, BLACK};

	template <class T>
	struct Node {
		T			key;
		nodeColor	color;
		Node<T>*	left;
		Node<T>*	right;
		Node<T>*	parent;
		Node		(T _key): key(_key), color(RED), left(NULL), right(NULL), parent(NULL) {}
	};

	template <class T>
	class RBT {
	private:
		Node<T>*	_root;

		Node<T>*	_insert(Node<T>* node, T key) {
			if (!node) {
				return new Node<T>(key);
			}
			if (key < node->key)
				node->left = _insert(node->left, key);
			else if (key > node->key)
				node->right = _insert(node->right, key);
			return node;
		}

		Node<T>*	_search(Node<T>* node, T key) const {
			if (!node)
				return node;
			if (key < node->key)
				return _search(node->left, key);
			else if (key > node->key)
				return _search(node->right, key);
			return node;
		}

		Node<T>*	_remove(Node<T>* node, T key) {
			if (!node)
				return NULL; // Falls on this case if a leaf is reached, which mean the key was not found on the traversal
			if (key < node->key)
				node->left = _remove(node->left, key);
			else if (key > node->key)
				node->right = _remove(node->left, key);
			if (!node->left) {
				Node<T>*	tmp = node->right;
				delete node;
				return tmp;
			} else if (!node->right) {
				Node<T>*	tmp = node->left;
				delete node;
				return tmp;
			}
			Node<T>*	tmp = _min(node->right);
			node->key = tmp->key;
			_remove(node->right, tmp->key);
		}

		Node<T>*	_min(Node<T>* node) const {
			if (node->left)
				return _min(node->left);
			return node;
		}

		Node<T>*	_max(Node<T>* node) const {
			if (node->right)
				return _min(node->right);
			return node;
		}

		void	_emptyTree(Node<T>* node) {
			if (!node)
				return;
			if (node->left)
				_emptyTree(node->left);
			if (node->right)
				_emptyTree(node->right);
			delete node;
		}

#ifdef BSTTEST
		void	_inorder_print(Node<T>* node) const {
			if (!node)
				return;
			_inorder_print(node->left);
			std::cout << node->key << " ";
			_inorder_print(node->right);
		}

		void	_inorder_list(Node<T>* node, std::list<Node<T>*>& lst) {
			if (node)
			{
				_inorder_list(node->left, lst);
				lst.push_back(node);
				_inorder_list(node->right, lst);
			}
		}
#endif

	public:
		RBT() : _root(NULL) {}
		~RBT() {
			_emptyTree(_root);
		}

		void insert(T key) {
			_root = _insert(_root, key);
		}

		Node<T>* search(T key) {
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

		std::list<Node<T>*> inorder_list(void) {
			std::list<Node<T>*> result;
			_inorder_list(_root, result);
			return result;
		}
#endif
	};
}

#endif