#include <iostream>
#include <string>
#include <climits>
#include "date.h"

using namespace std;




int main(void)
{
    Date date1, date2;
    long incby;
    
  
    cout << "\nPlease Enter a first date (mm/dd/yyyy): ";
    cin >> date1;
    while (!date1.good())
    {
        if (date1.bad_days())
        {
            cout << "\nThere are too many days!!";
        }
        if (date1.bad_month())
        {
            cout << "\nInvalid Month!!";
        }
        if (date1.bad_year())
        {
            cout << "\nInvalid Year!!";
        }
        if (date1.bad_notation())
        {
            cout << "\nImproper Notation!!";
        }
        cout << "\nPlease Try again: ";
        date1.clear_flags();
        cin >> date1;
    }
    cout << "\nPlease Enter the second date (mm/dd/yyyy): ";
    cin >> date2; 
    while (!date2.good())
    {
        if (date2.bad_days())
        {
            cout << "\nThere are too many days!!";
        }
        if (date2.bad_month())
        {
            cout << "\nInvalid Month!!";
        }
        if (date2.bad_year())
        {
            cout << "\nInvalid Year!!";
        }
        if (date2.bad_notation())
        {
            cout << "\nImproper Notation!!";
        }
        cout << "\nPlease Try again: ";
        date2.clear_flags();
        cin >> date2;
    }
    cout << "\nThe first date you entered was: " << date1 << '\n';
    cout << "\nThe second date you entered was: " << date2 << '\n';
    cout << "\nThe difference between these two dates is " << date2 - date1 
         << " days.\n";
    if (date2 < date1)
    {
        cout << '\n' << date1 << " comes after " << date2 << '\n';
    }
    else
    {
        cout << '\n' << date2 << " comes after " << date1 << '\n';
    }
    cout << "\nBy how many days would you like to increment Date 1? ";
    cin >> incby;
    date1+=incby;
    while (!date1.good())
    {
        cout << "\nYou must have entered a bad amount of days to increment that"
             << " date by...Please try again: ";
        cin >> incby;
        date1+=incby;
    }
    cout << "\nOk, " << date1 << " plus " << incby 
         << " days is: " << date1 << '\n';
    
    return 0;
}


