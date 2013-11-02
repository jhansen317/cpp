#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>

using namespace std;

int main(void)
{
    
        
    ifstream infile;
    
    infile.open("test.txt"); 
    

        infile.seekg(0);
        cout << (char)infile.get();
        infile.seekg(17, ios_base::cur);
        cout << (char)infile.peek();
        infile.seekg(-4, ios_base::cur);
        cout << (char)infile.get();
        infile.ignore();
        cout << (char)infile.get();
        infile.seekg(18);
        cout << (char)infile.get();
        infile.seekg(-6, ios_base::end);
        cout << (char)infile.peek();
        infile.seekg(-1, ios_base::end);
        cout << (char)infile.get();
        if (infile.fail())
        {
            cout << "/nFailed!";
        }
        cout << infile.tellg();
        if (infile.fail())
        {
            cout << "/nFailed!";
        }
        cout << (char)infile.get();
        if (infile.fail())
        {
            cout << "/nFailed!";
        }
        infile.seekg(0);
        if (infile.fail())
        {
            cout << "/nFailed!";
        }
        cout << (char)infile.get();

        
        
   
    infile.close();
    infile.clear();
    return 0;
}
