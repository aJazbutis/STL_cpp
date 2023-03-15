#ifndef PMERGEME_HPP
#define PMERGEME_HPP

# include <iostream>
# include <set>
# include <vector>
# include <deque>
# include <cctype>
# include <climits>
# include <stdlib.h>
# include <ctime>
# include <sys/time.h>

#define DIGITS "0123456789"
#define K 5

int		toPositiveInt(std::string s);
std::string	trim(std::string &s, char const *c);
std::time_t		getTime(void);

template <class T>
void	printOut(T &c)	{
	typename T::const_iterator	it;
	for (it = c.begin(); it != c.end(); it++)	{
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

template <class T>
void swap(T &a, T &b)	{
	T	t;
	t = a;
	a = b;
	b = t;
}

/*just for vector & deque
	the one that also handles list in sorting_.hpp*/
template <class T>
void	insertionSort(T &c)	{
	typename T::iterator i1, i2;
	for (i1 = c.begin() + 1; i1 != c.end(); i1++)	{
		if (*i1 < *(i1 - 1))	{
			int x = *i1;
			i2 = i1;
			while (i2 != c.begin() && x < *(i2 - 1))	{
				*i2 = *(i2 - 1);
				i2--;
			}
			*i2 = x;
		}
	}
}

template <class T>
void  merge(T &c, int l, int m, int r)	{
	int n1 = m - l + 1;
	int n2 = r -m;
	T L(n1);
	T R(n2);
	
	for (int i = 0; i < n1; i++)	{
		L[i] = c[l + i];
	} 
	for (int i = 0; i < n2; i++)	{
		R[i] = c[m + 1 + i];
	}
	int i = 0, j = 0, k = l;
	while (i < n1 && j < n2)	{
		if (L[i] <= R[j])
			c[k++] = L[i++];
		else
			c[k++] = R[j++];
	}			
	while (i < n1)	{
		c[k++] = L[i++];
	}
	while (i < n2)	{
		c[k++] = R[j++];
	}
}

template <class T>
std::time_t mergeInsertionSort(T &c, int l, int r)	{
	std::time_t t = getTime();
	if (r - l > K)	{
		int m = l + (r - l) / 2;
		mergeInsertionSort(c, l, m);
		mergeInsertionSort(c, m + 1, r);
		merge(c, l, m, r);
	} else	{
		insertionSort(c);
	}
	return (getTime() - t);
}

#endif
