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
short find(const char str[], char substr[], short index)
{
    short matchpos, subindx = 0, wildcount = 0;
    bool beginmatch, endmatch;
      
    while (substr[subindx] != '\0' && str[index] != '\0' && matchpos != -1)
    {
        // found escape character
        if (substr[subindx] == '/' && substr[subindx-1] != '/')
        {
            cout << "\nfound a '/'";
            subindx++;
        }
        else if (!beginmatch && subindx == 0 && substr[subindx] == '*')
        {
            beginmatch = true;
            matchpos = 0; 
        }
        // found unescaped '*' that's not the last char in search string
        else if (substr[subindx] == '*' && substr[subindx-1] != '/' 
                                        && substr[subindx + 1] != '\0')
        { 
            cout << "\nfound a '*'";
            beginmatch = true; 
            wildcount = index;
            // pause at '*' and look forward for next match 
            while (str[wildcount] != substr[subindx+1] && 
                                        str[wildcount] != '\0')
            {
                cout << "\ncounting forward " << wildcount << "spaces.";
                wildcount++;
            }
            // found next match
            if (str[wildcount] != '\0')
            {
                cout << "\nfound another match at position " << wildcount;
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
               cout << "\nFound a '?' in substring at position " << subindx;
               index++;
               subindx++;
        }
        // found a match, throw begin marker and advance to check next pair
        else if (!beginmatch && substr[subindx] == str[index])
        {
            cout << "\nfound first match at position " << index << ".";
            matchpos = index; //store the match
            beginmatch = true;
            index++;
            subindx++;          
        }
        // in the middle of potential matching string, keep checking
        else if (beginmatch && substr[subindx] == str[index] 
                            && substr[subindx + 1] != '\0')
        {
            cout << "\nfound another match at position " << index << ".";
            index++;
            subindx++;        
        }
        // check if the last character matches too
        else if (beginmatch && substr[subindx] == str[index] 
                           && substr[subindx + 1] == '\0')
        {
            cout << "\nfound final matching character at position " << index;
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
            cout << "\nfound a '?' in the last position!";
            endmatch = true;
            index++;
            subindx++; 
        }
        /* didn't find a match, keep going in "searched" string, start over in
        substring */
        else
        {
            cout << "\nDidn't find a match - moving on.";
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
