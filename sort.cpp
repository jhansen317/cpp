#include "file_to_vec.h"
#include "sortlib.h"
#include "searchlib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void commandVec(int argc, char* argv[], vector<string> & v)
{
	for (short i=0; i < argc; i++)
    {
    	v.push_back(string(argv[i]));
    }
	return; 	
}


bool optionExists(const vector<string> & cmdargs, const string & option)
{
	return linearSearch(cmdargs, option) != cmdargs.size(); 
}

string optionValue(const vector<string> & cmdargs, const string & option)
{
	return cmdargs[linearSearch(cmdargs, option) + 1];  
}


int main(int argc, char* argv[])
{
	string infilename, outfilename;
	vector<string> cmdargs;
    ifstream infile;
    ofstream outfile;
    vector<string> stringvec;
    vector<short> shortvec;
    
    //cout << "\n\n\tWelcome to the file sorter!\n";
    
    commandVec(argc, argv, cmdargs);

    infilename = optionValue(cmdargs, string("-i"));
    
    infile.open(infilename.c_str());               
    while (!infile)   
    {
        infile.close();  
        infile.clear();  

        cout << "File Not Found!" << endl;

        cout << "Input file name:  ";
        getline(cin, infilename);

        infile.open(infilename.c_str());
    }
    
        
    if (optionExists(cmdargs, string("-n"))) 
    {
    	cout << "\nTreating " << infilename << " as numerical data..."; 
    	file_to_vec(infile, shortvec);
    }
    else
    {
    	cout << "\nTreating " << infilename << " as string data...";
    	file_to_vec(infile, stringvec); 
    }
    
    if (optionExists(cmdargs, string("-q"))) 
    {
    	cout << "\nQuicksorting...";
    	quicksort(stringvec);
    }
    else if (optionExists(cmdargs, string("-s")))
    {
    	cout << "\nShellsorting...";
    	shellsort(stringvec); 
    }
    else if (optionExists(cmdargs, string("-n")))
    {
    	quicksort(shortvec);
    	
    }
    cout << "\nFile sorted successfully.";
   
    outfilename = optionValue(cmdargs, string("-o"));
    
    outfile.open(outfilename.c_str());  
    
    while (!outfile)  
    {
        outfile.close();  
        outfile.clear();  
        cout << "Invalid output file name!" << endl;

        cout << "Enter the output file name:  ";
        getline(cin, outfilename);

        outfile.open(outfilename.c_str());
    }
    
    if (optionExists(cmdargs, string("-n")))
    {
    	vec_to_file(outfile, shortvec);
    }
    else
    {
    	vec_to_file(outfile, stringvec);
    }
    cout << '\n'; 

    
    
	return 0; 
}
