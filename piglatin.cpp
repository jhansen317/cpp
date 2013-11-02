#include <iostream>
#include <string>
#include <cctype>
#include <climits>

using namespace std;

void pltrans(string & word);

int main(void)
{
    string::size_type start, end;
    string phrase, word, answer;
    char yesno;
    
    cout << "\n\t\tWelcome to the Pig Latin Translator\n";
         
    
    do
    {
        cout << "Please enter a word or phrase to translate. \n\n";
         
        getline(cin, phrase);
           
        start = phrase.find_first_not_of(" \t"); // finds the first non-space.
        
        if (start != string::npos) // if the phrase is not just empty spaces. 
        {
            end = phrase.find_first_of(" \t", start);
        
/* The entered phrase is loop'd through, and each individual word is extracted, 
sent to the translation function, and upon its return appended to the answer
string. */      

            while (end !=string::npos)
            {
                word.assign(phrase, start, end - start);
                pltrans(word);
                answer.append(word + " ");
                word.clear();
                start = phrase.find_first_not_of(" \t", end);
                
                if (start == string::npos)
                {
                    end = start;
                }
                else
                {
                    end = phrase.find_first_of(" \t", start);
                }
            }
            
            if (start != string::npos)
            {
                word.assign(phrase, start, end - start);
                pltrans(word);
                answer.append(word + " ");
                word.clear();
            }
        }
     
        cout << answer << "\n\nWould you like to enter another phrase?  ";
        answer.clear();
        cin >> yesno;
        cin.ignore(INT_MAX, '\n');     
    } while (toupper(yesno) == 'Y');
       
    return 0;
}

void pltrans(string & word)
{
    bool endpunct = false, startpunct = false;
    string cons, endp, startp, firstpair;
    string::size_type counter, vlpos = word.find_first_of("aeiouyAEIOUY"),
                               endpuncpos = word.find_last_of("!?,.:'\""), 
                               startpuncpos = word.find_first_of("!?,.:'\""); 
                               
/*Checks if there is punctuation at the beginning and end of the word. If there
are, the punctuation characters are removed and stored in strings, and the 
truth value of their presence is stored in bools. In the case of leading 
punctuation, the position of the first vowel is adjusted to compensate for the 
missing character. */
    
    if (endpuncpos == word.length() -1)
    {
        endp = word[endpuncpos];
        word.erase(endpuncpos);
        endpunct = true;
    }
    if (startpuncpos == 0)
    {
        startp = word[0];
        word.erase(startpuncpos, 1);
        startpunct = true;
        vlpos--;
    }

/*If the word starts with a consonant, consonant group, or "qu", those 
characters are removed from the beginning of the word and tacked on to the end
along with the "ay" suffix that all such words get.*/

    firstpair = word.substr(0, 2);
    
    if (vlpos != 0)
    {
        if (toupper(firstpair[0]) == 'Q' && toupper(firstpair[1]) == 'U')
        {
            cons = firstpair; 
            vlpos++;
        }
        else
        {
            cons = word.substr(0, vlpos);
        }       
        
        word.erase(0, vlpos); 
        word.append(cons + "ay");
        
/*If the first letter of the original word was capitalized, the first letter of
the re-arranged word inherits the capitalization, and the rest of the word is 
lower-cased. If the user types all different case letters and wants that to be 
reflected in the pig-latin version, sorry.*/
        
        if (isupper(cons[0]))
        {
            word[0] = toupper(word[0]);       
            for (counter = 1; counter <= word.size(); counter++)
            {
                word[counter] = tolower(word[counter]);
            }
        }
        else
        {
            for (counter = 0; counter <= word.size(); counter++)
            {
                word[counter] = tolower(word[counter]);
            }
        }              
    }
    
/* If the word started with a vowel, "yay" is appended. Capitalizion doesn't 
concern us here.*/

    else
    {
        word.append("yay");
    }
    
/*After the letters are re-arranged correctly, the punctuation character/s 
is/are added back in the appropriate place/s. */

    if (startpunct)
    {
        word = startp + word;
    }
    if (endpunct)
    {
        word.append(endp);  
    }
     
    return;
}
