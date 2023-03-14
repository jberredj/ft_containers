#ifndef STACK_HPP
# define STACK_HPP
# include "vector.hpp"
namespace ft {
	template <class T, class Container=ft::vector<T> >
	class stack {
	public: 
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		stack(const container_type& cntr = container_type()) : c(cntr) {}
		stack(const stack& src) : c(src.c) {}
		~stack(void) {}

		bool		empty() const { return c.empty(); }
		size_type	size() const { return c.size(); }
		reference top() { return c.back(); }
		const_reference top() const { return c.back(); }
		void push(const value_type& value) { c.push_back(value); }
		void pop(void) { c.pop_back(); }

		stack& operator=(const stack& src) {
			c =  src.c;
			return *this;
		}

		// Those operators are non-member, c is protected so friend is needed
		friend bool operator==(const stack& lhs, const stack& rhs) { return lhs.c == rhs.c; }
		friend bool operator<(const stack& lhs, const stack& rhs) { return lhs.c < rhs.c; }
		
	protected:
		container_type c;
	};
}

template <class T, class Container>
bool operator!=(const ft::stack<T, Container> &lhs,
				const ft::stack<T, Container> &rhs) { return !(lhs == rhs); }

template <class T, class Container>
bool operator<=(const ft::stack<T, Container> &lhs,
				const ft::stack<T, Container> &rhs) { return !(rhs < lhs); }

template <class T, class Container>
bool operator>(const ft::stack<T, Container> &lhs,
			const ft::stack<T, Container> &rhs) { return rhs < lhs; }

template <class T, class Container>
bool operator>=(const ft::stack<T, Container> &lhs,
				const ft::stack<T, Container> &rhs) { return !(lhs < rhs); }

#endif