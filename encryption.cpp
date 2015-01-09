#include<iostream>
#include<cmath>
#include<climits>
#include<cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "huge.h"

using namespace std;

/*huge N = huge("26797");
huge e = huge("13379");
huge d = huge("11099");
huge N = huge("289589987027694038837");
huge e = huge("123456791");
huge d = huge("266023389946776676079")*/

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
    //long tempp, tempq, tempe;
    //one = static_cast<const long>(1); 
    p = huge("100000000000000000151");
    //bigprime(p);
    cout << "\np is now " << p;
    q = huge("100000000000000000129");
    //bigprime(q);
    //tempq = bigprime(SHRT_MAX, USHRT_MAX);
    cout << "\nq is now " << q;
   // q = tempq;   
    N = p*q; 
   // N = huge("5000000064000000203");
    cerr << "\np * q = N = " << N;
    p--;
    q--;
    cerr << "\np-1 = " << p;
    cerr << "\nq-1 = " << q;
    Np = p*q;
    cerr << "\nAnd Np = " << Np;
  //  cin.ignore(INT_MAX, '\n');
   // tempe = bigprime(SHRT_MAX, USHRT_MAX);
    e = huge("100000000000000000039");
     //bigprime(e);
    cerr << "\ne is : " << e;
   // cin.ignore(INT_MAX, '\n');
    d = minverse(e, Np);
    //d = huge("199679738338703423");*/
    cout << "\nN = " << N << "\ne = " << e << "\nd = " << d << '\n';
    
    cout << "\nEnter a word to ENCRYPT: ";
    //getline(cin, M);
    cin >> M;
    toencrypt = readWord(M);
    cout << "\ntoencrypt = " << toencrypt;
    cout << "\nWorking on it.";
    todecrypt = modexp(toencrypt, e, N);
    cout << "\nEncrypted Message: " << todecrypt << '\n';
    toencrypt = modexp(todecrypt, d, N);
    M = printWord(toencrypt);
    
    cout << "\nDecrypted Message: " << M << '\n';
   
    return 0; 
    
}



bool isPrime(huge & n)
{
    huge i=3; 
    if (huge((n % 2)) == int(0))
    {
        return false;
    }
    while (n > i * i && n % i != 0)
    {
        i = (i + 2); 
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
        p = (p + static_cast<long>(1));
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
