#ifndef SORTLIB_H
#define SORTLIB_H

#include<iostream>
#include<vector>
#include<string>
#include <cstdlib>     
#include <ctime>      
#include <cmath>

const short CUTOFF = 5; 

bool doubleEql(const double lhs, const double rhs)
{
	return fabs(lhs-rhs) < 1e-6;
}


inline std::vector<short> randShort(std::vector<short>::size_type n)
{	
	std::vector<short> vec;
	std::vector<short>::size_type i;
	for (i=0; i < n; i++)
	{
		vec.push_back(static_cast<short>(rand()));
	}
	return vec;
}

template <class Comparable>

inline void swap(Comparable & a, Comparable & b)
{
	Comparable c = a;	
	a = b;
	b = c;
	return; 
}

/*******************************************************************************
*                            INSERTION SORT                                    *
*******************************************************************************/

template <class Comparable, typename compSizeT>

void insertionSort(std::vector<Comparable> & a, compSizeT low, compSizeT high)
{
	for (compSizeT p = low; p <= high; p++)
	{
		Comparable tmp = a[p];
		compSizeT j;
		
		for (j = p; j > low && tmp < a[j-1]; j--)
		{
			a[j] = a[j-1];
		}
		a[j] = tmp;
	}
	return;
}


/*******************************************************************************
*                               SHELLSORT                                      *
*******************************************************************************/
template <class Comparable>

void shellsort(std::vector<Comparable> & a)
{
	for (typename std::vector<Comparable>::size_type gap = a.size()/2; gap > 0; 
		gap = gap == 2 ? 1 : static_cast<typename std::vector<Comparable>::size_type >(gap/2.2))
	{
		for (typename std::vector<Comparable>::size_type  i = gap; i < a.size(); i++)
		{
			Comparable tmp = a[i]; 
			typename std::vector<Comparable>::size_type j = i;
			
			for( ; j >= gap && tmp < a[j-gap]; j-= gap)
			{
				a[j] = a[j-gap];
			}
			a[j] = tmp;
		}
	}
}


/*******************************************************************************
*                               QUICKSORT                                      *
*******************************************************************************/
template <class Comparable, typename compSizeT>

void quicksort(std::vector<Comparable> & a, compSizeT low, compSizeT high)
{
	if (low + CUTOFF > high)
	{
		insertionSort(a, low, high);
	}
	else
	{
		compSizeT middle = (low+high)/2;
		
		if (a[middle] < a[low])
		{
			swap(a[low], a[middle]);
		}
		if (a[high] < a[low])
		{
			swap(a[low], a[high]);
		}
		if (a[high] < a[middle])
		{
			swap(a[middle], a[high]);
		}

		Comparable pivot = a[middle];

		swap(a[middle], a[high-1]);

		compSizeT i, j;
		
		for (i = low-1, j = high-1; ; )
		{
			while(a[++i] < pivot) { }  // find low

			while (pivot < a[--j]) { } // find high

			if (i < j)
			{
				swap(a[i], a[j]);
			}
			else 
			{
				break;
			}			
		}
		swap(a[i], a[high-1]);
		
		quicksort(a, low, i-1);
		quicksort(a, i+1, high);
	}
	return;
}

template <class Comparable>
void quicksort(std::vector<Comparable> & a)
{
	typename std::vector<Comparable>::size_type b=0;
	
	quicksort(a, b, a.size()-1);
	return;
}

#endif        

