#include <iostream>
#include <cctype>
#include <climits>
#include <cmath>
#include <string>

using namespace std;

double midpointCalc(double point_a, double point_b);

   
double distanceCalc(double xa, double xb, double ya, double yb);

   
int main(void)
{
    const char holder = 'x'; // inputs
          double xa;     
          double ya;
          double xb;
          double yb;
          char t;
          bool errmes1 = false;
          bool errmes2 = false;
          bool errmes3 = false;
          char yes_no;
          double midx;  // outputs
          double midy;
          double distance;
        
          
        
    cout << "\n\tThis here is the Midpoint and Distance Calculation Program.\n\n"
         << "Would you like to start entering coordinates?  ";
        
    cin >> yes_no;
   
    cin.ignore(INT_MAX, '\n');

    while ( toupper(yes_no) == 'Y' )
    {
        errmes1 = false;
        errmes2 = false;
        errmes3 = false;
           
        cout << "\n\tExcellent. \n\nPlease enter the first point: ";
           
        cin >> ws; // get whitespace
           
        t = cin.peek();        //find out what's after whitespace
      
        if (!isdigit(t) &&   // if its not a number or a + or - 
               t != '-' &&
               t != '+')
        {                 
            cin >> t;            // then we'll take it 
        }
        else
        {
            t = holder;  // if a number has been entered fill t up with a value
            errmes1 = true; // turn on condition for error message later 
        }
      
        cin >> xa;       // then actually read the number
         
        cin >> ws;    // repeat 
           
        t = cin.peek();
      
        if (!isdigit(t) && t != '-' && t != '+')
        {                 
            cin >> t;
        }
        else
        {
            t = holder;
            errmes2 = true;
        }
      
        cin >> ya;
      
        while (cin.peek() != '\n' && isspace(cin.peek()))
        {
            cin.ignore();
        }
        if (cin.peek() != '\n')
        {
            cin >> t;
        }
        else
        {
            t = holder;
            errmes3 = true;
        }
           
        if (errmes1 == true)
        {
            cerr << "\nDon't forget your opening parenthesis!\n"; 
        }
           
        if (errmes2 == true)
        {            
            cerr << "\nDon't forget the comma between x and y values!\n";
        }
           
        if (errmes3 == true)
        {
            cerr << "\nDon't forget your closing parenthesis!\n";
        }
           
        errmes1 = false;  // reset error message switches
        errmes2 = false;
        errmes3 = false;
   
        cout << "\nPlease Enter the second Point:  ";

        cin >> ws;
           
        t = cin.peek();
      
        if (!isdigit(t) && t != '-' && t != '+')
        {                 
            cin >> t;
        }
        else
        {
            t = holder;
            errmes1 = true;
        }
      
        cin >> xb; 
         
        cin >> ws;
           
        t = cin.peek();
      
        if (!isdigit(t) && t != '-' && t != '+')
        {                  
            cin >> t;
        }
        else
        {
            t = holder;
            errmes2 = true;
        }
      
        cin >> yb;
      
        while (cin.peek() != '\n' && isspace(cin.peek()))
        {
            cin.ignore();
        }
        if (cin.peek() != '\n')
        {
            cin >> t;
        }
        else
        {
            t = holder;
            errmes3 = true;
        }
           
        if (errmes1 == true)
        {
            cerr << "\nDon't forget your opening parenthesis!\n"; 
        }
           
        if (errmes2 == true)
        {
            cerr << "\nDon't forget the comma between x and y values!\n";
        }
           
        if (errmes3 == true)
        {
            cerr << "\nDon't forget your closing parenthesis!\n";
        }
           
           
        midx = midpointCalc(xa, xb);
        midy = midpointCalc(ya, yb);
        distance = distanceCalc(xa, xb, ya, yb);
           

        cout << "\nThe line segment connecting points "
             << "(" << xa << ", " << ya << ")"
             << " and (" << xb << ", " << yb << ") is: "
             << distance << " units long.\n\nThe midpoint is: "
             << "(" << midx << ", " << midy << ").\n\n"
             << "Would you like to enter another set of points?  ";
   
        cin >> yes_no;
   
        cin.ignore(INT_MAX, '\n');  
    }
   
    cout << "\nOkay, then. See ya.\n\n";
   
    return 0;
}


double midpointCalc(double point_a, double point_b)
   {
      return (point_a + point_b)/2;
   }

double distanceCalc(double xa, double xb, 
                double ya, double yb)
   {                    
      return sqrt(pow((xa-xb), 2) + pow((ya-yb), 2));
   }
   
