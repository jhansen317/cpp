#ifndef PREFIX_TREE_INC
#define PREFIX_TREE_INC
#include <vector>
#include <string>
#include <fstream>

/* 
Nodes of our prefix tree - each has a char value, array of pointers to 
children nodes, and a EOW flag. 
*/
class Node 
{
    char letter;
    bool end;
    std::vector<Node*> children;

public:
    Node(void) : letter(' '), end(false), children(std::vector<Node*>()) {}
    ~Node() {}
    char get_letter(void) { return letter; }
    void set_letter(char c) { letter = c; return; }
    bool is_end(void) { return end; }
    void set_end(void) { end = true; return; }
    Node* find_child(char c);
    void append_child(Node* child) { children.push_back(child); }
    std::vector<Node*> get_children(void) { return children; }
};

/*
Simple prefix tree for searching a dictionary quickly, finding partial matches,
and quickly abandoning futile searches!
*/
class PrefixTree 
{
    Node* root;
public:
    PrefixTree(void) : root(new Node()) {}
    ~PrefixTree() {}
    void add_word(const std::string & s);
    void read_file(std::ifstream & infile);

    /* pass a false as the second arg and it will return true
       if s is a valid prefix in the tree, not just a full word. */
    bool search(const std::string & s, bool fullwords = true);
};

#endif
