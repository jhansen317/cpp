#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<climits>
#include<ctime>
#include "markov.h"

using namespace std;

int main(void)
{
    srand(time(NULL));
    char choice;
    ifstream infile;
    ifstream eventfile;
    ofstream outfile;
    string filename;
    short i, j;
    string data, second, third;
    vector<string> events;
    vector<string> subtrio;
    mkvchain mchain;
     
    cout << "\n\n\tWelcome to the Markov chain generator!\n";
    do {
        cout << "Choose from the menu:"
             << "\n1. Load Chain From File"
             << "\n2. Read Event File into chain"
             << "\n3. Save Chain To File"
             << "\n4. Generate Some Output!"
             << "\n5. Quit\n";
        cin >> choice;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if (choice == '1')
        {
            cout << "\nChain file to load: ";
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
            infile.peek();
            while(!infile.eof())
            {
                mchain.load_chain(infile);
                infile.peek();
            }        
            infile.close();
            infile.clear();
         
            cout << "\nChain loaded successfully!!\n";
        }
        else if (choice == '2')
        {
            cout << "\nEvent file to read: ";
            getline(cin, filename);
            eventfile.open(filename.c_str());
            while (!eventfile)   
            {
                eventfile.close();  
                eventfile.clear();  

                cout << "File Not Found!" << endl;

                cout << "Input file name:  ";
                getline(cin, filename);

                eventfile.open(filename.c_str());
            }
            mchain.read_event_file(eventfile);
            
            eventfile.close();
            eventfile.clear();
            cout << "\nEvent file read successfully!\n";
        }
        else if (choice == '3')
        {
            cout << "\nOutput file name:  ";
    
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
            mchain.save_chain(outfile);
            
            outfile.close();
            outfile.clear();
            
            cout << "\nChain saved to file successfully!!\n";
        }
        else if (choice == '4')
        {
            cout << "\nEnter a string and see what happens! ";
    
    
            getline(cin,data);
            
            for (i=0; i<150; i++)
            {
                mchain.get_next_pair(data, second, third);
                cout << ' ' << second << ' ' << third;
                data = third; 
            }
        
            cin.ignore(INT_MAX, '\n');
        }
        else
        {
            cout << "\nThanks for the memories!!!\n\n";
        }
      
        } while (choice != '5' && toupper(choice) != 'Q');
   
    return 0;
}
