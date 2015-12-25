#include "PrefixTree.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
    PrefixTree* trie = new PrefixTree();
    string filename, temp;
    ifstream infile;
    infile.open("large.txt");
    while (!infile)
    {
        infile.close();
        infile.clear();
        cerr << "Couldn't find dictionary file..." << endl;
        cout << "Try another filename:  ";
        getline(cin, filename);
        infile.open(filename.c_str());
    }
    trie->read_file(infile);
    infile.close();

    if ( trie->search("trouble") )
        cout << "Found trouble" << endl;

    if ( trie->search("tro", false) )
        cout << "Prefix tro matched..." << endl;

    if ( trie->search("abdominally") )
        cout << "Found abdominally" << endl;

    if ( trie->search("abd", false) )
        cout << "Found prefix abd" << endl;

    if ( trie->search("balloon") )
        cout << "Found balloon" << endl;

    delete trie;
}

