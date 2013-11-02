#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include "phraselib.h"

using namespace std;

int main(void)
{
    char choice, borderchar;
    phraseBox pbox; 
    string filename;
    ifstream infile;
    ofstream outfile;

    do 
    {
        cout << "\nPlease choose from the menu: "
         << "\n1. Read from keyboard and write to screen"
         << "\n2. Read from keyboard and write to file"
         << "\n3. Read from file and write to screen"
         << "\n4. Read from file and write to file"
         << "\n5. Quit\n";
         cin >> choice;
         cin.ignore(INT_MAX, '\n');
            if (choice == '1')
            {
                cout << "\nEnter the border character: ";
                cin >> borderchar;
                cin.ignore(INT_MAX, '\n');
                pbox.set_border(borderchar);
                cout << "\nEnter a phrase: ";
                cin >> pbox;                
                cout << "\nYour phrase looks like this:\n";
                pbox.set_alignment('L');
                cout << pbox; 
                pbox.set_alignment('R');
                cout << pbox;
                pbox.set_alignment('C');
                cout << pbox;
                cout << "\nWould you like to continue? ";
                cin >> choice;
                cin.ignore(INT_MAX, '\n');
                pbox.reset();
            }
        else if (choice == '2')
        {
            cout << "\nEnter the border character: ";
            cin >> borderchar;
            cin.ignore(INT_MAX, '\n');
            pbox.set_border(borderchar);
            cout << "\nEnter the output file name:  ";
            getline(cin, filename);
            outfile.open(filename.c_str());    
            while (!outfile)  
            {
                outfile.close();  
                outfile.clear();  
                cout << "Invalid output file name!" << endl;
        
                cout << "Enter the output file name:  ";
                getline(cin, filename);
        
                outfile.open(filename.c_str());
            }
           
            cout << "\nEnter your phrase: ";
            cin >> pbox;
            pbox.set_alignment('L');
            outfile << pbox; 
            pbox.set_alignment('R');
            outfile << pbox;
            pbox.set_alignment('C');
            outfile << pbox;
            outfile.close();
            outfile.clear();
            cout << "\nOutput file written successfully!";
            cout << "\nWould you like to continue? ";
            cin >> choice;
            cin.ignore(INT_MAX, '\n');
            pbox.reset();
            
        }
        else if (choice == '3')
        {
            cout << "\nEnter the border character: ";
            cin >> borderchar;
            cin.ignore(INT_MAX, '\n');
            pbox.set_border(borderchar);
            cout << "\nEnter the input file name:  ";
            getline(cin, filename);
            infile.open(filename.c_str());               
            while (!infile)   
            {
                infile.close();  
                infile.clear();  
        
                cout << "File Not Found!" << endl;
        
                cout << "Input file name:  ";
                getline(cin, filename);
        
                infile.open(filename.c_str());
            }
            infile >> pbox;
            infile.close();
            infile.clear();
            cout << "\nYour phrase looks like this:\n";
            pbox.set_alignment('L');
            cout << pbox; 
            pbox.set_alignment('R');
            cout << pbox;
            pbox.set_alignment('C');
            cout << pbox;
            cout << "\nWould you like to continue? ";
            cin >> choice;
            cin.ignore(INT_MAX, '\n');
            pbox.reset();
           
        }
        else if (choice == '4')
        {
            cout << "\nEnter the border character: ";
            cin >> borderchar;
            cin.ignore(INT_MAX, '\n');
            pbox.set_border(borderchar);
            cout << "\nEnter the input file name:  ";
            getline(cin, filename);
            infile.open(filename.c_str());               
            while (!infile)   
            {
                infile.close();  
                infile.clear();  
        
                cout << "File Not Found!" << endl;
        
                cout << "Input file name:  ";
                getline(cin, filename);
                infile.open(filename.c_str());
            }
            cin.clear();
            infile >> pbox;
            infile.close();
            infile.clear();
            cout << "\nFile read successfully! Enter the output file name:  ";
            getline(cin, filename);
            outfile.open(filename.c_str());    
            while (!outfile)  
            {
                outfile.close();  
                outfile.clear();  
                cout << "Invalid output file name!" << endl;
        
                cout << "Enter the output file name:  ";
                getline(cin, filename);
        
                outfile.open(filename.c_str());
            }
            pbox.set_alignment('L');
            outfile << pbox; 
            pbox.set_alignment('R');
            outfile << pbox;
            pbox.set_alignment('C');
            outfile << pbox;
            outfile.close();
            outfile.clear();
            cout << "\nFile written successfully!";
            cout << "\nWould you like to continue? ";
            cin >> choice;
            cin.ignore(INT_MAX, '\n');
            pbox.reset();
         } 
    } while (toupper(choice) == 'Y');
    
    cout << "\nThanks for using the phrase-boxer!\n";
    
    return 0;
}


