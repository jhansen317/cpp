#include <iostream>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <climits>
#include "huge.h"

using namespace std;

void swap(short & a, short & b)
{
    short c;
    c = a;
    a = b;
    b = c;
    return;
}    
void swap(char & a, char & b)
{
    char c;
    c = a;
    a = b;
    b = c;
    return;
}

huge huge::operator+(const huge & rhs) const
{
    huge temp, storage; 
    char carry = 0;
    size_t i=0, longest;
    if (numdigits >= rhs.numdigits)
    {
        longest = numdigits;
    }
    else
    {                                                                                      
        longest = rhs.numdigits;
    }
    if (sign == -1 && rhs.sign == 1)
    {
       // cerr << "\nCalling object is negative...";
        storage = *this;
        storage.sign = 1;
       // cerr << "\nStorage now holds: " << storage;
        temp = rhs - storage;
    }
    else if ((sign == 1 || sign == 0) && rhs.sign == 1)
    {
        //cerr << "\nCalling object is positive...";
        while (i<longest)
        {
            //cerr << "\nAdding digits: " << i;
            temp.digits[i] = static_cast<char>(digits[i] + rhs.digits[i] + carry);
            if (temp.digits[i] > 9)
            {
                if (i == longest-1)
                {
                    longest++;
                }
                temp.digits[i] %= 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            temp.numdigits++;
            i++;
        }
        temp.sign = 1;
    }
    else if (sign == 1 && rhs.sign == -1)
    {
        //cerr << "\nright hand object is negative...";
        storage = rhs;
        storage.sign = 1;
        temp = *this - storage;
    }
    i = temp.numdigits-1;
    while(i > 1 && temp.digits[i] == 0)
    {
       temp.numdigits--;
       i--;
    }
    if (temp.numdigits == 2 && temp.digits[1] == 0)
    {
        temp.numdigits--;
    }
    return temp; 
}



huge huge::operator-(const huge & rhs) const
{
    huge temp, storage, storage2; 
    char carry = 0;
    size_t i=0, longest;
    //cerr << "\nat least got into - operator!";
    //cin.ignore(INT_MAX, '\n');
    
    if (numdigits >= rhs.numdigits)
    {
        longest = numdigits;
    }
    else
    {
        longest = rhs.numdigits;
    }
    /*if (numdigits == 1 && rhs.numdigits == 1 && sign ==1 && rhs.sign == 1 )
    {
        if (digits[0] > rhs.digits[0])
        {
            temp.digits[0] = digits[0] - rhs.digits[0];
            temp.sign = 1;
        }
        else if (rhs.digits[0] > digits[0])
        {
            temp.digits[0] = rhs.digits[0] - digits[0];
            temp.sign = -1;
        }
        else
        {
            temp.digits[0] = 0;
            temp.sign = 0;
        }
        temp.numdigits = 1;
    }
    else if (rhs.numdigits == 1 && sign ==1 && rhs.sign == 1)
    {
        if (digits[0] >= rhs.digits[0])
        {
            temp = *this;
            temp.digits[0] = digits[0] - rhs.digits[0];
            temp.sign = 1;
        }
        else 
        {
            temp = *this;
            temp.digits[0] = 10 - (rhs.digits[0] - digits[0]);
            if (temp.digits[1] > 0)
            {
                temp.digits[1]--;
            }
           
        }
        
        
    }
    else*/ if (*this > rhs && (sign == 1 && rhs.sign ==1))
    {
        //cerr << "\nBoth objects are positive, left hand operand is larger";
        while (i<longest)
        {
          //  cerr << "\nworking on " << static_cast<short>(digits[i]) << " and " << static_cast<short>(rhs.digits[i]);
            if (digits[i]-carry < rhs.digits[i])
            {
                temp.digits[i] = static_cast<char>((digits[i]+10-carry) - rhs.digits[i]);
                carry = 1; 
            }
            else
            {
                temp.digits[i] = static_cast<char>(digits[i] - rhs.digits[i] - carry);
                carry = 0;
            }
            temp.numdigits++;
            i++;
        }
        temp.sign = 1;
       // cerr << "\nTemp = " << temp;
    }
    else if (rhs > *this && (sign == 1 && rhs.sign ==1))
    {
        //cerr << "\nBoth objects are positive, right hand operand is larger";
        temp = rhs - *this;
        temp.sign = -1;
    }
    else if (sign == -1 && rhs.sign == -1)
    {
       // cerr << "\nBoth objects are negative";
        storage = *this;
        storage.sign = 1;
        storage2 = rhs;
        storage2.sign = 1;
        temp = storage - storage2;            
        temp.sign = -1;
    }
    else if (sign == -1 && rhs.sign == 1)
    {

        //cerr << "\nleft hand operand is negative";
        storage = *this;
        storage.sign = 1;
        temp = storage + rhs;
        temp.sign = -1;
    }
    else if (sign == 1 && rhs.sign == -1)
    {
        //cerr << "\nRight hand operand is negative";
        storage = rhs;
        storage.sign = 1;
        temp = *this + storage;
    }
    else if (*this == rhs)
    {
        temp = static_cast<long>(0);
        temp.sign = 0;
    }
    else if (rhs.sign == 0)
    {
        temp = *this;
    }
    else if (sign == 0)
    {
        temp = rhs;
        temp.sign = -1;
    }

    //cerr << "\nBut did we get out....?";
   i = temp.numdigits-1;
   while(i > 1 && temp.digits[i] == 0)
   {
       temp.numdigits--;
       i--;
   }
   //cerr << "\ntemp == " << temp;
    if (temp.numdigits == 2 && temp.digits[1] == 0)
    {
        temp.numdigits--;
    }
   // cerr << "\ntemp = " << temp;
   //cerr << "\nResult for now = " << temp;
    return temp; 
}


huge huge::operator-(const long & rhs) const
{
    huge hrhs = rhs; 
   
    return *this - hrhs; 
}

istream & huge::read(istream & in) 
{
    size_t zeros, beg, end;
    numdigits = 0;
    if (in.peek() == '-')
    {
        in.ignore();
        sign = -1;
    }
    else
    {
        sign = 1;
    }
    

    while (isdigit(in.peek()) && numdigits < MAX_DIGITS)
    {
        digits[numdigits] = static_cast<char>(in.get()-'0');
        numdigits++;
    }
    
    for (zeros = numdigits; zeros < MAX_DIGITS; zeros++)
    {
        digits[zeros] = 0; 
    }
    for (beg=0, end=numdigits-1; beg < numdigits/2; beg++, end--)
    {
        swap(digits[beg], digits[end]);
    }
    in.ignore(INT_MAX, '\n');
    return in;
}

ostream & huge::print(ostream & out) const
{
    size_t pos = 1;
    if (sign == -1)
    {
        out << '-';
    }
    while (pos <= numdigits)
    {
        out << static_cast<char>(digits[numdigits-pos]+'0');
        pos++;
    }
    return out;
}


istream & operator>>(istream & in, huge & num)
{  
    return num.read(in);
}
ostream & operator<<(ostream & out, const huge & num)
{
    return num.print(out);
}
huge huge::operator*(const long & rhs) const
{
    huge hrhs;
    hrhs = rhs;
    
    return *this * hrhs;
}

huge huge::operator/(const huge & rhs) const
{
    huge returnval, temp;
    short holder; 
    temp = *this;
    //returnval = static_cast<long>(1);
    //cerr << "\nDivision passed *this = ";
    //this->print(std::cerr);
   // cerr << " and rhs = ";
    //rhs.print(std::cerr);
    //cin.ignore(INT_MAX, '\n');
   // cerr << "\nTemp = " << temp;
   // cerr << "\nReturnval + temp = " << returnval +temp;
    if (rhs > *this)
    {
        returnval = static_cast<long>(0);
    }
    else if (sign == 1 && rhs.sign == 1)
    {
         //cerr << "\nDivision both operands are positive";
         // cerr << "\nThis - rhs = " << *this-rhs;
        //cerr << "\nRhs*returnval = " << rhs*returnval;
        if (rhs.numdigits == 1)
        {
           // cerr << "\nGot into the right branch at least...";
            size_t i = numdigits-1;
           // cerr << "\nDividing " << static_cast<char>(digits[i]+'0');
          //  cerr << " and " << static_cast<char>(rhs.digits[0]+'0');
           // cerr << " which = " << static_cast<char>((digits[i]/rhs.digits[0])+'0');
            returnval.digits[i] = digits[i]/rhs.digits[0];
          //  cerr << " msb in returnval: " << static_cast<char>(returnval.digits[i]+'0');
            holder = digits[i] % rhs.digits[0];
            while (i > 0)
            {
                holder = (holder*BASE) + digits[i-1]; 
                returnval.digits[i-1] =  holder / rhs.digits[0];
                holder = holder % rhs.digits[0];
                i--;  
            }
            returnval.numdigits = numdigits;
            i = numdigits-1;
            while (returnval.digits[i] == 0)
            {               
                returnval.numdigits--;
                i--;
            }
            returnval.sign = 1;
            
        }
        else
        {
            while (!(rhs > temp)) 
            {
                temp = temp-rhs;
                returnval = returnval+static_cast<long>(1);    
            //cerr << "\nreturnval = " << returnval;
            //cerr << "\nrhs*returnval = " << rhs * returnval;
            //cerr << "\nThis - rhs = " << *this-rhs;
            //cin.ignore(INT_MAX, '\n');
            }
        }
    }
    else if (sign == -1 && rhs.sign == -1)
    {
        while (*this - rhs > rhs * returnval )
        {
            returnval = returnval+temp;     
            //cerr << "\nreturnval = " << returnval;
        }
    }
    
    return returnval;
}
vector<huge> readWord(string word)
{
    vector<huge> returnvec;
    huge temp;
    long longtemp;
    vector<huge>::size_type i;
    //cerr << "\nChar Max: " << setbase(16) << UCHAR_MAX;
   // cerr << "\nLong Max: " << LONG_MAX;
   // cerr << setbase(0) << "\nChar Max: " << UCHAR_MAX;
  //  cerr << "\nLong Max: " << LONG_MAX;
    for(i=0; i<word.size(); i+=3)
    {
        cerr << "\nBack in loop?";
       /*longtemp = (static_cast<long>(word[i])<<16);
        if (i+1 > word.size()-1)
        {
            i++;
        }
        else
        {
            longtemp+=static_cast<long>(word[i+1]);
        }*/
       
        longtemp = static_cast<long>((word[i]&0xFF)<<16);
       //cerr << "\nletter is: ";
        //cerr << setbase(16) << longtemp;
       //longtemp<<=16;
       // cerr << "\nshifted by 8: ";
     //   cerr << longtemp;           
        if (i+1 <= word.size())
        {         
            longtemp += static_cast<long>((word[i+1]&0xFF)<<8);
            //longtemp<<=8;
        }
        cerr << "\nletters 1 and 2 are: ";
        //cerr << setbase(16) << longtemp;
      
        //cerr << "\n1 and 2 shifted over 8: ";
       //cerr << longtemp;
        if (i+2 <= word.size())
        {
           // cerr << "\nthird Char: " << static_cast<int>(word[i+2]);
            longtemp += static_cast<long>(word[i+2]&0xFF);
        }
        /*longtemp<<=8;
        cerr << "\n1, 2, and 3 altogether: ";
        cerr << longtemp;*/

         //cerr << setbase(16) << longtemp;
       // cerr << "\nShifted over 16 bits and masked: " << ((longtemp>>16)&0xFF);
       // cerr << "\nAs char: " << static_cast<unsigned char>((longtemp>>16)&0xFF);
       // cerr << "\nShifted 8 bits and masked: " << ((longtemp>>8)&0xFF);
       // cerr << "\nAs char: " << static_cast<unsigned char>((longtemp>>8)&0xFF);      
       // cerr << "\n0just masked: " << (longtemp&0xFF);
        //cerr << "\nAs char: " << static_cast<unsigned char>(longtemp&0xFF);
        //cerr << "\nShifted over 8 bits: " << (longtemp>>8);
        
        
        /*cerr << "\nFF0000 bit masked: " << ((longtemp)&0xFF0000);
        //cerr << "\nshifted back 8 and masked: " << ((longtemp)&0xFF00>>8);
        //cerr << "\nshifted back 8: " << ((longtemp)>>8);
       // cerr << "\nCombined with upper 16 masked as a char: " << static_cast<unsigned char>((longtemp+longtemp2)&0x00FF);
       //  cerr << "\nCombined shifted back down: " << static_cast<char>((longtemp+longtemp2)>>8);
         //cerr << "\nCombined upper 16 masked: " << static_cast<char>(longtemp&0x00FF);
        //cerr << "\nFirst Letter: " << c1;
        //cerr << "\nSecond Letter: " << c2;*/
        temp = longtemp;
       // cerr << "\nPast assignment?";
        returnvec.push_back(temp); 
        //cerr << "\nBelow push_back?";
    }
    cerr << "\nOut of loop?";
    return returnvec;
}
string printWord(vector<huge> huges)
{
    string temp;
    unsigned char c1, c2, c3;
    long templong; 
    vector<huge>::size_type v;
    for(v=0; v<huges.size(); v++)
    {
        templong = huges[v].toLong();
        c1 = static_cast<unsigned char>((templong>>16)&0xFF);
        //cerr << "\nencrypted chars as long: ";
       // cerr << setbase(16) << templong;
        cerr << "\nchar 1: " << c1;
        c2 = static_cast<unsigned char>((templong>>8)&0xFF);
        cerr << "\nchar 2: "  << c2;
       // cerr << "\nSecond char with upper 8 masked: " << (huges[v].toLong()&0x00FF);
        c3 = static_cast<unsigned char>(templong&0xFF);
        cerr << "\nchar 3: " << c3;
        temp+=c1;
        temp+=c2;
        temp+=c3;
        
    }
   // cerr << "\nTemp: " << temp << '\n';
    for (string::size_type i=0; i<temp.size(); i++)
    {
        cerr << setbase(16) << temp[i];
    }
    return temp;
}


huge huge::operator*(const huge & rhs) const
{
    huge returnval;
    char temp;
    char quotient;
    size_t k = numdigits;
    size_t m = rhs.numdigits;
    size_t i, j;
    for (i=0; i < k; i++)
    {
       // cerr << "\nWorking on lhs digit # " << i;
        for (j=0; j < m; j++)
        {
            if (j == 0)
            {
                quotient = 0;
            }
            temp = static_cast<char>(returnval.digits[i+j] 
                 + quotient + (digits[i]*rhs.digits[j]));    
           // cerr << "\nStoring " << static_cast<short>(temp % 10) << " in digit " << i+j;      
            returnval.digits[i+j] = temp % 10;
            quotient = temp/10;           
        }
        //cerr << "\nStoring " << static_cast<short>(quotient) << " in digit " << i+m;
        returnval.digits[i+m] = quotient;   
        
    }
    returnval.numdigits = k+m;
    
    if (returnval.digits[returnval.numdigits-1] == 0)
    {
        returnval.numdigits--;
    }
    if ((sign == -1 && rhs.sign == 1) ||(sign == 1 && rhs.sign == -1))
    {
        returnval.sign = -1;
    }
    else if (sign == 0 || rhs.sign == 0)
    {
        returnval.sign = 0;
    }
    else
    {
        returnval.sign = 1;
    }
    //cerr << "\nThe number of digits in this number is: " << returnval.numdigits;
    return returnval;
}

