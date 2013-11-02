#include <iostream>
#include <cmath>
using namespace std;

int main(void)
{
	cout << "Enter the first Point:";

	double xa;
	double ya;
	

	cin >> xa >> ya; 

	cout << "Enter the second Point:";

	double xb;
	double yb;
	
	cin >> xb >> yb; 

	double distance = sqrt(pow((xa-xb), 2) + pow((ya-yb), 2));
	
	cout << "The distance bewteen (" << xa << ", " << ya << ") and (" << xb << ", " << yb << ") is " << distance << " units.\n";

	return 0;
}
