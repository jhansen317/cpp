#include <iostream>
#include <string>

using namespace std;

string read_yes_no(const string & prompt, const string & errmsg);

int main(void)
{
    string answer;
    
    answer = read_yes_no("\nPlease Answer Yes or No to this question  ", 
                        "\nYou did not answer Yes or No.\nPlease try again!  ");
    
    cout << "\n\nYou answered " << answer 
         << ". Thanks for trying this function!";
    
    return 0;
    
}

string read_yes_no(const string & prompt, const string & errmsg)
{
    string answer;
    
    cout << prompt;
    
    cin >> answer;
    
    while (answer != "Yes" && answer != "No")
    {
        
        cout << errmsg;
        
        cin >> answer;
    }
    
    return answer;
    
}
