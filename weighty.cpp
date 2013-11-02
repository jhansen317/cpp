#include <iostream>

using namespace std;

int main(void)
{
	cout << "Enter the number of ounces:";

	const short ozsPerLb = 16;
	short ozsIn;
  	
	

	cin >> ozsIn;
       
	short lbsOut = ozsIn/ozsPerLb; 
	short ozRmndrOut = ozsIn % ozsPerLb;
	double real_lbs = double(ozsIn)/double(ozsPerLb);

	if (ozsIn == 16)
	{

	cout <<"\n\t16 oz. is equal to 1 Lb. Just 1 Lb. That's it. Why are you using this program?\n\n";
 	
	}

	else if(ozsIn <= 32)
	{
	cout <<"\n\t"<< ozsIn << " oz. is equal to " << lbsOut << " Lb. and " << ozRmndrOut <<" oz. (That's " << real_lbs << " Lbs. by the way)\n\n";
 	}
	else
        {
	cout <<"\n\t"<< ozsIn << " oz. is equal to " << lbsOut << " Lbs. and " << ozRmndrOut <<" oz. (That's " << real_lbs << " Lbs., by the way)\n\n";
	}
	return 0;
}
