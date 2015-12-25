#ifndef FILE_TO_VEC_H
#define FILE_TO_VEC_H
#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include <typeinfo>


template <class fileType>
void file_to_vec(std::istream & in, std::vector<fileType> & v)
{
	//std::vector<std::string> v;
	fileType data;
	in >> data;
	in.peek();
	while(!in.eof())
	{
		v.push_back(data);
		in.ignore(INT_MAX, '\n');
		in >> data;
		in.peek();
	}
	return; 
	
}


template <class fileType>
void vec_to_file(std::ostream & out, std::vector<fileType> & v)
{
	typename std::vector<fileType>::size_type i=0;
	while (i < v.size())
	{
		out << v[i] << '\n'; 
		i++;
	}
	return; 
}

#endif        

