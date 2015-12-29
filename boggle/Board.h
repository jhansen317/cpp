#include <vector>
#include <string>
#include <fstream>

enum direction { U, DRU, R, DRD, D, DLD, L, DLU };
/*
// These increment operators are essentially clockwise rotations. 
// prefix
direction& operator++(direction& orig)
{
    orig = static_cast<direction>((orig + 1) % 8);
    return orig;
}

// postfix
direction operator++(direction& orig, int)
{
    direction rVal = orig;
    ++orig;
    return rVal;
}

// prefix
direction& operator--(direction& orig)
{
    orig = static_cast<direction>((orig - 1) % 8);
    return orig;
}

// postfix
direction operator--(direction& orig, int)
f
    direction rVal = orig;
    --orig;
    return rVal;
}
*/

class Link;
class Board;

class SquareNode
{
    char c;
    bool visited;
    std::vector<Link*> links;
    

public:
    friend class Link;
    friend class Board;
    SquareNode(void) : c(' '), visited(false), links(std::vector<Link*>()) {}                                        
    SquareNode(const char & l) : c(l), visited(false),links(std::vector<Link*>()) {}
    ~SquareNode(void) {}
    char get_c(void) { return c; }
    void set_c(const char & l) { c = l; return; } 
    size_t count_links(void) { links.size(); }
    SquareNode* find_from_from_by_dir(direction d);
    void add_link_to(SquareNode* other, direction d);
};

class Link
{
    direction dir;
    SquareNode* from;
    SquareNode* to;
public:
    friend class SquareNode;
    friend class Board;
    Link(void) : dir(U), from(NULL), to(NULL) {}
    Link(direction d, SquareNode* f, SquareNode* t) : dir(d), from(f), to(t) {}
    direction get_direction(void) { return dir; }
    SquareNode* get_from(void) { return from; }
    SquareNode* get_to(void) { return to; }
};

class Board
{
    size_t size;
    SquareNode* upperleft;
    Link* link;
public:
    Board(void) : size(0), upperleft(new SquareNode()), link(NULL) {}
    void add_row(SquareNode* tostartbelow, std::vector<char> chars, direction dir=R);
    SquareNode* get_upperleft(void) { return upperleft; } 
};



