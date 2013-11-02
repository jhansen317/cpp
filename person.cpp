#include <iostream>
#include <cctype>
#include <cstring>
#include <iomanip>
#include "strextra.h"
#include "person.h"



using namespace std;

    // constructors 

    person::person(void)
    {
        name[0] = '\0'; 
        street[0] = '\0';
        city[0] = '\0';
        state[0] = '\0';
        phone[0] = '\0';  
    }

    person::person(const char name[], const char street[], const char city[], 
                                const char state[], const char phone[])
    {
        set_name(name);         
        set_street(street);          
        set_city(city);
        set_state(state);
        set_phone(phone);
    }

    person::person(const person & p)
    {
        strcpy(name, p.name);         
        strcpy(street, p.street);
        strcpy(city, p.city);
        strcpy(state, p.state);
        strcpy(phone, p.phone);
    }
    
    // printing & reading
    void person::print(void) const
    {
        cout << '|' << setw(17) << name  
             << '|' << setw(18) << street        
             << '|' << setw(18) << city     
             << '|' << setw(5)  << state   
             << '|' << setw(13) << phone      
             << "|\n";
    }
    
    bool person::read(void)
    {
        bool success = !cin.fail();
        
        
        get_line(name, MAX_NAME);
       
        get_line(street, MAX_STREET);
        
        get_line(city, MAX_CITY);
        
        get_line(state, MAX_STATE);
       
        get_line(phone, MAX_PHONE);
        
        return success; 
    }    
    
    // accessors
    void person::get_name(char newname[], const short len) const
    {
        if (len > 0)
        {
            strncpy(newname, name, len-1);
            newname[len-1] = '\0';
        }
        else
        {
            strcpy(newname, name);
        }
        return;
    }    
     
    void person::get_street(char newstreet[], const short len) const
    {
        if (len > 0)
        {
            strncpy(newstreet, street, len-1);
            newstreet[len-1] = '\0';
        }
        else
        {
            strcpy(newstreet, street);
        }
        return;
    }
     
    void person::get_city(char newcity[], const short len) const
    {
        if (len > 0)
        {
            strncpy(newcity, city, len-1);
            newcity[len-1] = '\0';
        }
        else
        {
            strcpy(newcity, city);
        }
        return;
    }
     
    void person::get_state(char newstate[], const short len) const
    {
        if (len > 0)
        {
            strncpy(newstate, state, len-1);
            newstate[len-1] = '\0';
        }
        else
        {
            strcpy(newstate, state);
        }
        return;
    }
    void person::get_phone(char newphone[], const short len) const
    {
        if (len > 0)
        {
            strncpy(newphone, phone, len-1);
            newphone[len-1] = '\0';
        }
        else
        {
            strcpy(newphone, phone);
        }
        return;
    }
    
    //mutators
     
    bool person::set_name(const char newname[])
    {
        strncpy(name, newname, MAX_NAME-1);
        name[MAX_NAME-1] = '\0';
        return true;
    }
    bool person::set_street(const char newstreet[])
    {
        strncpy(street, newstreet, MAX_STREET-1);
        street[MAX_STREET-1] = '\0';
        return true;
    } 
    bool person::set_city(const char newcity[])
    {
        strncpy(city, newcity, MAX_CITY-1);
        city[MAX_CITY-1] = '\0';
        return true;
    } 
    bool person::set_state(const char newstate[])
    {
        strncpy(state, newstate, MAX_STATE-1);
        state[MAX_STATE-1] = '\0';
        return true;
    }     
    bool person::set_phone(const char newphone[])
    {
        strncpy(phone, newphone, MAX_PHONE-1);
        phone[MAX_PHONE-1] = '\0';
        return true;
    }
    
    
    bool person::is_empty(void)
    {
        return (name[0] == '\0' && street[0] == '\0' && city[0] == '\0' && 
            state[0] == '\0' && phone[0] == '\0'); 
    }
