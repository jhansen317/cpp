#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include "huge.h"

using namespace std;

int main(void)
{
    long convertee;
    huge test, addend, sum, difference, fromlong, divisor, multiplicand;
    vector<huge> hugevec;
    string word;
    cout << "\nLets try encoding a word as a vector of huges. Enter a word:";
    cin >> word;
    hugevec = strtohuge(word);

	cout << "Now the inverse...\n";
	word = hugetostr(hugevec);
	cout << "Word is: " << word;
    cout << '\n';
    /*for (vector<huge>::size_type i=0; i<hugevec.size(); i++)
    {
        cout << hugevec[i] << '\n';
    }
    cout << "\nHow bout printing one...";
    word = printWord(hugevec);
    //cout << word << '\n';
    cout << "\nPlease enter a number, no longer than 100 digits: ";   
    cin.clear(); 
    cin.ignore(INT_MAX,'\n'); 
    cin >> test;
    cout << "\nPlease enter another number, no longer than 20 digits: "; 
    cin >> addend;
    cout << "\nThe first number you entered was: " << test << " and the second"
         << " was " << addend << "\n";
    sum = test+addend;
    cout << "\nThe sum of those numbers is: " << sum << '\n';
    cout << "\nEnter a multiplicand: ";
    cin >> multiplicand;
    cout << "\nYou entered : " << multiplicand << "\n";
    sum = test * multiplicand;
    cout << multiplicand << " * " << test << " = " << sum << '\n';
    sum = test * addend;
    cout << "\nproduct of two huges test: " << test << " * " << addend << " = ";
    cout << sum << '\n';
    difference = sum - test;
    cout << "\nDifference test: " << sum << " - " << test << " = " << difference;
    test.append(5);
    cout << "\nAppend: test.append(appendee) = " << test;
    difference = sum - test;
    cout << "\nDifference test again: " << sum << " - " << test << " = " << difference;
    cout << "\nTrying decrement operator. Currently test = " << test;
    test--; 
    cout << "\nNow test = " << test;
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
    
    cout << "\nA greater than lhs: ";
    cin >> sum;
    cout << "\nGreater than rhs: ";
    cin >> divisor;
    if (sum > divisor)
    {
        cout << "\nLHS is greater than RHS";
    }
    else
    {
        cout << "\nRHS is greater than LHS";
    }
    cout << "\nA number to divide: ";
    cin >> sum;
    cout << "\nPlease enter a divisor: ";
    cin >> divisor;
    fromlong = sum/divisor;
    cout << "\nDivision test: " << sum << '/' << divisor << " = " << fromlong;
    //fromlong = sum % divisor;
    //cout << "\nModulo test: " << sum << '%' << divisor << " = " << fromlong; 
    */
    cout << '\n';
    
    
   
    return 0;
}
