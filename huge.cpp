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
        if (temp.numdigits == 1 && temp.digits[0] == 0)
        {
            temp.sign = 0;
        }
        else
        {
            temp.sign = 1;
        }
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

huge huge::operator/(const huge & divisor) const
{
    huge tempdividend, tempremainder, 
         tempquotient, quotient;
    tempremainder = static_cast<long>(0);
    for (size_t i = numdigits; i>0; i--)
    {
        tempdividend = tempremainder.append(digits[i-1]);
        tempquotient = static_cast<long>(10);
        while((divisor * tempquotient) > tempdividend)
        {
            //cerr << "\n" << (divisor*tempquotient) << " is greater than " << tempdividend;
            tempquotient--;
        }
        quotient.append(tempquotient.digits[0]);
        //cerr << "\nAppending: " << tempquotient.digits[0];
        tempremainder = tempdividend - (tempquotient*divisor);
    }
    quotient.sign = (sign == divisor.sign) ? 1 : -1;
    return quotient;
}

huge readWord(string word)
{
    huge temp;
    char hundreds, tens, ones;
    for(short i=0; i<word.size(); i++)
    {
        hundreds = word[i] / 100;
        tens = (word[i] % 100) / 10;
        ones = word[i] % 10;
        temp.append(hundreds);
        temp.append(tens);
        temp.append(ones);

    }
    return temp;
}
string printWord(const huge h)
{
    string temp;
    huge temph = h;
    char swp;
    char tempChar, hundreds, tens, ones;
    while(temph.get_size() != 0)
    {
        tempChar = temph.lsb_pop();
        tempChar += (temph.lsb_pop()*10);
        tempChar += (temph.lsb_pop()*100);
        temp+=tempChar;
    }
    for(short i=0, j=temp.size()-1; i<=(temp.size()/2), j>=(temp.size()/2); i++, j--)
    {
        swp = temp[i];
        temp[i] = temp[j];
        temp[j] = swp;
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

