#include <string>
#include <iostream>
#include <cctype>

int main(void)
{       
    struct Node
    {
        string data;
        Node *next;
    }
    string holder;
    char yesno;
    Node *first, *last;
    
    cout << "\n\tWelcome to the linked list driver!\nPlease Enter a word:  ";
    cin >> holder;
    first = new Node;
    last = first;
    first->data = holder;
    cout << "\nContinue? ";
    cin >> yesno;
    while(toupper(yesno) == 'Y')
    {
        cout << "\nEnter another word: ";
        cin >> holder;
        last->next = new Node;
        last = last->next;
        last->data = holder; 
        last->next = NULL;
        cout << "\nContinue? ";
        cin >> yesno;     
    }
    
    for ( Node *p = first; p != NULL; p = p->next )
    {
        cout << p->data << '\n';
    }
    
    return 0;   
}

