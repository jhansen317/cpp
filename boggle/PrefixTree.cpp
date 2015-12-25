#include "PrefixTree.h"

// simple linear search for character in children array 
Node* Node::find_child(char c)
{
    for (size_t i = 0; i < children.size(); i++)
    {
        Node* tmp = children[i];
        if ( tmp->get_letter() == c )
        {
            return tmp;
        }
    }
    return NULL;
}

// add characters from a word into our tree
void PrefixTree::add_word(const std::string & s)
{
    // start at the root
    Node* current = root;
    if ( s.length() == 0 )
    {
        current->set_end();
        return;
    }
    for (size_t i = 0; i < s.length(); i++)
    {
        Node* child = current->find_child(s[i]);
        // if we already have a child with current letter keep traversing 
        if (child != NULL)
        {
            current = child;
        }
        // otherwise make a new node and append under current
        else
        {
            Node* tmp = new Node();
            tmp->set_letter(s[i]);
            current->append_child(tmp);
            current = tmp;
        }
        // set end marker if it's the last letter
        if ( i == s.length() - 1 )
            current->set_end();
    }
    return;
}

// Read a list of words in a file-like object into a prefix tree
void PrefixTree::read_file(std::ifstream & infile)
{
    std::string temp;
    while (!infile.eof())
    {
        getline(infile, temp);
        this->add_word(temp);
    }
    return;
}

bool PrefixTree::search(const std::string & s, bool fullsearch)
{
    Node* current = root;
    while ( current != NULL )
    {
        for (size_t i = 0; i < s.length(); i++)
        {
            Node* tmp = current->find_child(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }
        /* at this point we've found a valid prefix but not necessarily a full word in the dictionary 
           if we are searching for full words report whether we've found the end */
        if (fullsearch)
        {
            return current->is_end();
        }
        else
        {
            return true;
        }
    }   
}



