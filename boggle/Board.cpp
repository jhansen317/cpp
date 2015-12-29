#include <iostream>
#include <string>
#include "Board.h"


/**************************
*   IMPLEMENTATIONS BELOW
**************************/


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
{
    direction rVal = orig;
    --orig;
    return rVal;
}

void SquareNode::add_link_to(SquareNode* other, direction d)
{
    std::cout << "Adding link from myself with char " << c << " to another node with char " << other->c << " and direction " << d << std::endl;
    Link* tmp = new Link(d, this, other);
    std::cout << "My link address is " << tmp << std::endl;
    links.push_back(tmp);
    return;
}



SquareNode* SquareNode::find_from_from_by_dir(direction d)
{
    for (size_t i=0; i<links.size(); i++)
    {
        if (links[i]->dir == d)
        {
            return links[i]->to;
        }
    }
}

void Board::add_row(SquareNode* tostartbelow, std::vector<char> chars, direction dir)
{
    std::cout << "Did make it into add_row...\n";
    direction opposite = dir;
   //  4pi/8 = pi/2 rotation, e.g. 180 degree rotation
   //    we use this opposite direction to send a connection both ways
     
    for(size_t i; i < 4; i++);
    {
        opposite++;
    }

    SquareNode* tmp;
    SquareNode* current;
     /*handle first letters...we need to check at the very least
       whether a square even exists for us. If we passed in a 
       NULL, we know we're trying to write the first row, and
       we know at least that our upperleft square exists so we 
       set its letter and move on. If we're starting somewhere
       else, we need to check the square below exists first, and
       if not, create it with our first letter. We also need to
       mark an opposite boundary on the first letter. Than we pop the
       first char off our string and get into a nice clean loop */
    std::cout << "Now we're trying some real shit\n";
    if (tostartbelow == NULL)
    {
        std::cerr << "Should be here....\n";
        //start off with the first letter in the upper left. 
        current = upperleft;
        std::cerr << "putting " << chars[0] << " at upper left...\n";
        current->set_c(chars[0]);    
        //current->set_letter('c');
        std::cerr << "And cleaned up first letters...\n";
    }
    else
    {
        std::cerr << "Putting " << chars[0] << " below " << tostartbelow->c << '\n';
        current = new SquareNode(chars[0]);
        tostartbelow->add_link_to(current, D);
    } 
    std::cout << "About to link up chars";   
    for(size_t i = 1; i < chars.size(); i++)
    {
        tmp = new SquareNode(chars[i]);
        std::cerr << "Linking " << current->c << " to " << tmp->c << " in direction " << dir << "\n"; 
        current->add_link_to(tmp, dir);
        current = tmp;
    }        
}




