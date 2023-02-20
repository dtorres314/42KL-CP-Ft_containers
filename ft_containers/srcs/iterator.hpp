/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:22:27 by schuah            #+#    #+#             */
/*   Updated: 2023/02/20 18:39:14 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "type_traits.hpp"

/**
 * https://en.cppreference.com/w/cpp/iterator/iterator_traits
 * https://en.cppreference.com/w/cpp/iterator/reverse_iterator
 */
namespace ft
{
	/* Base member types */
	template <class Iter> struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	/* T* specialization member types */
	template <class T> struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	/* const T* specialization member types */
	template <class T> struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef const T*							pointer;
		typedef const T&							reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	/* Reverse_iterator class */
	template <class Iter>
	class reverse_iterator : public std::iterator<
		typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type,
		typename iterator_traits<Iter>::difference_type,
		typename iterator_traits<Iter>::pointer,
		typename iterator_traits<Iter>::reference>
	{
		public:
			/* Member types */
			typedef Iter												iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;

			/* Default constructor */
			reverse_iterator() {};

			/* Initialization constructor */
			explicit	reverse_iterator(iterator_type x) : current(x) {};

			/* Copy constructor */
			template <class U>
			reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {};

			/* Copy assignation operator */
			reverse_iterator	&operator=(const reverse_iterator& other)
			{
				if (this == &other)
					return (*this);
				this->current = other.current;
				return (*this);
			};
			
			/* Base member function. Accesses the underlying iterator */
			iterator_type	base() const
			{
				return (this->current);
			};

			/* Accesses the pointed-to element */
			reference operator*() const
			{
				Iter tmp = current;
				return (*(--tmp));
			};

			pointer	operator->() const
			{
				return (&(this->operator*()));
			};
		
			/* Accesses an element by index */
			reference	operator[](difference_type n) const
			{
				return (this->base()[-n - 1]);
			};

			/* Advances or decrements the iterator */
			reverse_iterator&	operator++()
			{
				current--;
				return (*this);
			};

			reverse_iterator&	operator--()
			{
				current++;
				return (*this);
			};

			reverse_iterator	operator++(int)
			{
				return (reverse_iterator(current--));
			};


			reverse_iterator	operator--(int)
			{
				return (reverse_iterator(current++));
			};

			reverse_iterator	operator+(difference_type n) const
			{
				return (reverse_iterator(current - n));
			};

			reverse_iterator	operator-(difference_type n) const
			{
				return (reverse_iterator(current + n));
			};

			reverse_iterator	operator+=(difference_type n)
			{
				current -= n;
				return (*this);
			};

			reverse_iterator	operator-=(difference_type n)
			{
				current += n;
				return (*this);
			};

		protected:
			/* Protected member variables */
			Iter	current;
	};

	/* Compares the underlying iterators */
	template <class Iterator1, class Iterator2>
	bool	operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	/* Advances the iterator */
	template <class Iterator>
	reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
	{
		return (reverse_iterator<Iterator>(it.base() - n));
	}

	/* Computes the distance between two iterator adaptors */
	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type	operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif
