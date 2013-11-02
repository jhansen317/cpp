#include <iostream>
#include <iomanip>

using namespace std;

class phraseBox 
{
    char border;
    vector<string> stringvec;
    
public:
    phraseBox(void) : border('\0'), stringvec(vector<string>()) { }
    phraseBox(char c) : border(c), stringvec(vector<string>()) { }
    
    
    
};

ostream & operator<<(ostream & out, const phraseBox & pb);

int main(void)
{
    cout << setfill('#') << setw(50) << '\n';
    for (short i=0; i<8; i++)
    {
        cout << '#' << setw(48) << setfill(' ') << '#' << '\n';
    }
   
  
    cout << setfill('#') << setw(50) << '\n';
    return 0;
}
