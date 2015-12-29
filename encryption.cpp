#include<iostream>
#include<cmath>
#include<climits>
#include<cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "huge.h"

using namespace std;

inline unsigned long rand_range(unsigned long min, unsigned long max)
{
       return rand()% (max-min+1)  + min;
}
huge modexp(const huge & x, const huge & n, const huge & p);

void bigprime(huge & p);

bool isPrime(huge & n);

void bettergcd(const huge & a, const huge & b, huge & x, huge & y);

huge minverse(const huge & a, const huge & n);

int main(void)
{
    srand(time(NULL));
    vector<huge> hugecont, cryptovec, decryptovec,transfervec;
    vector<huge>::size_type v;
    string M;
    vector<string>::size_type ssize;
    vector<string> stringvec, decodevec;
    huge toencrypt, todecrypt, bigP;
    huge p, q, N, Np, e, d, R, dM, one; 
    p = huge("562949953421381");
    cout << "\np is now " << p;
    q = huge("562949953421503");
    cout << "\nq is now " << q;
    N = p*q; 
    cerr << "\np * q = N = " << N;
    p--;
    q--;
    cerr << "\np-1 = " << p;
    cerr << "\nq-1 = " << q;
    Np = p*q;
    cerr << "\nAnd Np = " << Np;
    e = huge("6374873");
    cerr << "\ne is : " << e;
    d = minverse(e, Np);
    cout << "\nN = " << N << "\ne = " << e << "\nd = " << d << '\n';
    
    cout << "\nEnter a word to ENCRYPT: ";
    getline(cin, M);
    cryptovec = strtohuge(M);
	cerr << "cipher text:\n";
	for (vector<huge>::size_type m=0; m < cryptovec.size(); m++)
	{
		cerr << cryptovec[m] << "\n";
		decryptovec.push_back(modexp(cryptovec[m], e, N));
	}
	cryptovec.clear();
	cerr << "encrypted cipher text:\n";
	for (vector<huge>::size_type m=0; m < decryptovec.size(); m++)
	{
		cerr << decryptovec[m] << "\n";
		cryptovec.push_back(modexp(decryptovec[m], d, N));
	}
	M = hugetostr(cryptovec);
	
    cout << "\nDecrypted Message: " << M << '\n';
   
    return 0; 
    
}



bool isPrime(huge & n)
{
    huge i=5; 
	//cerr << "n mod 2: " << n % 2 << "\n";
    if ((n % 2) == 0 || (n % 3) == 0)
    {
        return false;
    }
    while (n > i * i && 
		   n % i != 0 && 
		   n % (i + 2) != 0)
    {	
		cerr << "Trying i = " << i << "\n";
        i = (i + 6); 
    }
    
    return i*i > n;
}
huge modexp(const huge & x, const huge & n, const huge & p)
{
    huge temp;
    if (n==0)
    {
        return 1; 
    }
     /*cerr << "\nn = " << n;
     cerr << "\nx = " << x;
     cerr << ".";
     cerr << "\nx * x = " << x*x;
     cerr << "\nx*x%p = " << (x*x)%p;
     cerr << "\nn/2 = " << n/2;*/
//    cin.ignore(INT_MAX, '\n'); 
    temp = modexp((x*x) % p, n/2, p);
    //cerr << "\nN = " << n << " mod 2 = " << n % static_cast<long>(2);
    if (!((n % 2) == 0))
    {
        temp = (temp*x) % p;
    }
    return temp; 
    
}
void bigprime(huge & p)
{
    //huge val = huge("10000000000");
    while(!isPrime(p))
    {
		cerr << "p: " << p << "\n";
        p++;
    }
    return;// val;
}
void bettergcd(const huge & a, const huge & b, huge & x, huge & y)
{
    huge x1, y1;
    if (b == 0)
    {
        //cerr << "Right before assignment\n";
        x = 1;
        y = 0;
    }
    else 
    {
        //cerr << "Right before recursive call\n";
        //cerr << "Passing b=" << b << " and a=" << a << "and y1=" << y1 << "and x1=" << x1 << "\n";
        bettergcd(b, a % b, x1, y1);
        x = y1;
        y = (x1 - (a/b) * y1);
    }
    return;
}

huge minverse(const huge & a, const huge & n)
{
    huge x, y;
    
    bettergcd(a, n, x, y);
    return x > 0 ? x : x + n;
}
