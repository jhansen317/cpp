#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<short> DfromA(vector<short> & A);
vector<short> potentials(vector<short> & v);
bool AfromD(vector<short> & D, vector<short> & new_A, vector<short> & pots);
vector<short> AfromD(vector<short> & D);

void selsort(vector<short> & v);
void swap(short & a, short & b);
vector<short>::size_type min(const vector<short> & v, 
                     vector<short>::size_type beg, vector<short>::size_type end);
vector<short>::size_type linsearch(vector<short> & v, short find);

int main(void)
{
    short num;
    vector<short> A, new_A, D, C;
    vector<short>::size_type i;
    cout << "\nEnter some ordered numbers, starting with 0. Type 'q' to end: ";
    cin >> num;
    while (!cin.fail())
    {
        A.push_back(num);
        cin >> num;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    
    D = DfromA(A);
    
    cout <<"\nYour A vector is: ";
    for (i=0; i<A.size();i++)
    {
        cerr << A[i] << " ";
    }
    
    cout <<"\nYour D vector is: ";
    for (i=0; i<D.size();i++)
    {
        cerr << D[i] << " ";
    }
    new_A = AfromD(D);
    cout <<"\nYour NEW A vector is: ";
    for (i=0; i<new_A.size();i++)
    {
        cerr << new_A[i] << " ";
    }
    
    cout << '\n';
    return 0;
}

vector<short> DfromA(vector<short> & A)
{
    vector<short>::size_type i, j;
    vector<short> D;
    for (i=0; i<A.size(); i++)
    {
        for (j=i+1; j<A.size(); j++)
        {
            D.push_back(A[j]-A[i]);
        }
    }
    selsort(D);
    return D;
}



void selsort(vector<short> & v)
{
    vector<short>::size_type i;
    for (i = 0; i < v.size(); i++)
    { 
        swap(v[i], v[min(v, i, v.size())]);
    }
    return;
}
vector<short>::size_type min(const vector<short> & v, 
                     vector<short>::size_type beg, vector<short>::size_type end)
{
    vector<short>::size_type i, min = beg;
    
    for (i = beg; i < end; i++)
    {
        if(v[i] < v[min])
        {
            min = i;
        }
    }
    return min;
}

void swap(short & a, short & b)
{
    short c;
    c = a;
    a = b;
    b = c;
    return;
}

// returns a vector of sufficient potential A values
vector<short> potentials(vector<short> & v)
{
    vector<short>::size_type i;
    vector<short> returnvec;
    returnvec.push_back(0);
    returnvec.push_back(v.back());
    for (i = v.size()-2; i>2; i--)   
    {
        if ((v[i] != v[i+1]) && (linsearch(returnvec, v[i]) == returnvec.size()))
        {
            returnvec.push_back(v[i]);
            if (linsearch(returnvec, v.back()-v[i]) == returnvec.size())
            {
                returnvec.push_back(v.back()-v[i]);
            }
        }
    }
    selsort(returnvec);
    return returnvec;
}

vector<short>::size_type linsearch(vector<short> & v, short find)
{
    vector<short>::size_type i=0;
    while(i != v.size() && v[i] != find)
    {
        i++;
    }
    return i;
}
bool AfromD(vector<short> & D, vector<short> & new_A, vector<short> & pots)
{
    vector<short>::size_type i=0;
    bool got_it = false;
    
    // check if new_A is the right size first
    if ((new_A.size()*(new_A.size()-1))/2 < D.size()) 
    {
        while (i < pots.size() && !got_it) // loop through potential members
        {
            while (pots[i] < new_A.back()) // skip known invalid options
            {
                i++;
            }
            if (pots[i] == new_A.back()) // skip one more if necessary
            {
                i++;
            }
            new_A.push_back(pots[i]); // add the first new potential member

            got_it = AfromD(D, new_A, pots); // recurse to build the rest
            if (!got_it)
            {
                new_A.pop_back(); // didn't work - try a different one next time 
            }
            i++;
        }
   }
   else
   {
       got_it = (D == DfromA(new_A)); // if we're big enough, check correctness
   }
   return got_it;
}
vector<short> AfromD(vector<short> & D)
{
    vector<short> new_A, p;
    new_A.push_back(0); // we know we start with 0! 
    p = potentials(D);
    AfromD(D, new_A, p);
    return new_A;
}

