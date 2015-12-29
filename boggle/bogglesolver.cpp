#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include <climits>
#include <ctime>
#include "PrefixTree.h"
#include "RandLetter.h"
#include "../sortlib.h"

using namespace std;

// Tidy location class to hold coordinates on the board. 

class Location
{
	short row;
	short col;
	
public:
	Location(void) : row(0), col(0) { }
	Location(short r, short c) : row(r), col(c) { }
	Location(const Location & other) : row(other.row), col(other.col) { }
	
	short get_row(void) { return row; }
	short get_col(void) { return col; } 
	
	bool operator==(const Location other) const
	{
		return (row == other.row && col == other.col); 
	}
bool operator!=(const Location other) const
	{
		return !(row == other.row && col == other.col); 		
	}
};


// linear search 
template <class Comparable>
typename vector<Comparable>::size_type linsearch(vector<Comparable> & v, Comparable find)
{
    typename vector<Comparable>::size_type i=0;
    while(i != v.size() && v[i] != find)
    {
        i++;
    }
    return i;
}


template <class Object>
class matrix;


/* Traversors function like iterators, but instead of manipulating them 
 with arithmetic, you feed them directions as strings N, S, E, W, etc. They
 also remember where they have been, and for the purposes of this application
 are not allowed to "traverse" anywhere they've already gone, as per the 
 rules of boggle.  */
 
template <typename matrixT>
class Traversor
{
	matrix<matrixT> * matrixp;
	vector<Location> visited;
	short rowInd;
	short colInd;


public:
	Traversor(void) : matrixp(NULL), rowInd(-1), colInd(-1) { }

	Traversor(const matrix<matrixT> * mP) : 
        matrixp(const_cast<matrix<char>* >(mP)), rowInd(0), colInd(0) 
	{
		visited.push_back(Location(rowInd, colInd));
	}

	Traversor(const matrix<matrixT> * mP, short r, short c) : 
	    matrixp(const_cast<matrix<char>* >(mP)), rowInd(r), colInd(c) 
	{ 
		visited.push_back(Location(rowInd, colInd));
	}
	
	// dereference operator
	matrixT operator*(){ return matrixp->array[rowInd][colInd]; } 
	
	// comparison operators
	bool operator==(const Traversor other) const
	{
		return (rowInd == other.rowInd && colInd == other.colInd);
	}

	bool operator!=(const Traversor other) const
	{
		return !(rowInd == other.rowInd && colInd == other.colInd);
	}
	
	
	/* operator++ works a little oddly due to the two dimensional nature of
	 the boggle board ++ing a traversor object moves it from left to right 
	 down each row from top to bottom, made for easy looping through all 
	 items in the matrix. */
	Traversor operator++(int)
    {
    	if (colInd != matrixp->numcols()-1)
        {
        	colInd++;
        }
        else if (rowInd != matrixp->numrows()-1)
        {
        	colInd = 0;
        	rowInd++;
        }
        visited.clear();
        visited.push_back(Location(rowInd, colInd));
        return *this;
    }
	
	
    // moves the iterator in the specified direction 
	void operator+=(string dir)
	{
		if (dir == "N")
		{
			rowInd--;
		}
		else if (dir == "S")
		{
			rowInd++;
		}
		else if (dir == "E")
		{
			colInd++;
		}
		else if (dir == "W")
		{
			colInd--;
		}
		else if (dir == "NE")
		{
			rowInd--;
			colInd++;
		}
		else if (dir == "NW")
		{
			rowInd--;
			colInd--;
		}
		else if (dir == "SE")
		{
			rowInd++;
			colInd++;
		}
		else if (dir == "SW")
		{
			rowInd++;
			colInd--;
		}
		visited.push_back(Location(rowInd, colInd));
		return;
	}    
	
	// backs up to the previous position. 
	matrixT reverse(void)
    {
        if (visited.size() > 1)
        {
            visited.pop_back();
        }
        rowInd = visited.back().get_row();
        colInd = visited.back().get_col();
        return matrixp->array[rowInd][colInd];
    }
    
    /* tests if we can move a given direction - first tests if we move off
       the board, and then if we are moving to a spot we've been to before. */
   
	bool test(string dir)
	{		
		bool returnval = true;		
		
		(*this)+=dir;
		
		if (rowInd == matrixp->numrows() || rowInd == -1 || 
			colInd == matrixp->numcols() || colInd == -1)
		{
			returnval = false;
		}
		else if (linsearch(visited, Location(rowInd, colInd)) < visited.size()-1)
		{
			returnval = false; 
		}
		
		this->reverse(); 
		return returnval;
	}


};

template <class Object>
class matrix
{
	vector< vector<Object> > array;
	
public:
	friend class Traversor<Object>;
	typedef Traversor<Object> traversor;
	typedef typename vector<Object>::value_type contents_type;
	matrix(short rows, short cols ) : array(rows)
	{
		for (short i=0; i < rows; i++)
		{	
			array[i].resize(cols);
		}
	}	
	matrix(const matrix & rhs) : array(rhs.array) { }
	const vector<Object> & operator[](short row) const
	{
		return array[row];
	}
	vector<Object> & operator[](short row)
	{
		return array[row];
	}
	typename vector<Object>::size_type numrows(void) const
	{
		return array.size();
	}
	typename vector<Object>::size_type numcols(void) const
	{
		return numrows() > 0 ? array[0].size() : 0;
	}
	void push_back(const vector<Object> & newRow)
	{
		array.push_back(newRow);
	}
	
	traversor upperLeft(void) const
	{
		return traversor(this);
	}
	traversor upperRight(void) const 
	{
		return traversor(this, 0, numcols()-1);
	}
	traversor lowerRight(void) const
	{
		return traversor(this, numrows()-1, numcols()-1);
	}
};

string toLower(string a)
{
	string returnstring;
	for (string::size_type i=0; i<a.size(); i++)
	{
		returnstring += static_cast<char>(tolower(a[i]));
	}
	return returnstring;
}

template <class Comparable>
long fullSearch(const vector<Comparable> & a, const Comparable & x)
{
	long low = 0;
	long high = a.size()-1;
	long mid;
	while (low <= high)
	{
		mid = (low+high)/2;
		if (toLower(a[mid]) < toLower(x))
		{
			low = mid+1;
		}
		else if (toLower(a[mid]) > toLower(x))
		{
			high = mid-1;
		}
		else
		{
			return mid;
		}
	
	}
	return -1; 
}


long subSearch(vector<string> svec, string x)
{
	long low = 0;
	long high = svec.size()-1;
	long mid;
	while (low <= high)
	{
		mid = (low+high)/2;
		if (toLower(svec[mid].substr(0, x.size())) < toLower(x))
		{
			low = mid+1;
		}
		else if (toLower(svec[mid].substr(0, x.size())) > toLower(x))
		{
			high = mid-1;
		}
		else
		{
			return mid;
		}
	}
	return -1; 
}


void findwords(string & tempstring, const matrix<char> & grid, vector<string> & foundvec, 
	                            matrix<char>::traversor pos, 
	                            vector<string> & dicvec)
{
	string dirs[] = {"E", "S","NW","N", "W", "NE",  "SE", "SW"};
	
    for (size_t i=0; i < 8; i++)
    {
    	if (pos.test(dirs[i])) 
    	{
    		pos+=dirs[i];
    		tempstring += (*pos);
    		
    		if (fullSearch(dicvec, tempstring) != -1)
    		{
    			if (linsearch(foundvec, tempstring) == foundvec.size())
    			{
    				foundvec.push_back(tempstring); 
    			}   			
    			findwords(tempstring, grid, foundvec, pos, dicvec);
    		}
    	    else if (subSearch(dicvec, tempstring) != -1)
    		{
    			findwords(tempstring, grid, foundvec, pos, dicvec);	 
    		}
    		pos.reverse(); 
    		tempstring = tempstring.substr(0, tempstring.size()-1);
    	}
   	}
	return; 
}

void findwords_trie(string & tempstring, const matrix<char> & grid, vector<string> & foundvec, 
	                            matrix<char>::traversor pos, 
	                            PrefixTree* triedic)
{
	string dirs[] = {"E", "S","NW","N", "W", "NE",  "SE", "SW"};
	
    for (size_t i=0; i < 8; i++)
    {
    	if (pos.test(dirs[i])) 
    	{
    		pos+=dirs[i];
    		tempstring += (*pos);
    		
    		if (triedic->search(tempstring)) // search only for complete words
    		{
    			if (linsearch(foundvec, tempstring) == foundvec.size())
    			{
    				foundvec.push_back(tempstring); 
    			}   			
    			findwords_trie(tempstring, grid, foundvec, pos, triedic);
    		}
    	    else if (triedic->search(tempstring, false)) // if we didn't find a complete word, try prefix
    		{
    			findwords_trie(tempstring, grid, foundvec, pos, triedic);	 
    		}
    		pos.reverse(); 
    		tempstring = tempstring.substr(0, tempstring.size()-1);
    	}
   	}
	return; 
}
vector<string> findwords_trie(const matrix<char> & grid, PrefixTree* triedic)
{
    vector<string> found;
    matrix<char>::traversor start = grid.upperLeft();
    string s;
    s = *start;
    findwords_trie(s, grid, found, start, triedic);
    while (start != grid.lowerRight())
    {
        start++;
        s = *start;
        findwords_trie(s, grid, found, start, triedic);
    }

     return found;   
}
vector<string> findwords(const matrix<char> & grid)
{
	vector<string> found;
	vector<string> dict; 
	string s; 
	string temp, filename;
	ifstream infile;
	infile.open("large.txt"); 	
   	
	//cerr << "\nGot into first findwords"; 
	
    while (!infile)   
    {
        infile.close();  
        infile.clear();  
    
        cout << "File Not Found!" << endl;
    
        cout << "Input file name:  ";
        getline(cin, filename);
    
        infile.open(filename.c_str());
    }
    while (!infile.eof())
    {
    	getline(infile, temp);	
    	dict.push_back(temp);
    }
    infile.close();
    
    
    matrix<char>::traversor start = grid.upperLeft();
    s = *start; 
    findwords(s, grid, found, start, dict);
    while (start != grid.lowerRight())
    {
        start++;
        s = *start;
        findwords(s, grid, found, start, dict);
    }
	
	return found; 
}


int main(int argc, char* argv[])
{
	char c; 
    srand(time(NULL));
    string holder;
	vector<char> row;
	matrix<char> boggleboard(0,0);
    PrefixTree* trie = new PrefixTree();
    ifstream infile;
    infile.open("large.txt");
    trie->read_file(infile);
    infile.close();
	vector<string> foundwords; 
	size_t BOARD_SIZE;
    if (argc > 1)
    {
        BOARD_SIZE = atoi(argv[1]);
    }   
    else
    {
        BOARD_SIZE = 4;
    }
	
    cout << "Generating random boggle board..." << endl;
    holder = RandString(BOARD_SIZE*BOARD_SIZE);
    

	for (size_t i=0; i<BOARD_SIZE; i++) // loop to populate each row of the board 
	{
		for (size_t p=0; p<BOARD_SIZE; p++)
		{   
			row.push_back(holder[(i*BOARD_SIZE)+p]);
		}
		boggleboard.push_back(row);
		row.clear();
	}
	cout << "\nYour Boggle Board:"; 
    
	for (vector<char>::size_type i=0; i< boggleboard.numrows();i++)
	{
		cerr << '\n';
		for (vector<char>::size_type p=0; p < boggleboard.numcols(); p++)
		{
			cerr << boggleboard[i][p] << ' '; 
		}
	}
	

    vector<string> newfound;
    clock_t triebegin = clock();
    newfound = findwords_trie(boggleboard, trie);
    clock_t trieend = clock();
    double elapsed_secs_trie = static_cast<double>(trieend - triebegin) / CLOCKS_PER_SEC;

    quicksort(newfound);
	
    cout << "\nPrefixTree version found " << newfound.size() << 
            " words in " << elapsed_secs_trie << " seconds: ";
	for (vector<string>::size_type i = 0; i < newfound.size(); i++)
	{
		cout << '\n' << newfound[i]; 
	}

    cout << "\nStarting binary search version...please wait...\n";

    clock_t begin = clock();    	
	foundwords = findwords(boggleboard);
    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    quicksort(foundwords);
	cout << "\nBinary search version found " << foundwords.size() << 
            " words in " << elapsed_secs << " seconds: ";
	for (vector<string>::size_type i = 0; i < foundwords.size(); i++)
	{
		cout << '\n' << foundwords[i]; 
	}
	
	cout << '\n';
	
    double elapsed_ratio = elapsed_secs/elapsed_secs_trie;
 
    cout << "Ratio of binary search speed to tree search speed: " << elapsed_ratio << ":1" << endl;   
	return 0; 
}



