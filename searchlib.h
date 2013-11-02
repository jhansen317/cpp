#ifndef SEARCHLIB_H
#define SEARCHLIB_H

#include<vector>

template <class Comparable>
typename std::vector<Comparable>::size_type linearSearch(
	                 const std::vector<Comparable> & a, const Comparable & x)
{
	typename std::vector<Comparable>::size_type i=0; 
	bool found=false;
	while (i < a.size() && !found)
	{
		if (a[i] == x)
		{
			found = true;
		}
		else
		{
			i++;
		}
	}
	return i; 
}

template <class Comparable>
typename std::vector<Comparable>::size_type binarySearch(
	             const std::vector<Comparable> & a, const Comparable & x)
{
	typename std::vector<Comparable>::size_type low = 0;
	typename std::vector<Comparable>::size_type high = a.size()-1;
	typename std::vector<Comparable>::size_type mid;
	while (low <= high)
	{
		mid = (low+high)/2;
		if (toLower(a[mid]) < toLower(x))
		{
			low = mid+1;
		}
		else if (toLower(a[mid]) > toLower(x))
		{
			high = mid-1;
		}
		else
		{
			return mid;
		}
	
	}
	return a.size(); 
}



#endif        

