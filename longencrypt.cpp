#include<iostream>
#include<cmath>
#include<climits>
#include<cstdlib>
#include <ctime>

using namespace std;

inline long rand_range(long min, long max)
{
       return rand()% (max-min+1)  + min;
}
long modexp(const long & x, const long & n, const long & p);

long bigprime(long min, long max);

bool isPrime(long & n);

void bettergcd(const long & a, const long & b, long & x, long & y);

long minverse(const long & a, const long & n);

int main(void)
{
    srand(time(NULL));
    long p, q, N, Np, e, d, M, R, dM; 

    p = bigprime(100, 300);
    
    q = bigprime(100, 300);  
    N = p * q; 
    
    Np = (p-1)*(q-1);

    e = bigprime(100, 300);

    d = minverse(e, Np);
    
    cout << "\np = " << p << "\nq = " << q << "\nN = " << N << "\nNp = " << Np;
    cout << "\ne = " << e << "\nd = " << d << '\n';
    
    cout << "\nChoose an integer to ENCRYPT: ";
    cin >> M;
    R = modexp(M, e, N);
    
    cout << "\nEncrypted integer is: " << R; 
    
    cout << "\nDecrypted integer is: " << modexp(R, d, N) << '\n';
    
    
    
    return 0; 
}



bool isPrime(long & n)
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
long modexp(const long & x, const long & n, const long & p)
{
    long temp;
    if (n == 0)
    {
        return 1; 
    }
    temp = modexp((x*x) % p, n/2, p);
    if (n % 2 != 0)
    {
        temp = (temp*x) % p;
    }
    return temp; 
    
}
long bigprime(long min, long max)
{
    long val = rand_range(min, max);
    while(!isPrime(val))
    {
        val = rand_range(min, max);
    }
    return val;
}
void bettergcd(const long & a, const long & b, long & x, long & y)
{
    long x1=0, y1=0;
    if (b == 0)
    {
        x = 1;
        y = 0;
    }
    else 
    {
        cerr << "\nI've been passed: a = " << a << " ,b = " << b;
        cerr << " ,x =" << x << " and y = " << y;
        cerr << "\nAbout to go down the rabbit hole again...";
        cerr << "\nAbout to pass " << a << " % " << b;
        cin.ignore(INT_MAX, '\n');
        cerr << "\nThe result of which is: " << a % b;
        cin.ignore(INT_MAX, '\n');
        bettergcd(b, a % b, x1, y1);
        cerr << "\nout of recursive call?";
        cin.ignore(INT_MAX, '\n');
        cerr << "\nx1 = " << x1 << " and y1 =" << y1;
        cerr << "\nx = " << x << " and y = " << y;
        x = y1;
        cin.ignore(INT_MAX, '\n');
        cerr << "\ny = " << y;
        cerr << '\n' << x1 << " - (" << a << '/' << b << ") *" << y1;
        cerr << '\n' << x1 << " - " << a/b << " * " << y1;
        cerr << '\n' << x1 << " - " << (a/b) * y1;
        y = x1 - (a/b) * y1;
        cerr << "\nnow y = " << y;
    }
    return;
}

long minverse(const long & a, const long & n)
{
    long x=0, y=0;
    
    bettergcd(a, n, x, y);
    return x > 0 ? x : x + n;
}
