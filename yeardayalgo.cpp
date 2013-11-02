#include <iostream>

using namespace std;

short START_YEAR = 1800;
short END_YEAR = 2500;

int main(void)
{
    short year;
    long days=0;
    short count=0;
    
    for (year = START_YEAR; year <= END_YEAR; year++)
    {
        if (((year % 4 == 0) && (year % 100 != 0)) || 
            ((year % 4 == 0) && (year % 100 == 0) && (year % 400 == 0)))
        {
            days += 366;
        }
        else 
        {
            days += 365;
        }
        count++;
        cout << days << ", ";
    }
    cout << '\n' << count;
    
    return 0;
}
