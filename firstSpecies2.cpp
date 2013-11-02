#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

string allNotes[] = {"C,", "C#,","Db,", "D,", "D#,", "Eb,", "E,", "E#,", "F,",
                     "F#,", "Gb,", "G,", "G#,", "Ab,", "A,", "A#,", "Bb,", "B,",
                     "B#,", "C", "C#", "Db", "D", "D#", "Eb", "E", "E#", "F#",
                     "Gb", "G", "G#", "Ab", "A", "A#", "Bb", "B", "B#", "C'"};
                     
short modec[] = {0, 3, 6, 8, 11, 14, 17, 19, 22, 25, 29, 32, 35, 37};
                     
short cons[] = {0, 5, -5, 6, -6, 11, -11, 13, -13, 14, -14, 19, 24, 25};

short perfect[] = {0, 11, 19};

vector<short> options;

short rand_vec(vector<short> vec);
                     
class voice
{
    vector <short> pitches;
 
public:
    vector<short> get_pitches(short pos, short range = 0);
    short get_pitch(short pos);
    short voice_length(void);
    vector<short> get_harmonic(voice otherVoice, short pos, short range = 0);
    short get_harmonic(short note, short pos);
    short get_melodic(short note, short pos);
    void read_pitches(void);
    void add_pitch(short pitch);
    void print(void);
    bool is_parallel(voice otherVoice, short pos, short opt);
    bool is_direct(voice otherVoice, short pos, short opt);
  //  bool is_step(short first, short second);
  //  bool is_leap(short first, short second);
    bool is_asc(short first, short second);
  //  bool contour_ok(void);
};

int main(void) 
{
    srand(time(NULL));
    short i, c, note;
    voice cantus;
    voice tenor;
    
    cout << "\nEnter the Cantus pitches in order ('q' to end):\n";
    cantus.read_pitches();
    tenor.add_pitch(cons[11]);
    
    c = 1;
    
    while (c < cantus.voice_length())
    {
        options.clear();
        
        cout << "\nTesting: " << allNotes[cantus.get_pitch(c)];
        
        for (i = 0; i < 14; i++)
        {
            note = 0;
            while (note < 14 && modec[note] != cons[i] + cantus.get_pitch(c))
            {
               note++;
            }
            if (note != 14 && 
                !cantus.is_parallel(tenor, c, cantus.get_pitch(c) + cons[i]) && 
                !cantus.is_direct(tenor, c, cantus.get_pitch(c) + cons[i]) && 
                 tenor.get_melodic(cantus.get_pitch(c) + cons[i], c) != 9 &&
                 tenor.get_melodic(cantus.get_pitch(c) + cons[i], c) != 10 &&
                 tenor.get_melodic(cantus.get_pitch(c) + cons[i], c) < 14)
            {
                options.push_back(cons[i]);
                cout << allNotes[cons[i] + cantus.get_pitch(c)] << " added.\n";
            }
        }
              
        if (options.size() > 0)
    	{
    	    tenor.add_pitch(options[rand_vec(options)] + cantus.get_pitch(c));
    	    cout << allNotes[cons[i] + tenor.get_pitch(c)] << " chosen.\n";
    	    c++;
    	}
    	else
    	{
    	    cout << "\nPosition " << c << " generated no possible options!!\n";
    	    c = 1;
    	}
    	
    } 
    

    cout << "\nTenor: ";
    tenor.print();
    cout << "\nCantus: ";
    cantus.print();
    

    return 0;
    
}

short rand_vec(vector<short> vec)
{
    short max = vec.size();
    return rand() % max;
}


vector<short> voice::get_pitches(short pos, short range)
{
    vector<short> returnVect;
    short offset = 0;

    while (abs(offset) <= abs(range))
    {
        returnVect.push_back(pitches[pos + offset]);
        
        if (range < 0)
        {
            offset --;
        }
        else
        {
            offset ++;
        }
    }
    
    return returnVect;
}
short voice::voice_length(void)
{
    return pitches.size();
}

void voice::add_pitch(short pitch)
{
    pitches.push_back(pitch);
}

short voice::get_pitch(short pos)
{
    return pitches[pos];
}
    
vector<short> voice::get_harmonic(voice otherVoice, short pos, short range)
{
    vector<short> returnVect;
    short offset = 0;
    
    while (abs(offset) <= abs(range))
    {
        returnVect.push_back(abs(pitches[pos + offset] - 
                             otherVoice.pitches[pos + offset]));
        
        if (range < 0)
        {
            offset --;
        }
        else
        {
            offset ++;
        }
    }
    
    return returnVect;
}

short voice::get_harmonic(short note, short pos)
{
    return abs(note - pitches[pos]);
}

short voice::get_melodic(short note, short pos)
{
    return abs(note - pitches[pos-1]);
}

void voice::read_pitches(void)
{
    string::size_type pos; 
    string note;
	
	cin >> note;
   
    while (toupper(note[0]) != 'Q')
    {     
        pos = 0;
        
        while (pos != 38 && note != allNotes[pos])
        {
            pos++;       
        }        
        pitches.push_back(pos);     
        cin >> note;      
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    
    return;
}

void voice::print(void)
{
    vector<string>::size_type pos;
    
    for( pos = 0; pos < pitches.size() - 1; pos++)
    {
        cout << allNotes[pitches[pos]] << "  ";
    }
    
    cout << allNotes[pitches[pitches.size() - 1]] << "\n";
    
    return;
}
    
bool voice::is_parallel(voice otherVoice, short pos, short opt)
{
    bool ispar;
    short interval, prevint, i;
    
    interval = get_harmonic(opt, pitches[pos]);
    prevint = get_harmonic(otherVoice.pitches[pos-1], pitches[pos-1]);
    
    i = 0;
    
    while (i != 3 && !ispar)
    {
        if (interval == perfect[i] && prevint == perfect[i])    
        {
            ispar = true;
        }
        else
        {     
            ispar = false;
        }
        i++;
    }
    
    return ispar;
}

bool voice::is_direct(voice otherVoice, short pos, short opt)
{
    bool isdir, similar;
    
    short thisNote = pitches[pos],
          prevNote = pitches[pos - 1],
          prevOtherNote = otherVoice.pitches[pos - 1],
          interval = get_harmonic(opt, pitches[pos]);
    
   
    similar = (is_asc(prevNote, thisNote) && is_asc(prevOtherNote, opt))
          || (!is_asc(prevNote, thisNote) && !is_asc(prevOtherNote, opt));   
    
    if (similar && (interval == 0 || interval == 8 || 
                    interval == 11 || interval == 19) &&
                                    !is_parallel(otherVoice, pos, opt))
    {
        isdir = true;   
    }
    else
    {
        isdir = false;
    }
    
    return isdir; 
                                        
}

bool voice::is_asc(short first, short second)
{
    bool returnval;
    if (second - first > 0)
    {
        returnval = true;
    }
    else 
    {
        returnval = false;
    }
    
    return returnval;
}



