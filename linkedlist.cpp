#include <string>
#include <iostream>
#include <cctype>
#include <climits>

using namespace std;

struct Node
{
    string data; 
    Node *next;
};

int main(void)
{       
   
    string holder;
    char yesno;
    Node *first, *last;
    first = new Node;
    last = first;
    
    cout << "\n\tWelcome to the linked list driver!"
         << "\nPlease Enter a bunch of words, 'Q' to end: ";
         
    while(holder[0] != 'Q')
    {
        cin >> holder;
        if (holder[0] != 'Q')
        {
            last->next = new Node;
            last = last->next;
            last->data = holder; 
            last->next = NULL;
        }
    }
    
    for ( Node *p = first; p != NULL; p = p->next )
    {
        if (p->data.length() > last->data.length())
        {
            cout << p->data << '\n';
        }
    }
    
    return 0;   
}

