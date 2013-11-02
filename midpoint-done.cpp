#include <iostream>

using namespace std;

int main(void)
{  
   double xa;
   double ya;
   double xb;
   double yb;
   char c; 
   double midx;
   double midy;
   
   cout << "\n\t\tWelcome to the Midpoint Calculation Program!\n\n"
        << "To ensure accurate calculation, please enter the coordinates as: "
        << "(x, y)\n\n"
        << "Please Enter the first Point:"; 
   
   cin >> c >> xa >> c >> ya >> c;
   
   cout << "\nPlease Enter the second Point:";

   cin >> c >> xb >> c >> yb >> c;
   
   midx = (xa+xb)/2;
   midy = (ya+yb)/2;
   
   cout << "\nThe midpoint of the line segment bewteen "
        << "(" << xa << ", " << ya << ") and (" << xb << ", " << yb << ") "
        << "is (" << midx << ", " << midy << ")."
        << "\n\n\tThank you!\n\n";
   
   return 0;
}
