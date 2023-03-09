#ifndef _NODE_HPP
# define _NODE_HPP

namespace ft {
	enum nodeColor {RED = false, BLACK = true};
	template <class T>
	class RBNode {
	public:
		T			key;
		nodeColor	color;
		RBNode*		left;
		RBNode*		right;
		RBNode*		parent;

		RBNode		(): key(T()), color(BLACK), left(this), right(this), parent(this), _null(true) {} // This constructor is only used by the leaf/null terminator
		RBNode		(T _key, RBNode& nullNode): key(_key), color(RED), left(&nullNode), right(&nullNode),
					parent(&nullNode), _null(false) {}

		bool	isLeftChild(void) const { return parent->left == this; }
		bool	isRightChild(void) const { return parent->right == this; }
		bool	isLeftChildOf(RBNode& node) const { return node.left == this; }
		bool	isRightChildOf(RBNode& node) const { return node.right == this; }

		bool	isChildOf(RBNode& node) const { return isLeftChildOf(node) || isRightChildOf(node); }

		// All those functions are redundant, their meant to ease the code readability

		bool	isNotLeftChild(void) const { return parent->left != this;}
		bool	isNotRightChild(void) const { return parent->right != this;}
		bool	isNotLeftChildOf(RBNode& node) const { return node.left != this; }
		bool	isNotRightChildOf(RBNode& node) const { return node.right != this; }

		bool	leftChildIsLeaf(void) const { return left->_null; }
		bool	rightChildIsLeaf(void) const { return right->_null; }
		bool	leftChildIsNotLeaf(void) const { return !left->_null; }
		bool	rightChildIsNotLeaf(void) const { return !right->_null; }

		bool	isNull(void) const { return _null; }
		bool	isNotNull(void) const { return !_null; }
		bool	isLeaf(void) const { return _null; }
		bool	isNotLeaf(void) const {return !_null; }

		bool	isRoot(void) const { return parent->_null; }
		bool	isNotRoot(void) const { return !parent->_null; }
		
		bool	isRed(void) const { return !static_cast<bool>(color);}
		bool	isBlack(void) const { return !isRed(); }
		bool	isNotRed(void) const { return !isRed(); }
		bool	isNotBlack(void) const { return isRed(); }

		RBNode*	grandParent(void) const { return parent->parent; }
		RBNode*	sibling(void) const {
			if (isLeftChild())
				return parent->right;
			return parent->left;	
		}
		RBNode*	uncle(void) const { return parent->sibling(); }

		// left and right are public, those functions are used when function pointers are
		void		setLeft(RBNode *node) { left = node; }
		void		setRight(RBNode *node) { right = node; }
		RBNode*		getLeft(void) const {return left;}
		RBNode*		getRight(void) const {return right;}

	private:
		bool	_null;
	};

	template <class T>
	bool	operator<(const RBNode<T>& lhs, const RBNode<T>& rhs) {return lhs.getKey() < rhs.getKey();}

	template <class T>
	bool	operator>(const RBNode<T>& lhs, const RBNode<T>& rhs) {return !(lhs < rhs);}

}

#endif