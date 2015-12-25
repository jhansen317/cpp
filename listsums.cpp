#include<iostream>
#include<vector>
#include "quicksort.h"
#include <ctime>

using namespace std;


bool sumexists(vector<short> v, short result);


int main(void)
{
	srand(time(NULL)); 
	short checkme, temp; 
	vector<short> shortvec; 
	cout << "\nPlease enter a result to check against the numbers in vector: ";
	cin >> checkme;
	//shortvec = randShort(20);
	cout << "\nPlease Enter some numbers: "; 
	cin >> temp;
	while (!cin.fail())
	{
		shortvec.push_back(temp);
		cin >> temp; 
	}
	
	cout << "\nYour vector is: ";
	for (vector<short>::size_type i=0; i<shortvec.size(); i++)
	{
		cout << shortvec[i] << ' '; 
	}
	cout << '\n'; 
	
	if (sumexists(shortvec, checkme))
	{
		cout << "\nYes two numbers sum to " << checkme << '!';
	}
	else
	{
		cout << "\nNope, sorry."; 
	}
	
	return 0; 
}


bool sumexists(vector<short> v, short result)
{	
	short sum=0, i=0, p;
	bool returnval = false; 
	quicksort(v);
	while(sum < result && i < v.size())
	{
		p = i+1; 
		
		while(sum < result && p < v.size())
		{
			sum = v[i]+v[p]; 
			if (sum == result)
			{
				returnval = true; 
			}
			else
			{
				p++; 
			}
		}
		i++; 
	}	
	return returnval; 
}
