#ifndef QUICKSORT_H
#define QUICKSORT_H

#include<iostream>
#include<vector>
#include<string>
#include <cstdlib>     
#include <ctime>      
#include <cmath>
using namespace std;

const short CUTOFF = 5; 

bool doubleEql(const double lhs, const double rhs)
{
	return fabs(lhs-rhs) < 1e-6;
}


inline vector<short> randShort(vector<short>::size_type n)
{	
	vector<short> vec;
	vector<short>::size_type i;
	for (i=0; i < n; i++)
	{
		vec.push_back(static_cast<short>(rand()));
	}
	return vec;
}

template <class Comparable>

inline void swap2(Comparable & a, Comparable & b)
{
	Comparable c = a;	
	a = b;
	b = c;
	return; 
}

template <class Comparable, typename compSizeT>

void insertionSort(vector<Comparable> & a, compSizeT low, compSizeT high)
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


template <class Comparable, typename compSizeT>

void quicksort(vector<Comparable> & a, compSizeT low, compSizeT high)
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
			swap2(a[low], a[middle]);
		}
		if (a[high] < a[low])
		{
			swap2(a[low], a[high]);
		}
		if (a[high] < a[middle])
		{
			swap2(a[middle], a[high]);
		}

		Comparable pivot = a[middle];

		swap2(a[middle], a[high-1]);

		compSizeT i, j;
		
		for (i = low-1, j = high-1; ; )
		{
			while(a[++i] < pivot) { }  // find low

			while (pivot < a[--j]) { } // find high

			if (i < j)
			{
				swap2(a[i], a[j]);
			}
			else 
			{
				break;
			}			
		}
		swap2(a[i], a[high-1]);
		
		quicksort(a, low, i-1);
		quicksort(a, i+1, high);
	}
	return;
}

template <class Comparable>
void quicksort(vector<Comparable> & a)
{
	typename vector<Comparable>::size_type b=0;
	
	quicksort(a, b, a.size()-1);
	return;
}

#endif        

