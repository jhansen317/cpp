#ifndef MARKOV_H_INC
#define MARKOV_H_INC

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>


using namespace std;

// holds one "event" string and vector of subsequent event pairs, with parralel
// vector of tally and probability
class sequence
{
    string event;
    vector<string> second_events;
    vector<string> third_events;
    vector<short> tallies;
    vector<double> probs;    
    
    void update_prob_list(const vector<short> & tals, vector<double> & prbs);
    
public:
    
    sequence(void) : event(string()), second_events(vector<string>()), 
                                      third_events(vector<string>()),
                                      tallies(vector<short>()),
                                      probs(vector<double>()) { }
    
    sequence(const sequence & l) : event(l.event), 
                                   second_events(l.second_events),
                                   third_events(l.third_events),
                                   tallies(l.tallies), probs(l.probs) { }
                                   
    sequence(const vector<string> & trio, short tal) : event(trio[0]),
                                      second_events(vector<string>(1, trio[1])),
                                      third_events(vector<string>(1, trio[2])),
                                      tallies(vector<short>(1, tal)),
                                      probs(vector<double>(1,0.0)) { }
                                               
    bool set_event(string s);
    string get_event(void)
    {
        return event;
    }
    void add_pair(string f, string s, short tal=1);
    bool is_empty(void)
    {
        return event.empty();
    }
    
    void choose(string & f, string & s);
    
                       
    void print_to_file(ofstream & out);
    
};

// holds a vector of sequences with some utility functions - a markov chain! 
class mkvchain
{
    vector<sequence> chain;
    
public:
        
    mkvchain(void) : chain(vector<sequence>()) { }
    mkvchain(mkvchain & c) : chain(vector<sequence>())
    {
        vector<sequence>::size_type i;
        for (i=0; i< c.chain.size(); i++)
        {
            chain.push_back(c.chain[i]);
        }
    }
    

    
    void add_pair(vector<string> trio, short tal=1);
    
    void get_next_pair(const string & f, string & s, string & t);
    
    void read_event_lines(ifstream & input);
    
    void read_event_file(ifstream & input);

    bool load_chain(ifstream & input);
    
    void save_chain(ofstream & out);
    
    sequence get_sequence(vector<sequence>::size_type i)
    {
        return i >= chain.size() ? sequence() : chain[i];
    }
};

void add_sequence(vector<sequence> & seqvec, vector<string> trio);

short strtoshort(string & str);

short char_to_ones(const char & c);

inline long rand_range(long min, long max)
{
       return rand()% (max-min+1)  + min;
}

inline double rand_01(void)
{
       return rand_range(0L, RAND_MAX-1L)/(RAND_MAX-1.0);
}
   

#endif
