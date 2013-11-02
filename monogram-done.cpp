#include <iostream>
#include <cctype>
#include <climits>


using namespace std;

int main(void)
{
   char first;
   char middle;
   char last;
   char t;

   cout << "\n\t\tThis program will help you rearrange your initials."
        << "\n\n\t\tIn other words, it will make a Monogram for you."
        << "\n\nPlease enter your initials :";

   cin >> first >> ws;
   
   if (cin.peek() == '.')
   {
      cin >> t >> middle >> ws;
   }
   else
   {
      cin >> middle >> ws;
   }
   if (cin.peek() == '.')
   {
      cin >> t >> last;
      cin.ignore(INT_MAX, '\n');
   }
   else
   {
      cin >> last;
      cin.ignore(INT_MAX, '\n');
   }
	
   cout <<"\nThank you very much for your diligent work."
        <<"\n\nYour monogram will be either: " 
        << static_cast<char>(toupper(middle)) << "." 
        << static_cast<char>(tolower(first)) << "." 
        << static_cast<char>(toupper(last)) << "."
        << "\n\nor:"
        << "\n                              " 
        << static_cast<char>(toupper(middle)) << " " 
        << static_cast<char>(toupper(last))
        << "\n                               " 
        << static_cast<char>(toupper(first))
        << "\n\nThank you for using the Monogram Program!\n\n";

   return 0;
}
