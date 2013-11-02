#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class phraseBox 
{
    char border;
    vector<string> stringvec;
    
public:
    phraseBox(void) : border('\0'), stringvec(vector<string>()) { }
    phraseBox(char c) : border(c), stringvec(vector<string>()) { }
    
    vector<string>::size_type longest(void)
    {
        vector<string>::size_type i, larindex=0;
        
        for (i=0; i<stringvec.size()-1; i++)
        {
            if (stringvec[i].size() > stringvec[larindex].size())
            {
                larindex = i;
            }
        }
        return larindex;
    }
    char get_border(void) const { return border; }
    string operator[](vector<string>::size_type i) const {return stringvec[i];}
    vector<string>::size_type size(void) const { return stringvec.size(); }
    void insert(string s) 
    {
        stringvec.push_back(s);
        return;
    }
    
    
};

ostream & operator<<(ostream & out, const phraseBox & pb);
istream & operator>>(istream & in, phraseBox & pb);

int main(void)
{
    phraseBox testbox; 
    
    cout << "\nEnter a phrase: ";
    while (cin.peek() != '\n')
    {
        cin >> testbox; 
    }
    cin.ignore(); 
    cin.clear();
    
    cout << testbox; 
    
    return 0;
}

ostream & operator<<(ostream & out, const phraseBox & pb)
{
    size_t width = pb[pb.longest()].size() + 2;
    out << setfill(pb.get_border()) << setw(width) << '\n';
    for (vector<string>::size_type i=0; i < pb.size()-1; i++)
    {
        out << border << setw(width) << pb[i] << border << '\n';
    }
    out << setfill(pb.get_border()) << setw(width) << '\n';
    return out;
}

istream & operator>>(istream & in, phraseBox & pb)
{
    string s;
    in >> s; 
    pb.insert(s);
    return in; 
}
