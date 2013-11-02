#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include "student.h"

using namespace std;

int main(void)
{
    string filename;
    ifstream infile;
    ofstream outfile;
    student singlestu;
    vector<student> stuvec;
    vector<student>::iterator it;
    
    
    cout << "\n\n\tWelcome to the file copier!\n"
            "Input file name: ";
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
    while ( !infile.eof() )
    {
        singlestu.read(infile);
        stuvec.push_back(singlestu);
        infile.peek(); 
    }
    infile.close();
    infile.clear();
    
    
    
    cout << "\nFile read successfully.\nEnter the output file name:  ";
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
    
    
    for (it = stuvec.begin(); it < stuvec.end(); it++)
    {
        it->print(outfile);
    }
    
    outfile.close();
    outfile.clear();
    cout << '\n';
    
    
    
    return 0;
}
