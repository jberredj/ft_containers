#ifndef STACK_HPP
# define STACK_HPP
# include <vector> // TODO: Remove include

namespace ft {
	template <class T, class Container=std::vector<T>> //TODO: Replace std with ft
	class stack {
	public: 
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		stack(const container_type& ctnr = container_type()) : c(cont) {}
		stack(const stack& src) : c(src.c) {}
		~stack(void) {}

		bool		empty() const { return c.empty(); }
		size_type	size() const { return c.size(); }
		reference& top() const { return c.back(); }
		const_reference& top() const { return c.back(); }
		void push(const value_type& value) { c.push_back(value); }
		void pop(void) { c.push_back(value); }

		stack& operator=(const stack& src) {
			c =  src.c;
			return *this;
		}
	protected:
		container_type c;
	}
}

template <class T, class Container>
bool	operator==(const stack<T, Container>& lhs, 
					const stack<T, Container>& rhs) { return lhs.c == rhs.c; }

template <class T, class Container>
bool	operator!=(const stack<T, Container>& lhs, 
					const stack<T, Container>& rhs) { return !(lhs == rhs); }

template <class T, class Container>
bool	operator<(const stack<T, Container>& lhs, 
					const stack<T, Container>& rhs) { return lhs.c < rhs.c; }

template <class T, class Container>
bool	operator<=(const stack<T, Container>& lhs, 
					const stack<T, Container>& rhs) { return !(lhs < rhs); }

template <class T, class Container>
bool	operator>(const stack<T, Container>& lhs, 
					const stack<T, Container>& rhs) { return rhs < lhs; }

template <class T, class Container>
bool	operator>=(const stack<T, Container>& lhs, 
					const stack<T, Container>& rhs) { return !(rhs < lhs); }


#endif