#include <cstring>
#include <iostream>
#include <climits>
#include "strextra.h"

const short ARR_MAX = 50;



int main(void)
{
    char searchstr[ARR_MAX], subsearch[ARR_MAX];
    char c, answer;
    short pos = 0, start; 
    do {    
        cout << "\n\tWelcome to the find() driver.\nPlease Enter a string: ";
    
        get_line(searchstr, ARR_MAX); 
    
        cout << "\nPlease enter the char you'd like to find: ";
    
        cin >> c;
        
        cout << "\nWould you like to specify a starting position? ";
        cin >> answer; 
        cin.ignore(INT_MAX, '\n');
        if (toupper(answer) == 'Y')
        {
            cout << "\nOk, enter the starting position: ";
            cin >> start; 
            pos = find(searchstr, c, start); 
        }
        else
        {
            pos = find(searchstr, c);
        }
        if (pos == -1)
        {
            cout << "\nCharacter not found!";
        }
        else
        {
            cout << "\nCharacter found at position: " << pos;
        }
        
        cout << "\n\nPlease Enter a substring you'd like to find: ";
        
        get_line(subsearch, ARR_MAX); 
        
        cout << "\nWould you like to specify a starting position? ";
        cin >> answer; 
        cin.ignore(INT_MAX, '\n');
        if (toupper(answer) == 'Y')
        {
            cout << "\nOk, enter the starting position: ";
            cin >> start; 
            pos = find(searchstr, subsearch, start);
        }
        else
        {
            pos = find(searchstr, subsearch);
        }
        if (pos == -1)
        {
            cout << "\nSubstring not found!";
        }
        else
        {
            cout << "\nSubstring found starting at position: " << pos << "\n";
        }
        
        cout << "\nWould you like to try again? "; 
        cin >> answer;
        cin.ignore(INT_MAX, '\n');
        
    } while (toupper(answer) == 'Y');
    
    cout << "\nGoodbye.\n";   
    return 0;
}





