#ifndef PERSON_H_INC
#define PERSON_H_INC

#include <iostream>
#include <cctype>
#include <cstring>
#include <iomanip>

using namespace std;

const long MAX_NAME = 18,
               MAX_STREET = 18,
               MAX_CITY = 18,
               MAX_STATE = 3,
               MAX_PHONE = 14;
               
class person
{    
    char name[MAX_NAME], 
       street[MAX_STREET], 
         city[MAX_CITY], 
        state[MAX_STATE],
        phone[MAX_PHONE]; 
    
public:
    // constructors
    person(void);
    person(const char name[], const char street[], const char city[], 
           const char state[], const char phone[]);
    person(const person & p);
    
    // printing & reading  
    void print(void) const;  
    bool read(void);    
    
    // accessors
    void get_name(char newname[], const short len = 0) const;
    void get_street(char newstreet[], const short len = 0) const;
    void get_city(char newcity[], const short len = 0) const;
    void get_state(char newstate[], const short len = 0) const;
    void get_phone(char newphone[], const short len = 0) const;
    
    
    // mutators
    bool set_name(const char newname[]);   
    bool set_street(const char newstreet[]);    
    bool set_city(const char newcity[]);   
    bool set_state(const char newstate[]);   
    bool set_phone(const char newphone[]);
    bool is_empty(void);
};   

#endif


     
