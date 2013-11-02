#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>

using namespace std;



int main(void)
{
    string onesplaces[] =  {"", "I", "II", "III", "IV", 
                            "V", "VI", "VII", "VIII", "IX"}; // or "IIIVIIIX"

    string tensplaces[] =  {"", "X", "XX", "XXX", "XL", 
                            "L", "LX", "LXX", "LXXX", "XC"}; // or "XXXLXXXC"

    string hundredsplaces[] = {"", "C", "CC", "CCC", "CD", 
                               "D", "DC", "DCC", "DCCC", "CM"}; // or "CCCDCCCM"

    string thousandsplaces[] = {"", "M", "MM", "MMM"};


    string answer;
    char yesno;
    short number; 
    short ones;
    short tens;
    short hundreds;
    short thousands;
    
    cout << "\n\tWelcome to the Roman Numeral Conversion Program.\n"
            "Would you like to start Converting?  ";
            
    cin >> yesno;
            
    cin.ignore(INT_MAX, '\n');
    
    while (toupper(yesno) == 'Y')
    {

        cout << "\n\nPlease enter the number you would like to convert!  ";
    
        cin >> number;
    
        if (number > 0 && number < 4000)
        {      
            ones = number % 10;
            tens = number/10 % 10;
            hundreds = number/100 % 10;
            thousands = number/1000 % 10; 
               
            if (number < 10)
            {             
                answer.append(onesplaces[ones]);
            }
            else if (number > 9 && number < 100)
            {
                answer.append(tensplaces[tens]);
                answer.append(onesplaces[ones]);
            }
            else if (number > 99 && number < 1000)
            {
                answer.append(hundredsplaces[hundreds]);
                answer.append(tensplaces[tens]);
                answer.append(onesplaces[ones]);            
            }
            else 
            {
                answer.append(thousandsplaces[thousands]);
                answer.append(hundredsplaces[hundreds]);
                answer.append(tensplaces[tens]);
                answer.append(onesplaces[ones]);
            }
        
            cout << "The Roman Numeral is: " << answer;
            
            answer.clear();
            
            cout << "\n\nWould you like to enter another number?  ";
            
            cin >> yesno;
            
            cin.ignore(INT_MAX, '\n');
        }
        else
        {
            cout << "The number is too big or too small for Roman civilization";
            
            cout << "\n\nWould you like to enter another number?  ";
            
            cin >> yesno;
            
            cin.ignore(INT_MAX, '\n');
        }
    }        
    
    cout << "\n\nThanks for using the program! Bye.\n\n";
    
    
    return 0;
}


                                                    
                                                   
