#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <string>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;

/* String representations of all the notes in two octaves. */

const string allNotes[] = {"C,", "C#,","Db,", "D,", "D#,", "Eb,", "E,", "E#,", 
                           "F,", "F#,", "Gb,", "G,", "G#,", "Ab,", "A,", "A#,", 
                           "Bb,", "B,", "B#,", "C", "C#", "Db", "D", "D#", "Eb", 
                           "E", "E#", "F", "F#", "Gb", "G", "G#", "Ab", "A", 
                           "A#", "Bb", "B", "B#", "C'"};
                     
const short modec[] = {0, 3, 6, 8, 11, 14, 17, 19, 22, 25, 27, 30, 33, 36, 38};
                     
const short cons[] = {0, 5, -5, 6, -6, 11, -11, 13, -13, 14, -14, 19, 24, 25};

const short diss[] = {1, 4, 7, 9, 10, 12, 15, 16, 17, 18};

const short perfect[] = {0, 11, 19};





inline vector<short>::size_type rand_vec(vector<short> vec)
{
    vector<short>::size_type max = vec.size();
    return rand() % max;
}


inline short harm(short pitch1, short pitch2)
{
    return abs(pitch2 - pitch1);
}

inline short mel(short note, short prevNote)
{
    return note - prevNote;
}

void read(vector<short> & vec);

void print(vector<short> vec);

bool is_perfect(short intvl);

bool is_parallel(short intvl1, short intvl2);

bool is_direct(short intvl, short upper_int, short lower_int);

bool motion_ok(short intvl, short prevInt);

bool motion_ok(short intvl);

bool in_mode(short note);

short repeat(vector<short> vec, vector<short>::size_type pos);   

short num_third_sixth(vector<short> vec, vector<short> otherVec);

short num_leaps(vector<short> vec); 




int main(void) 
{
    map<vector<short>, short> storage;
    map<vector<short>, short>::iterator storit;
    srand(time(NULL));
    vector<short>::size_type i;
    vector<short>::size_type c; 
    vector<short>::size_type z; 
    short option, startnote, endnote, answer;
    long k;
    vector<short> options;
    vector<short> cantus;
    vector<short> counterpoint;
    vector<vector<short> > counterpoints;
  
    
    cout << "\nEnter the Cantus pitches in order ('q' to end):\n";
    read(cantus);
    
    cout << "\n\tSelect an option from the menu.\n"
    << "\n1. Upper Counterpoint: Octave - Octave"
    << "\n2. Upper Counterpoint: Fifth - Octave"
    << "\n3. Lower Counterpoint: Unison - Unison"
    << "\n4. Lower Counterpoint: Octave - Octave\n";
         
    cin >> answer;
    
    switch(answer)
    {
    case 1:
        startnote = cantus[0] + 19;
        endnote = cantus[cantus.size() - 1] + 19;
        break;
    case 2:
        startnote = cantus[0] + 11;
        endnote = cantus[cantus.size() - 1] + 19;
        break;
    case 3:
        startnote = cantus[0];
        endnote = cantus[cantus.size() - 1];
        break;
    case 4:
        startnote = cantus[0] - 19;
        endnote = cantus[cantus.size() - 1] - 19;       
    }
    
    
    k = 0;
    
    /* Begin overall loop which provides us with as many solutions as can be 
    completed in 500 cycles. */ 
    
    while (k != 100000)
    {
        c = 1;
        
        counterpoint.clear();
        
        /* The first note of the counterpoint is always a unison, fifth, or 
        octave, so we add the first note without checking anything. */ 
       
        counterpoint.push_back(startnote);
        
        /* loops through each note of the cantus unless it reaches a point where
        there are no longer any legal possibilities available*/
        do  
        {
            options.clear();
            
            /*loop through each of the consonant intervals stored in the cons 
            array*/
            
            for (i = 0; i < 14; i++) // consonance loop
            {   
                /* assign the sum of the cantus pitch and the consonant interval
                to the option variable for readablity */
                
                option = cantus[c] + cons[i];  
                
                /* For the second pitch of the counterpoint, test for parallel 
                or direct motion, and test the conotour with the single-argument
                version which only looks back one note. Check that the pitch is
                in the C mode, and that it doesn't repeat the previous pitch. */
                
                if (c > 1 && !is_parallel(cons[i], 
                               harm(cantus[c-1],  counterpoint[c-1]) ) && 
                    !is_direct(cons[i], 
                        mel(option,  counterpoint[c-1]), 
                        mel(cantus[c], cantus[c-1])) && 
                    
                    
                    motion_ok(mel(option,  counterpoint[c-1]), 
                        mel( counterpoint[c-1],  counterpoint[c-2])) &&
                    
                    in_mode(option) && (option !=  counterpoint[c-1]))
                {
                    options.push_back(option);
                }
                
                /* same test as above, but after pitch 2 use the motion_ok 
                function with two arguments to test for too much disjunct 
                motion*/
                
                if (c <= 1 && !is_parallel(cons[i], 
                               harm(cantus[c-1],  counterpoint[c-1]) ) && 
                    !is_direct(cons[i], 
                        mel(option,  counterpoint[c-1]), 
                        mel(cantus[c], cantus[c-1])) && 
                    
                    
                    motion_ok(mel(option,  counterpoint[c-1])) &&
                    
                    in_mode(option) && (option !=  counterpoint[c-1]))
                {
                    options.push_back(option);
                }
            }  // end consonance loop
            
            /*if there are any legal options, add one randomly chosen option to
            the counterpoint vector and continue on to the next cantus note. */
                  
            if (options.size() > 0)
            {              
                counterpoint.push_back(options[rand_vec(options)]);
            }
            
            c++;
            
                     
        } while (c < cantus.size()-1 && options.size() != 0); // end cantus loop
        
        // c is now in the last position of both vectors
        

        
        // check if final note can be added 
        
        if (options.size() != 0 && !is_parallel(harm(endnote, cantus[c]), 
                                                harm(cantus[c-1],  
                                                         counterpoint[c-1])) && 
                      !is_direct(harm(endnote, cantus[c]), 
                                  mel(endnote, counterpoint[c-1]), 
                                  mel(cantus[c], cantus[c-1])) && 
                                  motion_ok(mel(endnote,  counterpoint[c-1]), 
                        mel( counterpoint[c-1],  counterpoint[c-2])) &&
                              in_mode(endnote) && (endnote !=  counterpoint[c-1]))
        {
             counterpoint.push_back(endnote);
        }
        
        /* Check for the frequency of appearance of each pitch in the 
        counterpoint. If the frequency of appearance of any single pitch is
        greater than one third than the # of notes, the solution is abandoned.  
        This produces a tendency towards seemingly directed motion rather
        than aimless motion. */
        
        i=0; 
        
        while (i < cantus.size() &&  counterpoint.size() == cantus.size()) 
        {
            if (repeat(counterpoint, i) > 
                 static_cast<double>(counterpoint.size()) / 3.0)
            {
                counterpoint.clear();
            }
            else
            {
                i++;
            }
        }
        
        /* This is a final check for disjunct motion in proportion to the 
        length of the melody, and parallel thirds and sixths - the melody can't
        leap around too much, and a counterpoint which produces too many 
        parallel thirds and sixths is abandoned. */
        
        if (counterpoint.size() == cantus.size() && 
            (static_cast<double>(num_third_sixth(counterpoint, cantus)) /
             static_cast<double>(cantus.size()) < 0.25) &&
             static_cast<double>(num_leaps(counterpoint)) /
             static_cast<double>(cantus.size()) < 0.4 )
        {
            counterpoints.push_back(counterpoint);
        }
        else
        {
            counterpoint.clear();
        }
        
        k++;
    }
    
    for (i=0; i<counterpoints.size(); i++)
    {
        cout << "\nCounterpoint " << i << ": ";
        print(counterpoints[i]);
        
        z = 0;
        
        for (k=0; k<counterpoints.size(); k++)
        {
            if(counterpoints[i] == counterpoints[k])
            {
                z++;
            }
        }
        
        cout << " happens " << z << "times.";
        
        
        /*storage.insert ( pair<vector<short>, short>(counterpoints[i], 1) );*/
        
    }
    
    cout << "\nCantus: ";
    print(cantus);
    

    return 0;
    
}

bool is_perfect(short intvl)
{
    short i = 0;
    bool is;
    
    while (i < 3 && intvl != perfect[i])
    {
        i++;
    }
    if (i == 3)
    {
        is = false;
    }
    else 
    {
        is = true;
    }
    
    return is;
}
bool is_parallel(short intvl1, short intvl2)
{
    return (is_perfect(intvl1) && is_perfect(intvl2));
}

void read(vector<short> & vec)
{
    short pos; 
    string note;
	
	cin >> note;
   
    while (toupper(note[0]) != 'Q')
    {     
        pos = 0;
        
        while (pos != 39 && note != allNotes[pos])
        {
            pos++;       
        }        
        vec.push_back(pos);     
        cin >> note;      
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    
    return;
}

void print(vector<short> vec)
{
    vector<short>::size_type pos;
    
    for( pos = 0; pos < vec.size() - 1; pos++)
    {
        cout << allNotes[vec[pos]] << "  ";
    }
    
    cout << allNotes[vec[vec.size() - 1]] << "\n";
    
    return;
}
    
bool is_direct(short intvl, short upper_int, short lower_int)
{
    bool isdir;
    
    if (is_perfect(intvl) && ((upper_int > 0 && lower_int > 0) || 
                              (upper_int < 0 && lower_int < 0 )))
    {
        isdir = true;   
    }
    else
    {
        isdir = false;
    }
    
    return isdir;                                       
}


bool motion_ok(short intvl, short prevInt)
{
    short i = 0;
    
    while ((i != 10) && 
           (abs(intvl) != diss[i]) && 
       /* if previous motion was a leap up or down the voice cannot continue in 
       the same direction, and must move by step*/ 
             !(prevInt > 6 && intvl > 0) && 
             !(prevInt < -6 && intvl < 0) &&
             !(abs(prevInt) > 3 && abs(intvl) > 3)  &&
             (abs(intvl) < 13))
    {
        i++;
    }
    
    return i == 10;
}
bool motion_ok(short intvl)
{
    short i = 0;
    
    while ((i != 10) && 
           (abs(intvl) != diss[i]) && 
           (abs(intvl) < 13))
    {
        i++;
    }
    
    return i == 10;
}

bool in_mode(short note)
{
    short i = 0;
    while (i != 15 && note != modec[i])
    {
        i++;
    }
    
    return i != 15;
}

short repeat(vector<short> vec, vector<short>::size_type pos)      
{                                                     
    short i = 0; 
    vector<short>::size_type j;      
    j = 1; 
  
    while (j != vec.size())
    {
        if (vec[pos] == vec[j])
        {
            i++;
        }
        j++;
    }    
    
    return i;
}

short num_third_sixth(vector<short> vec, vector<short> otherVec)
{
    vector<short>::size_type j = 0;
    short i = 0;
    
    while (j != vec.size())
    {
        if ( ( ( ( (harm(vec[j],     otherVec[j]) == 5) || 
                   (harm(vec[j],     otherVec[j]) == 6) ) && 
                 ( (harm(vec[j+1], otherVec[j+1]) == 5) || 
                   (harm(vec[j+1], otherVec[j+1]) == 6) ) ) ||
               ( ( (harm(vec[j],     otherVec[j]) == 13) || 
                   (harm(vec[j],     otherVec[j]) == 14) ) && 
                 ( (harm(vec[j+1], otherVec[j+1]) == 13) || 
                   (harm(vec[j+1], otherVec[j+1]) == 14) ) ) ) ||
             ( ( ( (harm(vec[j],     otherVec[j]) == 5) || 
                   (harm(vec[j],     otherVec[j]) == 6) ) && 
                 ( (harm(vec[j+1], otherVec[j+1]) == 5) || 
                   (harm(vec[j+1], otherVec[j+1]) == 6) ) ) ||
               ( ( (harm(vec[j],     otherVec[j]) == 24) || 
                   (harm(vec[j],     otherVec[j]) == 25) ) && 
                 ( (harm(vec[j+1], otherVec[j+1]) == 24) || 
                   (harm(vec[j+1], otherVec[j+1]) == 25) ) ) ) )
        {
            i++;
        }
        j++;
    }
    
    return i;
}

short num_leaps(vector<short> vec)      
{                                                     
    short i = 0; 
    vector<short>::size_type j;      
    j = 1; 
  
    while (j != vec.size())
    {
        if (harm(vec[j], vec[j-1]) > 3)
        {
            i++;
        }
        j++;
    }    
    
    return i;
}

