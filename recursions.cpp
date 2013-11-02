#include <iostream>

using namespace std;

short sum(short n);
short comb(short n, short k);

int main(void)
{
    short num, en, kay;
    cout << "\nEnter a Number: ";
    cin >> num;
    
    cout << "\nThe sum of the first " << num << " integers is: " << sum(num);
    
    cout << "\nEnter N: ";
    cin >> en;
    cout << "\nEnter K: ";
    cin >> kay;
    cout << comb(en, kay);
    return 0;
}

short sum(short n)
{
    if (n==1)
    {
        cerr << "\nReturning 1";
        return 1;
    }
    else
    {
        cerr << "\nCalling sum(" << n << "-1)";
        return sum(n-1)+n;
    }
}

short comb(short n, short k)
{
    if (k == 0)
    {
        return 1;
    }
    else if (n == k)
    {
        return 1;
    }
    else
    {
        cout << "\nCalling comb(" << n-1 << ", " << k << ") + comb(" << n-1 << ", " << k-1 << ')';
        return comb(n-1, k) + comb(n-1, k-1);
    }
}

short combmem(short n, short k)
{
    static vector<short> mem(1);
    static bool init = false;
    if (!init)
    {
        mem[0] = 1;
        init = true;
    }
    if (n - k = (short)(mem.size()))
    {
        mem.resize(n+1);
    }
    return n < 0 ? 0
                 : (mem[n] != 0 ? mem[n]
                                : mem[n] = comb(n-1, k) + comb(n-1, k-1);
}

                                    7,4
               6,4                                      6,3
        5,4                  5,3
   4,4    4,3              4,3        4,2
        3,3   3,2       3,3   3,2
             2,2  2,1        2,2  2,1
                  1,1  1,0       1,1  1,0
