
#ifndef HUGE_H
#define HUGE_H
#include <cmath>
#include <string>
#include <vector>
#include <iostream>

const size_t MAX_DIGITS = 10000;

const short CHUNK_SIZE = 5;

const short BASE = 10;

void swap(char & a, char & b);

class huge {

    size_t numdigits;
    char sign;
    char digits[MAX_DIGITS]; 

public:
    huge(void) : numdigits(0), sign(0)
    {
        for(size_t i=0; i<MAX_DIGITS; i++)
        {
            digits[i] = 0;
        }
    }

    huge(const huge & other) : numdigits(other.numdigits), sign(other.sign)
    {
        size_t i;
        for(i=0; i<other.numdigits; i++)
        {
            digits[i] = other.digits[i];
        }
        i = numdigits;
        while (i < MAX_DIGITS)
        {
            digits[i] = 0;
            i++;
        }
    }

    huge(const std::string & other);
    huge(const int & other);
    std::istream & read(std::istream & in);
    std::ostream & print(std::ostream & out) const;
    size_t get_size(void) { return numdigits; }
    huge & operator=(const huge & other);
    huge & operator=(const int & other);
    huge operator+(const huge & rhs) const;
    huge operator+(const int & rhs) const
    {
        huge hrhs = rhs;
        return *this+hrhs;
    }
    char lsb_pop(void);
	//char byteToChar(void);
    huge lsb_push(const char & digit);
    huge operator-(const huge & rhs) const;
    huge operator-(const int & rhs) const;
    huge operator*(const huge & rhs) const;
    huge operator*(const int & rhs) const;
    huge operator--(int)
    {
        *this = *this - 1;
        return *this;
    }
    huge operator++(int)
    {
        *this = *this + 1;
        return *this;
    }
    bool operator>(const huge & rhs) const;
    bool operator>(const int & rhs) const
    {
        huge hrhs = rhs;
        return *this > hrhs;
    }
    bool operator==(const huge & rhs) const;
    bool operator==(const int & rhs) const
    {
        huge hrhs; 
        hrhs = rhs;
        return *this == hrhs;
    }
    bool operator!=(const huge & rhs) const
    {
        return !(*this == rhs);
    }
    huge operator/(const huge & rhs) const;
    huge operator%(const huge & rhs) const;
    huge operator%(const int & rhs) const
    {
        huge hrhs;
        hrhs = rhs;
        return *this % hrhs;
    }

    char byteToChar(void) const
	{
		size_t i;
		huge byteSize("256");
		char ret;
		if (*this > byteSize)
		{
			std::cerr << "This huge is too big to be a byte...\n";
			return 0;
		}
		else
		{
			for (i=0; i<numdigits;i++)
			{
				ret += digits[i] * pow(10, i);
			}
		}
		return ret;
	}
};

inline huge hugePow(const huge & base, const int & exp) 
{
	huge ret=1;
	for (int i=0; i<exp; i++)
	{
		ret = base * ret; 
	}
	return ret;
}



std::istream & operator>>(std::istream & in, huge & num);
std::ostream & operator<<(std::ostream & out, const huge & num);
std::vector<huge> strtohuge(std::string word);
std::string hugetostr(const std::vector<huge> & h);

#endif        //  #ifndef HUGE_H



