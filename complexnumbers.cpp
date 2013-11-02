#include <iostream>
#include <cctype>
#include <climits>
#include <cstring>
#include "person.h"

using namespace std;

int main(void)
{
    complexNum firstnumber, secondnumber;
    char yesno, choice;
 
    cout << "\n\tWelcome to the Complex Number Calculator!!!";
    
    do
    {   
        yesno = 'n';
        cout << "\nHow would you like to proceed?"
             << "\n1. (P)rint sum, difference, product, and quotient of two"
             << " complex numbers."
             << "\n2. (E)nter in your own expression."
             << "\n3. (F)ind the magnitude and conjugate of a complex number."
             << "\n4. (Q)uit\n";
             
        cin >> choice;
        cin.ignore(INT_MAX, '\n');
    
        if (toupper(choice) == 'P' || choice == '1')
        {
            cout << "\nPlease enter the first complex number:  ";    
            while( !firstnumber.read())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "\nInvalid notation! Please try again!\n";
                cout << "\nPlease enter the first complex number:  ";
            }
                    
            cout << "\nPlease enter the second complex number:  ";        
            while( !secondnumber.read())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "\nInvalid notation! Please try again!\n";
                cout << "\nPlease enter the second complex number:  ";
            }
            
            cout << "\nYou entered: ";
            firstnumber.print();
            cout << " and ";
            secondnumber.print();
            
            cout << "\n\nSum: ";
            firstnumber.plus(secondnumber).print();
            
            cout << "\nDifference: ";           
            firstnumber.minus(secondnumber).print();
            
            cout << "\nProduct: ";
            firstnumber.mult_by(secondnumber).print();
            
            cout << "\nQuotient: ";           
            firstnumber.div_by(secondnumber).print();
                        
            cout << "\nWould you like to continue?  ";
            cin >> yesno;
        }
        if (toupper(choice) == 'E' || choice == '2')
        {
            cout << "\nSupported operators are '+', '-', '*', and '/'."
                 << "\nPlease enter an expression in the form a+bi + c+di:";
                 
            while (!firstnumber.read_expr())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "\nInvalid notation! Please try again."
                     << "\nEnter an expression in the form a+bi + c+di: "; 
            }
            
            cout << "\nThe answer is: ";
            firstnumber.print();
            
            cout << "\nWould you like to continue?  ";
            cin >> yesno;
            cin.ignore(INT_MAX, '\n');
        }
        if (toupper(choice) == 'F' || choice == '3')
        {
            cout << "\nPlease enter a complex number:  ";         
            firstnumber.read();
            
            cout << "\nThe magnitude of ";           
            firstnumber.print();            
            cout << " is " << firstnumber.mag();
            
            cout << "\nThe conjugate is ";            
            firstnumber.conj().print(); 
            
            cout << "\nWould you like to continue?  ";
            cin >> yesno;
            cin.ignore(INT_MAX, '\n');
        }
    } while (toupper(yesno) == 'Y');
    
    cout << "\nGoodbye!\n\n";
    
    return 0;
}
