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
huge::huge(const string & other) : numdigits(0), sign(0)
{
    size_t zeros, beg, end;
    string::size_type i=0;
    if (other[0] == '-')
    {
        i = 1;
        sign = -1;
    }
    else if (other[0] == '0')
    {
        sign = 0;
        i = other.size();
    }
    else
    {
        sign = 1;
    }
    

    while (i < other.size() && 
            numdigits < MAX_DIGITS && isdigit(other[i]))
    {
        digits[numdigits] = static_cast<char>(other[i]-'0');
        numdigits++;
        i++;
    }
    for (zeros = numdigits; zeros < MAX_DIGITS; zeros++)
    {
        digits[zeros] = 0; 
    }
    for (beg=0, end=numdigits-1; beg < numdigits/2; beg++, end--)
    {
        swap(digits[beg], digits[end]);
    }
}
huge::huge(const int & other) : numdigits(0), sign(0)
{
    size_t i;
    int digit = 10;
        
    sign = (other < 0) ? -1 : 
           (other > 0) ? 1 : 0;
        
    if (other < 10)
    {
        digits[0] = std::abs(other);
        numdigits = 1;
    }
    else
    {
        while (other % digit <= std::abs(other))
        {
            digits[numdigits] = static_cast<char>((other % digit)/ (digit/BASE));
            numdigits++;
            digit *= BASE;
        }
    }
    i = numdigits;
    while (i < MAX_DIGITS)
    {
        digits[i] = 0;
        i++;
    }
}
huge & huge::operator=(const huge & other)
{
    size_t i;
    for(size_t i=0; i<other.numdigits; i++)
    {
        digits[i] = other.digits[i];
    }
    sign = other.sign;
    numdigits = other.numdigits;
    i = numdigits;
    while (i < MAX_DIGITS)
    {
        digits[i] = 0;
        i++;
    }
    return *this;
}
huge & huge::operator=(const int & other)
{
    int digit = 10;
    numdigits=0;
    size_t i;
    if (other < 0)
    {
        sign = -1;
    }
    else if (other > 0)
    {
        sign = 1;
    }
    else
    {
        digits[0] = 0;
        sign = 0;
        numdigits = 1;
    }
    if ((other < 10 && other > 0) || (other < 0 && other > -10))
    {
        digits[0] = std::abs(other);
        numdigits = 1;
    }
    else
    {
        while (other % (digit/BASE) < std::abs(other))
        {
            digits[numdigits] = static_cast<char>((other % digit)/ (digit/BASE));
            numdigits++;
            digit *= BASE;
        }
    }
    i = numdigits;
    while (i < MAX_DIGITS)
    {
        digits[i] = 0;
        i++;
    }
return *this;
}

bool huge::operator>(const huge & rhs) const
{
    bool returnval = false;
    size_t i;
    if (*this == rhs)
    {
        return false;
    }
    else if (sign == 1 && rhs.sign == 1)
    {
        if (numdigits == rhs.numdigits)
        {
            i = numdigits-1;
            while (i != 0 && digits[i] == rhs.digits[i])
            {
                i--;
            }
            return (digits[i] > rhs.digits[i]);
        }
        else
        {
            return (numdigits > rhs.numdigits);
        }
    }
    else if (sign == -1 && rhs.sign == -1)
    {
        if (numdigits == rhs.numdigits)
        {
            i = numdigits-1;
            while (digits[i] == rhs.digits[i] && i != 0 )
            {
                i--;
            }
                return !(digits[i] > rhs.digits[i]);
        }
        else
        {
            return !(numdigits > rhs.numdigits);
        }

    }
    else if (sign != rhs.sign)
    {
        return (sign > rhs.sign);
    }
    return returnval;
}
bool huge::operator==(const huge & rhs) const
{     
    size_t i = 0;
    bool returnval = false;
    if (numdigits == 1 && rhs.numdigits == 1 && digits[0] == rhs.digits[0])
    {
        returnval = true;
    }
    else if (numdigits == rhs.numdigits && sign == rhs.sign)
    {
        while (i < numdigits && digits[i] == rhs.digits[i])
        {
            i++;
        }
        if (i == numdigits)
        {
            returnval = true;
        }
        else
        {
            returnval = false;
        }
    }
    else
    {
        returnval = false;
    }
    return returnval;
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
        storage = *this;
        storage.sign = 1;
        temp = rhs - storage;
    }
    else if ((sign == 1 || sign == 0) && rhs.sign == 1)
    {
        while (i<longest)
        {
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
    
    if (numdigits >= rhs.numdigits)
    {
        longest = numdigits;
    }
    else
    {
        longest = rhs.numdigits;
    }
    if (*this > rhs && (sign == 1 && rhs.sign ==1))
    {
        while (i<longest)
        {
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
    }
    else if (rhs > *this && (sign == 1 && rhs.sign ==1))
    {
        temp = rhs - *this;
        temp.sign = -1;
    }
    else if (sign == -1 && rhs.sign == -1)
    {
        storage = *this;
        storage.sign = 1;
        storage2 = rhs;
        storage2.sign = 1;
        temp = storage - storage2;            
        temp.sign = -1;
    }
    else if (sign == -1 && rhs.sign == 1)
    {
        storage = *this;
        storage.sign = 1;
        temp = storage + rhs;
        temp.sign = -1;
    }
    else if (sign == 1 && rhs.sign == -1)
    {
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


huge huge::operator-(const int & rhs) const
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
huge huge::operator*(const int & rhs) const
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
        tempdividend = tempremainder.lsb_push(digits[i-1]);
        tempquotient = static_cast<long>(10);
        while((divisor * tempquotient) > tempdividend)
        {
            tempquotient--;
        }
        quotient.lsb_push(tempquotient.digits[0]);
        tempremainder = tempdividend - (tempquotient*divisor);
    }
    quotient.sign = (sign == divisor.sign) ? 1 : -1;
    return quotient;
}
char huge::lsb_pop(void)
{
    char returnChar = digits[0];
    size_t i;
    for (i = 1; i<numdigits; i++)
    {
        digits[i-1] = digits[i]; // shift everything toward LSB
    }
    if (numdigits > 0)
        numdigits--;
    return returnChar;
}

huge huge::lsb_push(const char & digit)
{
    if (numdigits == 0)
    {
        if (digit == 0)
        {
            numdigits++;
        }
        else
        {
            numdigits++;
            sign = 1;
            digits[0] = digit;
        }
            
    }
    else if (numdigits == 1 && digits[0] == 0 && digit == 0)
    {
        return *this;
    }
    else if (numdigits == 1 && digits[0] == 0 && digit > 0)
    {
        digits[0] = digit;
        sign = 1;
    }        
    else
    {
        for (size_t i = numdigits; i > 0; i--)
        {
            digits[i] = digits[i-1];
        }
        digits[0] = digit;
        sign = 1;
        numdigits++;
    }
    return *this;
}

vector<huge> strtohuge(string word)
{
	huge temp, holder, multiplier, base("256");
    vector<huge> cont;
    char hundreds, tens, ones;
	string::size_type i=0, k=0, numChunks = 0, remainder=0;
	numChunks = word.size() / CHUNK_SIZE;
	remainder = word.size() % CHUNK_SIZE; 

	temp = 0;
	k = 0;
	// process complete chunks
	while (i < numChunks)
	{
		k = 0;
		temp = 0;
	    while (k<CHUNK_SIZE)
   		{
			multiplier = hugePow(base, k);
			holder = multiplier * static_cast<int>(word[(i*CHUNK_SIZE)+k]);
        	temp = temp + holder;
			k++;
    	}
		cont.push_back(temp);
		i++;
	}

	k = 0;
	temp = 0;
	// process remaining partial chunk and pad with zeros
	while (k < remainder)
	{
		multiplier = hugePow(base, k);
		holder = multiplier * static_cast<int>(word[(i*CHUNK_SIZE)+k]);
        temp = temp + holder;
		k++;		
	}
	if (remainder > 0)
	{	
		cont.push_back(temp);
	}
    return cont;
}


string hugetostr(const vector<huge> & h)
{
    huge temp = 0, holder = 0, divisor, base("256");
	string ret;
    char swp;
    char tempChar;

	for (vector<huge>::size_type i=0; i < h.size(); i++)
	{
		for (int k=0; k<CHUNK_SIZE; k++)
		{
			divisor = hugePow(base, k);
			holder = (h[i]/divisor) % base;
			tempChar = holder.byteToChar();
			if (tempChar != 0)
			{
				ret += tempChar;
			}
		}
	}

    return ret;
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

huge huge::operator%(const huge & rhs) const
{   
    huge holder;
    if (rhs == 1 || (rhs == 2 && digits[0] % 2 == 0))
    {
        return huge(0);
    }
    else if (*this > rhs)
    {
        return *this - ((*this / rhs) * rhs);
    }
    else if (*this == rhs)
    {
        return huge(0);
    }
    else
    {
        return *this;
    }
}
