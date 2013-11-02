#include "markov.h"
#include<string>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;


bool sequence::set_event(string s)
{
    bool okay = false;
    
    if (event.empty())
    {
        event = s;
        okay = true;
    }
    
    return okay;
}


/*returns randomly selected "next pair" of strings, weighted by probability of
occurence*/

void sequence::choose(string & f, string & s)
{
    vector<string>::size_type i=0;
    double r = rand_01();
    double choice = probs[i];
    
    while (r>choice && i<probs.size()-1)
    {
        i++;
        choice += probs[i];
    }
    
    f = second_events[i];
    s = third_events[i];
    
    return;
        
}

// adds "next pair" of strings and updates the tally & probability

void sequence::add_pair(string f, string s, short tal)
{
    vector<string>::size_type i=0;

    //search for second pair
    while (i < second_events.size() && 
          (second_events[i] != f || third_events[i] != s))
    {
        i++;
    }
    
    // if pair is found increment the tally
    if (i != second_events.size())
    {
        tallies[i] += tal;
    }
    else // or add the pair to list of potential second events and start tally 
    {
        second_events.push_back(f);
        third_events.push_back(s);
        tallies.push_back(tal);
        probs.push_back(0.0);
    }
    
    // re-calculate the probabilites
    update_prob_list(tallies, probs);
    
    return;
}


// calculates probabilities based on tally of each "next pair" 

void sequence::update_prob_list(const vector<short> & tals, 
                                      vector<double> & prbs)
{
    short total=0;
    vector<short>::size_type t;
     
    for (t=0; t < tals.size(); t++)
    {
        total += tals[t]; // sum all the tallies
    }

    for (t=0; t < prbs.size(); t++)
    {
        if (total != 0) // take the probability for each event 
        {
            prbs[t] = static_cast<double>(tals[t])/static_cast<double>(total);
        }
    }
    
    return;
}

// prints table of events and tallys to a file, to be loaded or updated later 
void sequence::print_to_file(ofstream & out)
{
    vector<string>::size_type i;
    
    out << "\nEVENT: " << event;
   
    for (i=0; i < second_events.size(); i++)
    {
         out << "\nSECOND: " << second_events[i]
              << "\nTHIRD: " << third_events[i] 
              << "\nTALLY: " << tallies[i] << '\n';
    }
    
    return;
}

/* either adds a pair to an existing sequence, or creates a new sequence if it 
hasn't happened yet*/

void mkvchain::add_pair(vector<string> trio, short tal)
{
    short i=0;
    while (i < chain.size() &&
               chain[i].get_event() != trio[0] &&
              !chain[i].is_empty())
    {
        i++;
    } 
    if (i != chain.size())
    {
        chain[i].add_pair(trio[1], trio[2], tal);
    }
    else
    {
        chain.push_back(sequence());
        if (chain[i].set_event(trio[0]))
        {
            chain[i].add_pair(trio[1], trio[2], tal);
        }   
    }
    return;
}


// prints table of events and probabilities of entire chain to file 
void mkvchain::save_chain(ofstream & out)
{
    vector<sequence>::size_type i=0;
    while (i<chain.size() && !chain[i].is_empty())
    {
        chain[i].print_to_file(out);
        i++;
    }
}


// reads in raw data from file line by line and creates a chain object. 

void mkvchain::read_event_lines(ifstream & input)
{
    string event;
    vector<string> seq;
    vector<string> subseq;
    vector<string>::size_type i;
    while(!input.eof())
    {
        getline(input, event);
        seq.push_back(event);
    }
    for(i=0; i+2<seq.size(); i++)
    {
        subseq.push_back(seq[i]);
        subseq.push_back(seq[i+1]);
        subseq.push_back(seq[i+2]);
        this->add_pair(subseq);
        subseq.clear();
    }
    return;
}

void mkvchain::read_event_file(ifstream & input)
{
    string event;
    vector<string> seq;
    vector<string> subseq;
    vector<string>::size_type i;
    while(!input.eof())
    {
        input >> event;
        seq.push_back(event);
    }
    for(i=0; i+2<seq.size(); i++)
    {
        subseq.push_back(seq[i]);
        subseq.push_back(seq[i+1]);
        subseq.push_back(seq[i+2]);
        this->add_pair(subseq);
        subseq.clear();
    }
    return;
    
    
}


// reads table of events and tallies from file and stores them in memory
bool mkvchain::load_chain(ifstream & input)
{
    
    string line, label, value;
    string::iterator vit;
    string::size_type pos; 
    vector<string> three,seq;
    vector<short> tals;
    vector<string>::size_type vi, t;
    bool event = false;
    long filepos;
    short i, counter=0;
    bool endblock = false;
     
    
    while (!input.eof() && !endblock)
    {
       
        filepos = input.tellg();
        getline(input, line);
        
        pos = line.find(':');
        label = string(line, 0, pos);
        value = string(line, pos+1, line.length()-1);
        vit = value.begin();
        
        while(isspace(*vit))
        {
            value.erase(vit);
            vit = value.begin();
        }
        
        if (label.find("EVENT") != string::npos)
        {
            if (!event)
            {
                three.push_back(value);
                event = true;
            }
            else 
            {   
                endblock = true;
                input.seekg(filepos);
            }
        }
        
        else if (label.find("SECOND") != string::npos)
        {
        
            three.push_back(value);
        }
        else if (label.find("THIRD") != string::npos)
        {
        
            three.push_back(value);
        }
        else if (label.find("TALLY") != string::npos)
        {
            tals.push_back(strtoshort(value));         
        }           
    }
 
    for (vi=0, t=0; vi+2 < three.size(); vi+=2, t++)
    {
        seq.push_back(three[0]);
        seq.push_back(three[vi+1]);
        seq.push_back(three[vi+2]);
        this->add_pair(seq, tals[t]);
        seq.clear();
    }
   
    return endblock;
}



// finds event of string f, and generates the next events
void mkvchain::get_next_pair(const string & f, string & s, string & t)
{
    short i=0;
    while (i < chain.size()-1 &&
               chain[i].get_event() != f &&
              !chain[i].is_empty())
    {
        i++;
    } 
    if (i != chain.size())
    {
        chain[i].choose(s, t);
    }
    return; 
}

// non member version to add a sequence to a chain
void add_sequence(vector<sequence> & seqvec, vector<string> trio)
{
    short i=0;
    while (i < seqvec.size() && 
           seqvec[i].get_event() != trio[0] && 
           !seqvec[i].is_empty())
    {    
        i++;
    }

    
    if (!seqvec[i].is_empty())
    {
        seqvec[i].add_pair(trio[1], trio[2]);
    }
    else
    {
        seqvec.push_back(sequence());
        if (seqvec[i].set_event(trio[0]))
        {
            seqvec[i].add_pair(trio[1], trio[2]);
        }   
    }
    return;
}


short strtoshort(string & str)
{
    short answer=0, t; 
    string::iterator it = str.begin();
    
    if (*it == '-' || *it == '+')
    {
        str.erase(it);
    }
   
    
    for (it = str.end()-1, t=1; it >= str.begin(); it--,t*=10)
    {
        answer += (char_to_ones(*it) * t);
    }

    
    return answer;
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
