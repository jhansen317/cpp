#include "dublist.h"
#include <iostream>
#include <cstddef>
#include <climits>

using namespace std;

int main(void)
{

    doublelist dlist, dlist2;
       
    cout << "\nDynamic list of Doubles!\n"; 
    
    /*cout << "\nWhat size do you want your list to be? ";
    
    cin >> size;
    
    cout << "\nOk, a list of size: " << size;
    
    dlist = doublelist(size);*/
       
    cout << "\nEnter a bunch of doubles! ";
    
    cin >> dlist;
    
    cout << "\nThe Current number of filled spots in dlist is: " 
         << dlist.get_size();
    
    cout << "\nThe Last number in dlist is: " << dlist.get_last();
    
    cout << "\nDeleting last number in dlist - the size is: ";
    
    dlist.delete_last();
    
    cout << dlist.get_size() 
         << "\nThe last number in dlist is now: " << dlist.get_last();

    cout << "\nThe whole dlist is: " << dlist;  

    
    cout << "\n[] operator test: calling dlist[6]:\n";
    
    cout << "\ndlist[6] is: " << dlist[6] << '\n';
    
    cout << "\nTrying dlist[6] = 3.5";
    
    dlist[6] = 3.5;
    
    cout << "\ndlist[6] is now: " << dlist[6];
    
    cout << "\nEnter a bunch of doubles! ";
    
    cin >> dlist2;
   
    cout << "\ndlist2 is: " << dlist2 << '\n';
    
    
    cout << "\nCopying dlist into dlist2...";
    
    dlist2 = dlist;
    
    cout << "\ndlist2 is now: " << dlist2 << '\n';
    
    
    cout << "\n\nBye!";
    return 0;
}
