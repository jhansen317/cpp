#include <iostream>

using namespace std;

int main(void)
{
    short i, j, w, y, k, count=0;
    cout << "\nEnter a W: ";
    cin >> w;
    for (i=0; i<=w; i++)
    {
        for (j=0; j<=i; j++)
        {
            count++;
        }
    }
    y = w;
    for (k=1; k<=y; k++)
    {
        count++;
    }
    cout << "\nFor a w of " << w << " the total count is: " << count;
    return 0;
}
                                                                            
