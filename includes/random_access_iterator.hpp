#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP
#include <memory>
#include <iterator> //  for std::bidirectional_iterator_tag
#include "_iterator.hpp"

namespace ft
{
	template <class T>
	class random_access_iterator : public ft::iterator<random_access_iterator_tag, T>
	{
	private:
		typedef ft::iterator<std::random_access_iterator_tag, typename T::value_type> _iterator;
		T *_value;

	public:
		typedef random_access_iterator iterator_type;
		typedef typename _iterator::value_type value_type;
		typedef typename _iterator::difference_type difference_type;
		typedef typename _iterator::reference reference;
		typedef typename _iterator::pointer pointer;
		typedef std::random_access_iterator_tag iterator_category;

		random_access_iterator(void) : _value(NULL) {}
		random_access_iterator(const T *value) : _value(value) {}
		random_access_iterator(const iterator_type &it) : _value(it._value) {}
		~random_access_iterator(void) {}

		iterator_type &operator=(const iterator_type &rhs)
		{
			_value = rhs._value;
			return *this;
		}

		reference operator*(void) const { return *_value; }
		pointer operator->(void) const { return _value; }

		iterator_type &operator++(void)
		{
			_value++;
			return *this;
		}
		iterator_type operator++(int)
		{
			iterator_type tmp = *this;
			++(*this);
			return tmp;
		}

		iterator_type &operator--(void)
		{
			_value--;
			return *this;
		}
		iterator_type operator--(int)
		{
			iterator_type tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator==(const iterator_type &rhs) const { return _value == rhs._value; }
		bool operator!=(const iterator_type &rhs) const { return !(*this == rhs); }
		T &operator[](const difference_type offset) { return (*(*this + offset)); };
		const T &operator[](const difference_type offset) const { return (*(*this + offset)); };

		iterator_type operator+(difference_type offset) const
		{
			return static_cast<iterator_type>(_value + offset);
		}

		iterator_type operator-(difference_type offset) const
		{
			return static_cast<iterator_type>(_value - offset);
		}
		difference_type operator-(const iterator_type &rhs) const { return (_value - rhs._value); }

		bool operator<(const iterator_type &rhs) const { return _value < rhs._value; }
		bool operator<=(const iterator_type &rhs) const { return !(rhs < *this); }
		bool operator>(const iterator_type &rhs) const { return rhs < *this; }
		bool operator>=(const iterator_type &rhs) const { return !(*this < rhs); }

		iterator_type &operator+=(const difference_type offset)
		{
			_value += offset;
			return *this;
		}

		iterator_type &operator-=(const difference_type offset)
		{
			_value -= offset;
			return *this;
		}

		operator cRandom_access_iterator<T>(void) { return (cRandom_access_iterator<T>(_value)); }
	};

	template <class T>
	class cRandom_access_iterator : public ft::iterator<random_access_iterator_tag, T>
	{
	private:
		typedef ft::iterator<std::random_access_iterator_tag, typename T::value_type> _iterator;
		T *_value;

	public:
		typedef cRandom_access_iterator iterator_type;
		typedef typename _iterator::value_type value_type;
		typedef typename _iterator::difference_type difference_type;
		typedef typename _iterator::reference reference;
		typedef typename _iterator::pointer pointer;
		typedef std::random_access_iterator_tag iterator_category;

		cRandom_access_iterator(void) : _value(NULL) {}
		cRandom_access_iterator(const T *value) : _value(value) {}
		cRandom_access_iterator(const iterator_type &it) : _value(it._value) {}
		cRandom_access_iterator(const random_access_iterator &it) : _value(it._value) {}
		~cRandom_access_iterator(void) {}

		iterator_type &operator=(const iterator_type &rhs)
		{
			_value = rhs._value;
			return *this;
		}

		reference operator*(void) const { return *_value; }
		pointer operator->(void) const { return _value; }

		iterator_type &operator++(void)
		{
			_value++;
			return *this;
		}
		iterator_type operator++(int)
		{
			iterator_type tmp = *this;
			++(*this);
			return tmp;
		}

		iterator_type &operator--(void)
		{
			_value--;
			return *this;
		}
		iterator_type operator--(int)
		{
			iterator_type tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator==(const iterator_type &rhs) const { return _value == rhs._value; }
		bool operator!=(const iterator_type &rhs) const { return !(*this == rhs); }
		T &operator[](const difference_type offset) { return (*(*this + offset)); };
		const T &operator[](const difference_type offset) const { return (*(*this + offset)); };

		iterator_type operator+(difference_type offset) const
		{
			return static_cast<iterator_type>(_value + offset);
		}

		iterator_type operator-(difference_type offset) const
		{
			return static_cast<iterator_type>(_value - offset);
		}
		difference_type operator-(const iterator_type &rhs) const { return (_value - rhs._value); }

		bool operator<(const iterator_type &rhs) const { return _value < rhs._value; }
		bool operator<=(const iterator_type &rhs) const { return !(rhs < *this); }
		bool operator>(const iterator_type &rhs) const { return rhs < *this; }
		bool operator>=(const iterator_type &rhs) const { return !(*this < rhs); }

		iterator_type &operator+=(const difference_type offset)
		{
			_value += offset;
			return *this;
		}

		iterator_type &operator-=(const difference_type offset)
		{
			_value -= offset;
			return *this;
		}

	};
}
#endif