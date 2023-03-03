#ifndef _NODE_HPP
# define _NODE_HPP

namespace ft {
	enum nodeColor {RED = false, BLACK = true};

	template <class T>
	class RBNode {
	public:
		T			key;

		RBNode		():	key(T()), _color(BLACK), _left(this), _right(this), _parent(this), _isNotNull(false) {} // This constructor is only used by the leaf/null terminator

		RBNode		(T _key, RBNode* terminator): key(_key), _color(RED), _left(terminator), _right(terminator),
					_parent(terminator), _isNotNull(true) {}

		void	setColor(nodeColor newColor) {_color = newColor;}
		void	recolor(void) {_color = static_cast<nodeColor>(!_color);}
		void	setParent(RBNode *node) {_parent = node;}
		void	setLeft(RBNode *node) {
			_left = node;
			if (node->_isNotNull)
				node->setParent(this);
		}
		void	setRight(RBNode *node) {
			_right = node;
			if (node->_isNotNull)
				node->setParent(this);
		}


		void	setNull(bool value) {
			_isNotNull = !value;
			_color = static_cast<nodeColor>(value);
		}

		RBNode*		getLeft(void) {return _left;}
		RBNode*		getRight(void) {return _right;}
		RBNode*		getParent(void)	{return _parent;}
		RBNode*		getSibling(void) {
			if (_parent->_left == this)
				return _parent->_right;
			return _parent->_left;
		}
		RBNode*		getUncle(void) {return _parent->getSibling();}
		RBNode*		getGrandParent(void) {return _parent->_parent;}
		
		nodeColor	getColor(void) {return _color;}

	private:
		nodeColor	_color;
		RBNode*		_left;
		RBNode*		_right;
		RBNode*		_parent;
		bool		_isNotNull;
	};

	template <class T>
	bool	operator<(const RBNode<T>& lhs, const RBNode<T>& rhs) {return lhs.getKey() < rhs.getKey();}

	template <class T>
	bool	operator>(const RBNode<T>& lhs, const RBNode<T>& rhs) {return !(lhs < rhs);}

}

#endif