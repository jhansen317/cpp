#ifndef PHRASELIB_H_INC
#define PHRASELIB_H_INC

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype> 

// Draws a box around a phrase entered at the keyboard or from a file
class phraseBox 
{
    char border;
    char alignment;
    std::vector<std::string> stringvec;
    
public:
    phraseBox(void) : border('*'), alignment('L'), 
                      stringvec(std::vector<std::string>()) { }
    phraseBox(char c, char a) : border(c), alignment(a),
                                        stringvec(std::vector<std::string>()) 
    {
        set_alignment(a); 
        set_border(c);
    }
    
    std::vector<std::string>::size_type longest(void) const
    {
        std::vector<std::string>::size_type i, larindex=0;
        
        for (i=0; i<stringvec.size(); i++)
        {
            if (stringvec[i].size() > stringvec[larindex].size())
            {
                larindex = i;
            }
        }
        return larindex;
    }
    void set_border(char b) { isprint(b) ? border = b : border = '*' ; return; }
    char get_border(void) const { return border; }
    void set_alignment(char a) 
    { 
        alignment = (toupper(a)!='L' && toupper(a)!='C' && toupper(a)!='R') 
        ? 'L' : toupper(a);
        return;             
    }
    char get_align(void) const { return alignment; } 
    std::string operator[](std::vector<std::string>::size_type i) const 
    {
        return stringvec[i];
    }
    std::vector<std::string>::size_type size(void) const 
    { 
        return stringvec.size(); 
    }
    void insert(std::string s) 
    {
        stringvec.push_back(s);
        return;
    }
    void reset(void)
    {
        stringvec.erase(stringvec.begin(), stringvec.end());
        alignment = 'L';
        border = '*';
    }
    
    
};

std::ostream & operator<<(std::ostream & out, const phraseBox & pb);
std::istream & operator>>(std::istream & in, phraseBox & pb);
#endif  

