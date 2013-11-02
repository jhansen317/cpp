vector<char>::size_type find(vector<char> vec, char c);
vector<char>::size_type find(vector<char> vec1, vector<char> vec2);


vector<char>::size_type find(vector<char> vec, char c)
{
 
    vector<char>::size_type index = 0;
    
    while(index != vec.size() && vec[index] != c)
    {
        index++;
    }
    return index++;
}
