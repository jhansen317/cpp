#include "student.h"
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

bool student::print(ofstream & output) const
{
    if (output.is_open() && output.good())
    {
        output << "\nname = " << name 
               << "\nID = " << id
               << "\nGPA = " << gpa
               << "\ngender = " << gender << "\n";              
    }
    
    return output.good();
}

bool student::read(ifstream & input)
{
    string line, label, value;
    string::iterator vit;
    string::size_type pos, i; 
    bool labels[4] = {false, false, false, false};
    bool endblock;
    streampos filepos;
    
    while (!input.eof() && !endblock)
    {
        filepos = input.tellg();

        getline(input, line);
        
        pos = line.find('=');
        label = string(line, 0, pos);
        value = string(line, pos+1, line.length()-1);
        vit = value.begin();
        
        for (i=0; i<label.length(); i++)
        {
            label[i] = toupper(label[i]);
        }
        while(isspace(*vit))
        {
            value.erase(vit);
            vit = value.begin();
        }
        
        if (label.find("NAME") != string::npos)
        {
            if (!labels[0])
            {
                set_name(value);
                labels[0] = true;
            }
            else 
            {   
                endblock = true;
                input.seekg(filepos);
            }
        }
        else if (label.find("ID") != string::npos)
        {
            if (!labels[1])
            {
                set_id(strtolong(value));
                labels[1] = true;
            }
            else 
            {
                endblock = true;
                input.seekg(filepos);
            }
        }
        else if (label.find("GPA") != string::npos)
        {
            if (!labels[2])
            {
                set_gpa(strtodub(value));
                labels[2] = true;
            }
            else
            {
                endblock = true;
                input.seekg(filepos);
            }
        }
        else if (label.find("GENDER") != string::npos)
        {
            if (!labels[3])
            {
                set_gender(value[0]);
                labels[3] = true;
            }
            else
            {
                endblock = true;
                input.seekg(filepos);
            }   
        }   
        else if (label.find('#') != string::npos)
        {
            // do nothing? 
        }
            
    }
    
    
    if (!labels[0])
    {
        value = "";
        set_name(value);
    }
    if (!labels[1])
    {
        set_id(0);
    }
    if (!labels[2])
    {
        set_gpa(0.0);
    }
    if (!labels[3])
    {
        value = "";
        set_gender(value[0]);
    }
    
    return endblock;
}

long strtolong(string & str)
{
    long answer=0, t; 
    bool neg = false;
    string::iterator it = str.begin();
    
    if (*it == '-' || *it == '+')
    {
        if (*it == '-')
        {
            neg = true;
        }
        str.erase(it);
    }
   
    
    for (it = str.end()-1, t=1; it >= str.begin() && t < LONG_MAX; it--,t*=10)
    {
        answer += (char_to_ones(*it) * t);
    }
    
    if(neg)
    {
        answer = -answer;
    }
    
    return answer;
}

double strtodub(string & str)
{
    double pre = 0.0, post = 0.0, t = 0.0;
    string::size_type pos;
    string::iterator it = str.begin();
    bool neg = false;
    
    if (*it == '-' || *it == '+')
    {
        if (*it == '-')
        {
            neg = true;
        }
        str.erase(it);
    }
    
    pos = str.find('.');
    
    for (it = str.end()-1, t=1.0; it > str.begin() + pos; it--, t*=10.0)
    {
        post += (static_cast<double>(char_to_ones(*it)) * t);
    }
    
    post = post/t;
    
    for (it = str.begin()+pos-1, t=1.0; it >= str.begin(); it--, t*=10.0)
    {
        pre += (static_cast<double>(char_to_ones(*it)) * t);       
    }
     
    pre += post;
    
    if(neg)
    {
        pre = -pre;
    }
    
    return pre;
}

short char_to_ones(const char & c)
{
    short answer;
    switch (c)
    {
    case '0':
        answer = 0;
        break;
    case '1':
        answer = 1;
        break;
    case '2':
        answer = 2;
        break;
    case '3':
        answer = 3;
        break;
    case '4':
        answer = 4;
        break;
    case '5':
        answer = 5;
        break;
    case '6':
        answer = 6;
        break;
    case '7':
        answer = 7;
        break;
    case '8':
        answer = 8;
        break;
    case '9':
        answer = 9;
        break;
    default:
        answer = 0;   
    }
    return answer; 
}


