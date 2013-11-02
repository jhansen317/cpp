#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<cctype>
#include<climits>

using namespace std;

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



template <class Comparable>
short linsearch(vector<Comparable> & v, Comparable find)
{
    short i=0;
    while(i != v.size() && v[i] != find)
    {
        i++;
    }
    return i;
}


template <class Object>
class matrix;

template <typename matrixT>
class Traversor
{
	matrix<matrixT> * matrixp;
	vector<Location> visited;
	short rowInd;
	short colInd;


public:
	Traversor(void) : matrixp(NULL), rowInd(-1), colInd(-1) { }
	Traversor(matrix<matrixT> * mP) : matrixp(mP), rowInd(0), colInd(0) 
	{
		visited.push_back(Location(rowInd, colInd));
	}
	Traversor(matrix<matrixT> * mP, short r, short c) : 
	                                  matrixp(mP), rowInd(r), colInd(c) 
	{ 
		visited.push_back(Location(rowInd, colInd));
	}
	matrixT operator*(){ return matrixp->array[rowInd][colInd]; } 
	
	bool operator==(const Traversor other) const
	{
		return (rowInd == other.rowInd && colInd == other.colInd);
	}
	bool operator!=(const Traversor other) const
	{
		return !(rowInd == other.rowInd && colInd == other.colInd);
	}
	
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
	
	traversor upperLeft(void)
	{
		return traversor(this);
	}
	traversor upperRight(void)
	{
		return traversor(this, 0, numcols()-1);
	}
	traversor lowerRight(void)
	{
		return traversor(this, numrows()-1, numcols()-1);
	}
};
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

string toLower(string a)
{
	string returnstring;
	for (string::size_type i=0; i<a.size(); i++)
	{
		returnstring += tolower(a[i]);
	}
	return returnstring;
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






void findwords(string & tempstring, matrix<char> grid, vector<string> & foundvec, 
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
vector<string> findwords(matrix<char> grid)
{
	vector<string> found;
	vector<string> dict; 
	string s; 
	string temp, filename;
	ifstream infile;
	infile.open("word.list"); 	
   	
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


int main(void)
{
	vector<char> row;
	matrix<char> boggleboard(0,0);

	vector<string> foundwords; 
	
	string findme; 

	row.push_back('i');
	row.push_back('w');
	row.push_back('l');
	row.push_back('i');
	boggleboard.push_back(row);
	row.clear();
	row.push_back('w');
	row.push_back('e');
	row.push_back('l');
	row.push_back('b');
	boggleboard.push_back(row);
	row.clear();
	row.push_back('a');
	row.push_back('e');
	row.push_back('s');
	row.push_back('a');
	boggleboard.push_back(row);
	row.clear();
	row.push_back('p');
	row.push_back('i');
	row.push_back('r');
	row.push_back('h');
	boggleboard.push_back(row);

	
    
	for (short i=0; i< boggleboard.numrows();i++)
	{
		cerr << '\n';
		for (short p=0; p < boggleboard.numcols(); p++)
		{
			cerr << boggleboard[i][p] << ' '; 
		}
	}
	
	
	foundwords = findwords(boggleboard);
	
	cout << "\nFound " << foundwords.size() << " words: "; 
	
	for (vector<string>::size_type i = 0; i < foundwords.size(); i++)
	{
		cout << '\n' << foundwords[i]; 
	}
	
	cout << '\n'; 
	
	return 0; 
}


//a q b d 
//c o n t 
//h r a i 
//t n e n 


