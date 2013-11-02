#include <iostream>
#include <cctype>
#include <string>


using namespace std;

int main(void)
{
	unsigned short i;
   string word_string;

	cout << "Enter A word: ";

	getline(cin, word_string);

	
	
	for (i = 0; i < word_string.length(); i++)
	{
		cout << word_string[i] << "\n\n";
	}


	return 0;
}
