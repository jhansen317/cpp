#include "phraselib.h"

std::ostream & operator<<(std::ostream & out, const phraseBox & pb)
{
    size_t width = pb[pb.longest()].size()+2;
    size_t pre, post; 
    
    out << std::setw(width+3) << std::setfill(pb.get_border()) << '\n';
    
    for (std::vector<std::string>::size_type i=0; i < pb.size(); i++)
    {
        pre = pb.get_align() == 'C' ? (width-pb[i].size())/2 : 0;
        if (pre*2 < width-pb[i].size() && pre != 0)
        {
            post = (width-pb[i].size())/2 + 1;
        }
        else if (pre > 0)
        {
            post = pre;
        }
        else
        {
            post = 0;
        }
        out << pb.get_border();
        out << std::setw(pre) << std::setfill(' ') << "";
        if (pb.get_align() == 'L') 
        {
            out << ' ' << std::setw(width-1) 
                << std::setiosflags(std::ios_base::left) << pb[i];
            out << std::resetiosflags(std::ios_base::left);
        } 
        else if (pb.get_align() == 'R')
        {
            out << std::setw(width-1) 
                << std::setiosflags(std::ios_base::right) << pb[i] << ' ';
            out << std::resetiosflags(std::ios_base::right);
        }
        else 
        {
            out << pb[i]; 
        }
        out << std::setw(post) << std::setfill(' ') << "";
        out << pb.get_border() << '\n';
    }
    out << std::setw(width+3) << std::setfill(pb.get_border()) << '\n';
    
    return out;
}

std::istream & operator>>(std::istream & in, phraseBox & pb)
{
    std::string s; 
    while(in.peek() != '\n')
    {
        in >> s;
        pb.insert(s);
    }
    
    return in; 
}
