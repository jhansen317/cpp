#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include "huge.h"

using namespace std;

int main(void)
{
    long multiplicand, convertee;
    huge test, addend, sum, difference, fromlong, divisor;
    vector<huge> hugevec;
    string word;
    cout << "\nLets try encoding a word as a vector of huges. Enter a word:";
    cin >> word;
    hugevec = readWord(word);
    cout << '\n';
    for (vector<huge>::size_type i=0; i<hugevec.size(); i++)
    {
        cout << hugevec[i] << '\n';
    }
    cout << "\nHow bout printing one...";
    word = printWord(hugevec);
    cout << word << '\n';
    cout << "\nPlease enter a number, no longer than 100 digits: ";   
    cin >> test;
    cout << "\nPlease enter another number, no longer than 20 digits: "; 
    cin >> addend;
    cout << "\nThe first number you entered was: " << test << " and the second"
         << " was " << addend << "\n";
    sum = test+addend;
    cout << "\nThe sum of those numbers is: " << sum << '\n';
    cout << "\nEnter a multiplicand: ";
    cin >> multiplicand;
    sum = test * multiplicand;
    cout << '\n' << multiplicand << " * " << test << " = " << sum << '\n';
    sum = test * addend;
    cout << "\nproduct of two huges test: " << test << " * " << addend << " = ";
    cout << sum << '\n';
    difference = sum - test;
    cout << "\nDifference test: " << sum << " - " << test << " = " << difference;
    cout << "\nEnter a long number to turn into a huge: ";
    cin >> convertee;
    fromlong = convertee;
    cout << "\nThat long is now a huge: " << fromlong << '\n';
    if (fromlong > sum)
    {
        cout << '\n' << fromlong << " is greater than " << sum;
    }
    else
    {
        cout << '\n' << fromlong << " is less than " << sum;
    }
    cin.ignore(INT_MAX, '\n');
    cout << "\nA number to divide: ";
    cin >> sum;
    cout << "\nPlease enter a divisor: ";
    cin >> divisor;
    fromlong = sum/divisor;
    cout << "\nDivision test: " << sum << '/' << divisor << " = " << fromlong;
    fromlong = sum % divisor;
    cout << "\nModulo test: " << sum << '%' << divisor << " = " << fromlong; 
    
    cout << '\n';
    
    
   
    return 0;
}
