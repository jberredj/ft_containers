#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include <cstddef>
# include <memory>
# include "_iterator.hpp"

namespace ft {

	template< class Iter >
	class reverse_iterator: public
		ft::iterator<typename iterator_traits<Iter>::iterator_category,
					typename iterator_traits<Iter>::value_type,
					typename iterator_traits<Iter>::difference_type,
					typename iterator_traits<Iter>::pointer,
					typename iterator_traits<Iter>::reference>
	{
	protected:
		Iter current;
	public: 
		typedef Iter	iterator_type;

		reverse_iterator():current() {}
		explicit reverse_iterator(iterator_type x):current(x) {}
		template <class U>
		reverse_iterator(const reverse_iterator<U>& other):current(other.base()) {}

		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& other )
		{
			current = other.base()
			return *this;
		}

		iterator_type base() const { return current; }

		reference operator*() const
		{
			Iterator tmp = current;
			return *--tmp;
		}
		pointer operator->() const { return std::addressof(operator*()); } //TODO: I don't know if we are allowed to use std::addressof

		reference operator[](difference_type n) const
		{
			return current[-n - 1];
		}

		reverse_iterator& operator++()
		{
			--current;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--current;
			return tmp;
		}

		reverse_iterator& operator--()
		{
			++current;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++current;
			return tmp;
		}
		
		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(current - n);
		}
		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(current + n);
		}

		reverse_iterator& operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}
		reverse_iterator& operator-=(difference_type n)
		{
			current += n;
			return *this;
		}
	};

	template <class Iterator1, class Iterator2>
	bool    operator==(const reverse_iterator<Iterator1> & lhs,
						const reverse_iterator<Iterator2> & rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs,
					const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() != rhs.base();
	}
			
	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs,
					const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs,
					const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() >= rhs.base();
	}
	
	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs,
					const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs,
					const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() <= rhs.base();
	}
			
	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return rhs.base() - lhs.base();
	}
			
	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
		const reverse_iterator<Iter>& lhs)
	{
		return reverse_iterator<Iter> (lhs.base() - n);
	}

}

#endif