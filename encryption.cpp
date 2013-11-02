#include<iostream>
#include<cmath>
#include<climits>
#include<cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "huge.h"

using namespace std;

huge N = huge("14014621");
huge e = huge("3709");
huge d = huge("898813");

inline unsigned long rand_range(unsigned long min, unsigned long max)
{
       return rand()% (max-min+1)  + min;
}
huge modexp(const huge & x, const huge & n, const huge & p);

unsigned long bigprime(unsigned long min, unsigned long max);

bool isPrime(unsigned long & n);

void bettergcd(const huge & a, const huge & b, huge & x, huge & y);

huge minverse(const huge & a, const huge & n);

int main(void)
{
    srand(time(NULL));
    vector<huge> hugecont, cryptovec, decryptovec,transfervec;
    vector<huge>::size_type v;
    string M;
    //huge p, q, N, Np, e, d, R, dM, one; 
    //long tempp, tempq, tempe;
    //one = static_cast<const long>(1); 
    //tempp = bigprime(SHRT_MAX, USHRT_MAX);
   // cout << "\nTrying to store " << tempp << " in huge p";
    //p = tempp;
   // tempq = bigprime(SHRT_MAX, USHRT_MAX);
   // cout << "\nTrying to store " << tempq << " in huge q";
   // q = tempq;   
   // N = p*q; 
   // cerr << "\np * q = " << N;
    //cerr << "\np-1 = " << p-one;
   // cerr << "\nq-1 = " << q -one;
   // Np = (p-one)*(q-one);
   // cerr << "\nAnd Np = " << Np;
  //  cin.ignore(INT_MAX, '\n');
   // tempe = bigprime(SHRT_MAX, USHRT_MAX);
   // e = tempe;
   // cerr << "\ne is : " << e;
   // cin.ignore(INT_MAX, '\n');
   // d = minverse(e, Np);
    
    //cout << "\np = " << p << "\nq = " << q << "\nN = " << N << "\nNp = " << Np;
   // cout << "\ne = " << e << "\nd = " << d << '\n';
    
    cout << "\nChoose a word to ENCRYPT: ";
    getline(cin, M);
    cin.ignore(INT_MAX, '\n');
    hugecont = readWord(M);
    cout << "\nLets try printing: ";
    cout << printWord(hugecont);
    cout << "\nWorking on it.";
    for(v=0; v<hugecont.size(); v++)
    {
        cryptovec.push_back(modexp(hugecont[v], e, N));
    }
    
   // R = modexp(M, e, N);
    M = printWord(cryptovec);
    cout << "\nEncrypted word is: " << M << '\n';
    transfervec = readWord(M);
    
    for(v=0; v<transfervec.size(); v++)
    {
        decryptovec.push_back(modexp(transfervec[v], d, N));
    }
    
    M = printWord(decryptovec);
    
    cout << "\nDecrypted integer is: " << M << '\n';
   
    
    return 0; 
}



bool isPrime(unsigned long & n)
{
    unsigned long i=3; 
    if (n % 2 == 0)
    {
        return false;
    }
    while (i * i <= n && n % i != 0)
    {
        i += 2; 
    }
    
    return i*i > n;
}
huge modexp(const huge & x, const huge & n, const huge & p)
{
    huge temp;
    if (n==static_cast<long>(0))
    {
        return static_cast<long>(1); 
    }
   //  cerr << "\nn = " << n;
    // cerr << "\nx = " << x;
     //cerr << ".";
    //cerr << "\nx * x = " << x*x;
   // cerr << "\nx*x%p = " << x*x%p;
   // cerr << "\nn/2 = " << n/static_cast<long>(2);
//    cin.ignore(INT_MAX, '\n');
    temp = modexp((x*x) % p, n/static_cast<long>(2), p);
    //cerr << "\nN = " << n << " mod 2 = " << n % static_cast<long>(2);
    if (!(n % static_cast<long>(2) == static_cast<long>(0)))
    {
        temp = (temp*x) % p;
    }
    return temp; 
    
}
unsigned long bigprime(unsigned long min, unsigned long max)
{
    unsigned long val = rand_range(min, max);
    while(!isPrime(val))
    {
        val = rand_range(min, max);
    }
    return val;
}
void bettergcd(const huge & a, const huge & b, huge & x, huge & y)
{
    huge x1, y1, zero, one;
    zero = static_cast<long>(0);
    one = static_cast<long>(1);
    if (b == zero)
    {
        x = one;
        y = zero;
    }
    else 
    {
 
        //cerr << " ,x =" << x << " and y = " << y;
       // cerr << "\nAbout to go down the rabbit hole again...";
       // cerr << "\nAbout to pass " << a << " % " << b;
      //  cin.ignore(INT_MAX, '\n');
      //  cerr << "\nThe result of which is: " << a % b;
       //cin.ignore(INT_MAX, '\n');
        bettergcd(b, a % b, x1, y1);
     //   cerr << "\nout of recursive call?";
     //   cin.ignore(INT_MAX, '\n');
     //   cerr << "\nx1 = " << x1 << " and y1 =" << y1;
     //  cerr << "\nx = " << x << " and y = " << y;
        x = y1;
     //   cin.ignore(INT_MAX, '\n');
    //  cerr << "\ny = " << y;
       // cerr << '\n' << x1 << " - (" << a << '/' << b << ") *" << y1;
     //   cerr << '\n' << x1 << " - " << a/b << " * " << y1;
     //   cerr << '\n' << x1 << " - " << (a/b) * y1;
        y = x1 - (a/b) * y1;
   //    cerr << "\nnow y = " << y;
    //   cerr << "\nand x = " << x;
    }
    return;
}

huge minverse(const huge & a, const huge & n)
{
    huge x, y;
    
    bettergcd(a, n, x, y);
    return x > static_cast<long>(0) ? x : x + n;
}
