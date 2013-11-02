  /*  while (str[index] != '\0')       
    {
        sub_begin = index;  // if found, store position of first match
        
        while ((substr[subindx] == str[index] &&  
                               substr[subindx] != '\0' && 
                                  str[index] != '\0') || 
                               substr[subindx] == '*' ||
                               substr[subindx] == '?')  
        {
            //find the wildcard that's not the last char of the string
            if (substr[subindx] == '*' && substr[subindx + 1] != '\0')
            {
                cout << "\n '*' found at position " << subindx << "\n";
                
                /* pause at the '*' index and search forward in the string
                until the char that matches the one after '*' is found. If 
                terminating char is found first, abort mission. 
                
                while (str[index] != substr[subindx + 1] &&  
                       str[index] != '\0')
                {
                    cout << "\nCounting forward " << index << " Chars.";
                    index++;
                }
                if (str[index] != '\0') // found another match 
                {
                    cout << "\nFound match for next char after '*'\n";
                    subindx++; // advance to next char in search string
                }
                else // or abort
                { 
                    cout << "\nDidn't find another char after '*'\n";
                    sub_begin = -1;
                }
            } 
            else if (substr[subindx] == '*' && substr[subindx + 1] == '\0') 
            {
                cout << "\nFound a '*' at the end of the string";
                subindx++;
            }
            else if (substr[subindx] == '?' && substr[subindx + 1] != '\0')
            {
                cout << "\nFound '?' at position " << subindx 
                     << "- skipping one letter!";
                index++;
                subindx++;
            }
            else
            {
                cout << "\nFound a matching letter!";
                index++;
                subindx++;
            }
            
        }
        if (substr[subindx] != '\0')
        {
            sub_begin = -1;
        }
    }
    else
    {
        sub_begin = -1;   
    } */
