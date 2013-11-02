#include <iostream>
#include <cctype>
#include <climits>
#include <cstring>
#include "person.h"
#include "strextra.h"

const short MAX_RECORDS = 10;

using namespace std;

// prints all entries containing stuff, with labeling
void print_all(person persarr[], short size = MAX_RECORDS);

/* prints entries of persarr[] that contain searchstr[] in the member data
specified by element */
void search(person persarr[], char searchstr[], char element);

// returns the first empty index in persarr[] or MAX_RECORDS if full. 
short first_empty(person persarr[], short size = MAX_RECORDS);

int main(void)
{
    short index, recordid, first;
    person rolodex[MAX_RECORDS];
    person entry;
    char yesno, choice;
    char data[20], searchstr[20];
 
    cout << "\n\tWelcome to the Rolodex thing!";
    
    do
    {   
        yesno = 'n';
        cout << "\nHow would you like to proceed?"
             << "\n1. Add Entry"
             << "\n2. Edit Entry"
             << "\n3. Delete Entry" 
             << "\n4. Find an Entry."
             << "\n5. Print all entries."
             << "\n6. (Q)uit\n";
             
        cin >> choice;
        cin.ignore(INT_MAX, '\n');
    
        if ((toupper(choice) == '1' || toupper(choice) == 'A') 
         && (first_empty(rolodex) < MAX_RECORDS))
        {    
           
            
            cout << "\nPlease enter the name: ";
            get_line(data, MAX_NAME);           
            entry.set_name(data);
            
            cout << "\nPlease enter the street: ";
            get_line(data, MAX_STREET);
            entry.set_street(data);
            
            
            cout << "\nPlease enter the city: ";
            get_line(data, MAX_CITY);
            entry.set_city(data);
            
            cout << "\nPlease enter the state: ";
            get_line(data, MAX_STATE);
            entry.set_state(data);
            
            cout << "\nPlease enter the phone: ";
            get_line(data, MAX_PHONE);
            entry.set_phone(data);
            
            rolodex[first_empty(rolodex)] = entry; // if so fill it up
            
            cout << "\nAdding record......successful!";   
        }
        else if ((toupper(choice) == '1' || toupper(choice) == 'A') 
         && (first_empty(rolodex) == MAX_RECORDS))
        {
            cout << "\nThe Rolodex is full! You'll have to make room!\n";
        }
        else if (toupper(choice) == '2' || toupper(choice) == 'E')
        {
            index = 0;
            print_all(rolodex);
            
            cout << "\nPlease enter the ID of the record you'd like to edit:  ";
            
            cin >> recordid;  
            
            while (recordid >= MAX_RECORDS || rolodex[recordid].is_empty())
            {
                cout << "\nThat's a totally invalid ID. Try again:  ";
                cin >> recordid; 
            }
            
            cout << "\nAlright, would you like to enter a single part of an "
                 << "entry or the entire thing? Choose from the menu.\n"
                 << "\n1. Edit name."
                 << "\n2. Edit street."
                 << "\n3. Edit city."
                 << "\n4. Edit state."
                 << "\n5. Edit phone."
                 << "\n6. Edit entire entry."
                 << "\n7. Go Back to Main Menu.";
                 
            cin >> choice; 
                 
            if (choice == '1')
            {
                cout << "\nYou have chosen to edit the name. The name of the " 
                     << "current entry is ";
                rolodex[recordid].get_name(data);
                cout << data << " \n";                   
                cout << "\nPlease enter the new name: ";
                get_line(data, MAX_NAME);           
                rolodex[recordid].set_name(data);
            }
            else if (choice == '2')
            {
                cout << "\nYou have chosen to edit the street. The street of the " 
                     << "current entry is ";
                rolodex[recordid].get_street(data);
                cout << data << " \n";               
                cout << "\nPlease enter the new street: ";
                get_line(data, MAX_STREET);           
                rolodex[recordid].set_street(data);
            }
            else if (choice == '3')
            {
                cout << "\nYou have chosen to edit the city. The city of the " 
                     << "current entry is ";
                rolodex[recordid].get_city(data);
                cout << data << " \n";                     
                cout << "\nPlease enter the new city: ";
                get_line(data, MAX_CITY);           
                rolodex[recordid].set_city(data);
            }
            else if (choice == '4')
            {
                cout << "\nYou have chosen to edit the state. The state of the "
                     << "current entry is ";
                rolodex[recordid].get_state(data);
                cout << data << " \n";
                cout << "\nPlease enter the new state: ";
                get_line(data, MAX_STATE);           
                rolodex[recordid].set_state(data);
            }
            else if (choice == '5')
            {
                cout << "\nYou have chosen to edit the phone. The phone of the "
                     << "current entry is ";
                rolodex[recordid].get_phone(data);
                cout << data << " \n";
                cout << "\nPlease enter the new state: ";
                get_line(data, MAX_PHONE);           
                rolodex[recordid].set_phone(data);
            }
            else if (choice == '6')
            {
                cout << "\nPlease enter the name: ";
                get_line(data, MAX_NAME);           
                entry.set_name(data);
                
                cout << "\nPlease enter the street: ";
                get_line(data, MAX_STREET);
                entry.set_street(data);
                
                
                cout << "\nPlease enter the city: ";
                get_line(data, MAX_CITY);
                entry.set_city(data);
                
                cout << "\nPlease enter the state: ";
                get_line(data, MAX_STATE);
                entry.set_state(data);
                
                cout << "\nPlease enter the phone: ";
                get_line(data, MAX_PHONE);
                entry.set_phone(data);
                
                rolodex[recordid] = entry;
            }
            else if (choice != '7')
            {
                cout << "\nEditing record.....successful!";
            }
            else 
            {
                cout << "\nReturning to main menu!";
            }
            
        }
        else if (toupper(choice) == '3' || toupper(choice) == 'D')
        {
            index = 0;
            // check for the first empty spot so we can go back and clean up
            first = first_empty(rolodex);
            print_all(rolodex);
            
            cout << "\nPlease enter the ID of the record to delete:  ";
            
            cin >> recordid; 
            
            
            // check for valid id
            while (recordid >= MAX_RECORDS || rolodex[recordid].is_empty())
            {
                cout << "\nThat's a totally invalid ID. Try again:  ";
                cin >> recordid; 
            }
            
            // empty out that spot with a default construction
            rolodex[recordid] = person(); 
            
            // move all the other doggies down cause our first_empty() depends
            // on the empty spots being at the end 
            
            for (index = recordid+1; index < MAX_RECORDS; index++)
            {
                rolodex[index-1] = rolodex[index];
            }
            
            // make sure all the spots after the good data are clear. 
            
            for (index = first-1; index < MAX_RECORDS; index++)
            {
                rolodex[index] = person(); 
            }
            
            cout << "\nDeleting....Complete!"; 
            
        }
        else if (toupper(choice) == '4' || toupper(choice) == 'F')
        {
            cout << "\nYou've chosen to find an entry!"
                 << "\nPlease Choose from the list:"
                 << "\n\n1.Find by (n)ame."
                 << "\n2.Find by (s)treet." 
                 << "\n3.Find by (c)ity."
                 << "\n4.Find by s(t)ate."
                 << "\n5.Find by (p)hone.\n";
            cin >> choice; 
            
            if (toupper(choice) == '1' || toupper(choice) == 'N')
            {
                cout << "\nEnter the name to search for:  ";
                get_line(searchstr, MAX_NAME);           
                cout << "\nOk, searching for " << searchstr << '\n';  
                search(rolodex, searchstr, choice);           
            }
            else if (toupper(choice) == '2' || toupper(choice) == 'S')
            {
                cout << "\nEnter the street to search for:  ";
                get_line(searchstr, MAX_STREET);           
                cout << "\nOk, searching for " << searchstr << '\n';  
                search(rolodex, searchstr, choice); 
            }
            else if (toupper(choice) == '3' || toupper(choice) == 'C')
            {
                cout << "\nEnter the city to search for:  ";
                get_line(searchstr, MAX_CITY);           
                cout << "\nOk, searching for " << searchstr << '\n';  
                search(rolodex, searchstr, choice); 
            }
            else if (toupper(choice) == '4' || toupper(choice) == 'T')
            {
                cout << "\nEnter the state to search for:  ";
                get_line(searchstr, MAX_STATE);           
                cout << "\nOk, searching for " << searchstr << '\n';  
                search(rolodex, searchstr, choice); 
            }
            else if (toupper(choice) == '5' || toupper(choice) == 'P')
            {
                cout << "\nEnter the phone to search for:  ";
                get_line(searchstr, MAX_PHONE);           
                cout << "\nOk, searching for " << searchstr << '\n';  
                search(rolodex, searchstr, choice); 
            }
            else 
            {
                cout << "\nAborting Search!\n"; 
            }
        }
        else if (toupper(choice) == '5' || toupper(choice) == 'P')
        {
            print_all(rolodex);         
        }
        
        cout << "\nWould you like to continue?  ";
        cin >> yesno;
    } while (toupper(yesno) == 'Y');
    
    cout << "\nGoodbye!\n\n";
    
    return 0;
}

void print_all(person persarr[], short size)
{
    short index = 0; 
    
    cout << '|' << left << setw(2)  << "ID"
         << '|' << setw(17) << "Name"  
         << '|' << setw(18) << "Street"        
         << '|' << setw(18) << "City"     
         << '|' << setw(5)  << "State"   
         << '|' << setw(13) << "Phone"      
         << "|\n"
         << "----------------------------------------"
         << "----------------------------------------\n";
         
    while (!persarr[index].is_empty() && index < size) // print all the records
    {
        cout << '|' << setw(2)  << index;
        persarr[index].print();
        index++;
    }
         
    return;
}


void search(person persarr[], char searchstr[], char element)
{
    short index, pos=0;
    char data[20];
    for (index = 0; index < MAX_RECORDS; index++)
    {
        if (toupper(element) == '1' || toupper(element) == 'N')
        {
            persarr[index].get_name(data);
        }
        else if (toupper(element) == '2' || toupper(element) == 'S')
        {
            persarr[index].get_street(data);
        }
        else if (toupper(element) == '3' || toupper(element) == 'C')
        {
            persarr[index].get_city(data);
        }
        else if (toupper(element) == '4' || toupper(element) == 'T')
        {
            persarr[index].get_state(data);
        }
        else if (toupper(element) == '5' || toupper(element) == 'P')
        {
            persarr[index].get_phone(data);
        }
                    
        if (find(data, searchstr, pos) != -1)
        {
            //cout << "found match:\n";
            persarr[index].print();
        }
        else
        {
            //cout << "Didn't find a match :(\n";
        }
    }
    
    return; 
}

short first_empty(person persarr[], short size)
{
    short count = 0;
    
    while (count < size && !persarr[count].is_empty())
    {
        count++;
    }
    
    return count;
}



