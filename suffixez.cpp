#include <iostream>
#include <climits>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

string rand_mess_gen(short choice);

int main(void)
{
    long number;
    short ones_place, tens_place, num;
    char yes_no;
    string suffix;
    
    srand(time(NULL));
    
    cout << "\nWelcome to the ordinal number suffix program!\n"
            "Would you like to enter a number?  ";
            
    cin >> yes_no;
    
    while (toupper(yes_no) == 'Y')
    {
        cout << "\n\nPlease enter a number:  ";
    
        cin >> number;
    
        ones_place = number % 10;
    
        tens_place = number/10 % 10;
   
        if (tens_place == 1)
        {
            suffix = "th";
        }
        else if (ones_place == 1)
        {
            suffix = "st";
        }
        else if (ones_place == 2)
        {
            suffix = "nd";
        }
        else if (ones_place == 3)
        {
            suffix = "rd";
        }
        else 
        {
            suffix = "th";
        }
        
        num = rand() % 5 + 1;
    
    
        cout << rand_mess_gen(num) << number << suffix << "\n\n"
                "Would you like to enter another number?  ";
                
        cin >> yes_no;
    
        cin.ignore(INT_MAX, '\n');
        
    }
    
    cout << "Thanks, Bye!\n\n";
        
    
    
    
    return 0;
}

string rand_mess_gen(short choice)
{
    string message;
    
    switch(choice)
    {
    case 1:
        message = "\nThe answer you're looking for is ";
        break;
    case 2: 
        message = "\nThe the correct suffix appended is ";
        break;
    case 3:
        message = "\nI believe that would be ";
        break;
    case 4:
        message = "\nSomething tells me that it's ";
        break;
    case 5:
        message = "\nI couldn't possibly think of another way to say ";
        break;
    }
    
    return message;
}
