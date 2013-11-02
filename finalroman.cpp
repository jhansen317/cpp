#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>
#include "digitConverter.h" 

using namespace std;

//string convertDigit(short place, short number, char one, char five, char ten);

short romanNumberReader(void);

void answerPrinter(string answer);

int main(void)
{
    short number;
    char yesno;
    string answer;
    
    srand(time(NULL));
    
    cout << "\n\tWelcome to the Roman Numeral Conversion Program\n";
    
    do
    {
    
    number = romanNumberReader();
    
    answer.insert(0, convertDigit(1, number, 'I', 'V', 'X'));
    answer.insert(0, convertDigit(10, number, 'X', 'L', 'C'));
    answer.insert(0, convertDigit(100, number, 'C', 'D', 'M'));
    answer.insert(0, convertDigit(1000, number, 'M', '\0', '\0'));
      
    answerPrinter(answer);
       
    answer.clear();
    
    cout << "\nWould you like to enter another number?  ";
    
    cin >> yesno;
    
    } while (toupper(yesno) == 'Y');
    
    return 0;
}

/*string convertDigit(short place, short number, char one, char five, char ten)
{
    
    string returnString;
    short i;
    
    returnString.clear();
    
    number = number/place % 10;
    
    if (number > 0 && number < 4 || number > 4 && number < 9 )
    {  
        for(i = 1; i <= number % 5; i++)
        {
        returnString.insert(returnString.begin(), one);
        }
       
        if (number >= 5 && number < 9)
        {                
            returnString.insert(returnString.begin(), five); 
        }
    }
    else if (number == 4)
    {                
        returnString.insert(returnString.begin(), five); 
        returnString.insert(returnString.begin(), one);
    }
    else if (number == 9)
    {                      
        returnString.insert(returnString.begin(), ten);
        returnString.insert(returnString.begin(), one);
    }
    
    return returnString;   
}*/

short romanNumberReader(void)
{
    short number;
    
    cout << "\nPlease enter the number you would like to convert  ";
    
    cin >> number;
    
    while (number < 1 || cin.fail() )
    {
        cin.clear();
        cout << "\nI'm sorry, that number is too small for Roman Civilization!"
             << "\nPlease try again.  ";
        cin.ignore(INT_MAX, '\n');
        cin >> number;
    }
    while (number > 3999 || cin.fail())
    {
        cin.clear();
        cout << "\nI'm sorry, that number is too large for Roman Civilization!"
             << "\nPlease try again.  ";
        cin.ignore(INT_MAX, '\n');
        cin >> number;
    }
    
    return number;
}

void answerPrinter(string answer)
{
    short choice;
     
    choice = rand() % 3 + 1;
    
    
    switch(choice)
	{
	    case 1:
	        cout << "\nThe Roman way to say it is " << answer << "\n";
	        break;	    
	    case 2:	    
	        cout << "\nI believe it's probably " << answer << "\n";
	        break;
	    case 3:	    
	        cout << "\nYou must mean " << answer << "\n";
	        break;
	}
}



