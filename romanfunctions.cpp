#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>

using namespace std;

short read_number(void);

short extract_place(short number, short place);

void too_large(void);

void too_small(void);

bool go_on(void);

int main(void)
{
    string onesplaces[] =  {"", "I", "II", "III", "IV", 
                            "V", "VI", "VII", "VIII", "IX"}; // or "IIIVIIIX"  IVXLCDM

    string tensplaces[] =  {"", "X", "XX", "XXX", "XL", 
                            "L", "LX", "LXX", "LXXX", "XC"}; // or "XXXLXXXC"

    string hundredsplaces[] = {"", "C", "CC", "CCC", "CD", 
                               "D", "DC", "DCC", "DCCC", "CM"}; // or "CCCDCCCM"

    string thousandsplaces[] = {"", "M", "MM", "MMM"};


    string answer;
    short number;
    bool repeat;
    
    repeat = true;
    
    while (repeat == true)
    {

        number = read_number();
    
        if (number <= 0)
        {
            too_small();
            repeat = go_on();
        }
        else if (number > 3999)
        {
            too_large();
            repeat = go_on();
        }
        else
        {                         
            answer.append(thousandsplaces[extract_place(number, 1000)]);
            answer.append(hundredsplaces[extract_place(number, 100)]);
            answer.append(tensplaces[extract_place(number, 10)]);
            answer.append(onesplaces[extract_place(number, 1)]);
           
        
            cout << "The Roman Numeral is: " << answer;
            
            answer.clear();
            
            repeat = go_on();
        }
        
    }        
    
    cout << "\n\nThanks for using the program! Bye.\n\n";
    return 0;
}



    










void too_large(void)
{    
    cout << "\nI'm sorry, That number is too large for Roman Civilization";   
}

void too_small(void)
{      
    string message;
    
    message = string (40, '*');
    cout << message;   
}

short extract_place(short number, short place)
{
    return number/place % 10;
}


short read_number(void)
{
    short number;
    
    cout << "\nPlease Enter a number  ";
    
    cin >> number;
    
    return number;
}

bool go_on(void)
{
    char yesno;
    
    cout << "\n\nWould you like to enter another number?  ";
    
    cin >> yesno;
    
    cin.ignore(INT_MAX, '\n');
    
    if (toupper(yesno) == 'Y')
    {
        return true;
    }
    else
    {
        return false;
    }
}




