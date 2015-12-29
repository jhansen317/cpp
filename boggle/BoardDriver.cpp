#include <iostream>
#include "Board.h"

using namespace std;
int main(void)
{
    string tester = "abcd";   
    SquareNode* sqp = new SquareNode();
    SquareNode* sqp2 = new SquareNode();
    SquareNode* sqp3 = new SquareNode();
    short in1, in2, in3, out1, out2, out3;
    sqp->set_c('a');
    sqp2->set_c('b');
    sqp3->set_c('c');
    sqp2->add_link_to(sqp, DLD);
    sqp->add_link_to(sqp2, R);
    sqp->add_link_to(sqp3, U);
    sqp2->add_link_to(sqp3, DRU);
    cout <<  sqp->count_links() << endl; 
    cout <<  sqp2->count_links() << endl;
    cout << sqp3->count_links() << endl;
    Board boggleboard;
    vector<char> charvec;
    charvec.push_back('a');    
    charvec.push_back('b');    
    charvec.push_back('c');    
    charvec.push_back('d');    
    boggleboard.add_row(NULL, charvec, R);
//    Link* lnk = new Link(U, sqp, sqp2, NULL, NULL, NULL, NULL);
//    Link* lnk2 = new Link(L, sqp, sqp3, NULL, NULL, NULL, NULL);
//    sqp->set_first_out(lnk);
//    sqp2->set_first_in(lnk);
    
//    cout << "Linked from " << lnk->get_from()->get_c() << " to " << 
//            lnk->get_to()->get_c() << endl;
    cout << "And NO ERRORS\n";
    return 0;
}
