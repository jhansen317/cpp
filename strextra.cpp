#include "strextra.h"
#include <cstring>
#include <iostream>
#include <climits>

using namespace std;

// char
short find(const char str[], char c, short index)
{
    while (str[index] != c && str[index] != '\0')
    {
        index++;
    }
    if (str[index] == '\0')
    {
        index = -1; 
    }
    return index;
}

// string
short find(const char str[], char substr[], short index, bool caseSense)
{
    short matchpos = 0, subindx = 0, wildcount = 0;
    bool beginmatch, endmatch;
    
    while (substr[subindx] != '\0' && str[index] != '\0' && matchpos != -1)
    {
        // found escape character
        if (substr[subindx] == '/' && substr[subindx-1] != '/')
        {
            subindx++;
        }
        // if the first char in the search string is * then beginmatch is true
        else if (!beginmatch && subindx == 0 && substr[subindx] == '*')
        {
            beginmatch = true;
            matchpos = 0; 
        }
        // found unescaped '*' that's not the last char in search string
        else if (substr[subindx] == '*' && substr[subindx-1] != '/' 
                                        && substr[subindx + 1] != '\0')
        { 
            beginmatch = true; 
            wildcount = index;
            // pause at '*' and look forward for next match 
            while ((caseSense ? str[wildcount] : toupper(str[wildcount])) != 
                (caseSense ? substr[subindx+1] : toupper(substr[subindx+1])) && 
                                        str[wildcount] != '\0')
            {
                wildcount++;
            }
            // found next match
            if (str[wildcount] != '\0')
            {
                index = wildcount;
                subindx++;
            }
            // didn't find it - abort 
            else
            {
                matchpos = -1;
            }                  
        }
        // found an unescaped '?' that's not the last char
        else if (substr[subindx] == '?' && substr[subindx - 1] != '/' 
                                        && substr[subindx + 1] != '\0')       
        {
               index++;
               subindx++;
        }
        // found a match, throw begin marker and advance to check next pair
        else if (!beginmatch && 
            (caseSense ? substr[subindx] : toupper(substr[subindx])) == 
            (caseSense ? str[index] : toupper(str[index])))
        {
            matchpos = index; //store the match
            beginmatch = true;
            index++;
            subindx++;          
        }
        // in the middle of potential matching string, keep checking
        else if (beginmatch && 
            (caseSense ? substr[subindx] : toupper(substr[subindx])) == 
            (caseSense ? str[index] : toupper(str[index])) 
                            && substr[subindx + 1] != '\0')
        {
            index++;
            subindx++;        
        }
        // check if the last character matches too
        else if (beginmatch && 
            (caseSense ? substr[subindx] : toupper(substr[subindx])) == 
            (caseSense ? str[index] : toupper(str[index])) 
                           && substr[subindx + 1] == '\0')
        {
            endmatch = true;
            index++;
            subindx++; 
        }
        else if (substr[subindx] == '*' && substr[subindx + 1] == '\0')
        {
            endmatch = true;
            subindx++; 
        }
        else if (beginmatch && substr[subindx + 1] == '\0' 
                            && substr[subindx] == '?')
        {
            endmatch = true;
            index++;
            subindx++; 
        }
        /* didn't find a match, keep going in "searched" string, start over in
        substring */
        else
        {
            index++;   
            subindx = 0;
            beginmatch = false;
        }       
    }
    if (!beginmatch || !endmatch)
    {
        matchpos = -1;
    }
    
    return matchpos; 
}

//nice input
void get_line(char s[], const long max)
{
    cout.flush();
    if (cin.peek() == '\n')
    {
        cin.ignore();
    }
    cin.getline(s, max);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return;
}
