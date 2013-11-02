ostream & operator<<(ostream & out, const phraseBox & pb)
{
    size_t width = pb[pb.longest()].size();
    out << setfill(pb.get_border()) << setw(width+2) << '\n';
    for (vector<string>::size_type i=0; i < pb.size()-1; i++)
    {
        out << border << setfill('') << setw(width) << pb[i] << border << '\n';
    }
    out << setfill(pb.get_border()) << setw(width+2) << '\n';
    return out;
}
