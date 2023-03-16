#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;
		T1 first;
		T2 second;

		pair() : first(T1()), second(T2()) {}
		pair(const T1 &_first, const T2 &_second) : first(_first), second(_second) {}
		template <class U, class V>
		pair(const pair<U, V> &p) : first(p.first), second(p.second) {}
	};

	template <class T1, class T2, class U1, class U2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2, class U1, class U2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2, class U1, class U2>
	bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
	{
		return lhs.first < rhs.first ||
			   (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2, class U1, class U2>
	bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2, class U1, class U2>
	bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2, class U1, class U2>
	bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	ft::pair<T1, T2> make_pair(const T1 &first, const T2 &second)
	{
		return pair<T1, T2>(first, second);
	}
}

#endif