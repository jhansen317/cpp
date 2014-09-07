
#ifndef HUGE_H
#define HUGE_H
#include <cmath>
#include <string>
#include <vector>

const size_t MAX_DIGITS = 10000;

const short BASE = 10;

void swap(char & a, char & b);

class huge {
    
    char digits[MAX_DIGITS]; 
    char sign;
    size_t numdigits;
    
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
    huge(const std::string & other) : numdigits(0), sign(0)
    {
         size_t zeros, beg, end;
         numdigits = 0;
         std::string::size_type i=0;
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
    
    
    
    huge(const long & other) : numdigits(0), sign(0)
    {
        //std::cerr << "\nProblem in huge = long operator";
        size_t i;
        long digit = 10;
        
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
            sign = 0;
        }
        
        if (other < 10)
        {
            //std::cerr << "\nother = " << other;
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
    huge(const unsigned long & other) : numdigits(0), sign(0)
    {
        //std::cerr << "\nProblem in huge = long operator";
        size_t i;
        unsigned long digit = 10;

        while (other % digit <= std::abs(other))
        {
            digits[numdigits] = static_cast<char>((other % digit)/ (digit/BASE));
            numdigits++;
            digit *= BASE;
        }
    
        i = numdigits;
        while (i < MAX_DIGITS)
        {
            digits[i] = 0;
            i++;
        }

    }
    
    size_t get_size(void)
    {
        return numdigits;
    }
    long toLong(void)
    {
        size_t i=0;
        long returnval=0, place = 1;
        
        while(i < numdigits)
        {
            returnval += digits[i] * place;
            place*=BASE;
            i++;
        }
        return returnval;
    }
    huge & operator=(const huge & other)
    {
        size_t i;
       // std::cerr << "\nGot into huge = huge operator";
        for(size_t i=0; i<other.numdigits; i++)
        {
           // std::cerr << "\ncopying digit: " << i;
           // std::cerr << " Which is " << static_cast<char>(other.digits[i]+'0');
            digits[i] = other.digits[i];
           // std::cerr << "\nCopied version is: " << static_cast<char>(digits[i]+'0');
        }
        sign = other.sign;
        numdigits = other.numdigits;
        i = numdigits;
        while (i < MAX_DIGITS)
        {
            digits[i] = 0;
            i++;
        }
        //std::cerr << "\n*this is now: " << *this;
        return *this;
    }
    huge & operator=(const long & other)
    {
        long digit = 10;
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
            //std::cerr << "\nstoring " << std::abs(other) << " in lsb";
            numdigits = 1;
        }
        else
        {
            while (other % (digit/BASE) < std::abs(other))
            {
            //std::cerr << "\nother % (digit/BASE) = " << other % (digit/BASE);
            //std::cerr << "\n(other % digit)/ (digit/BASE) = " << (other % digit)/ (digit/BASE);
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
    huge & operator=(const short & other)
    {
        long digit = 10;
        numdigits=0;
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
            sign = 0;
        }
        if (other < 10)
        {
            digits[0] = std::abs(other);
            numdigits = 1;
        }
        else
        {
            while (other % (digit/BASE) <= std::abs(other))
            {
                digits[numdigits] = static_cast<char>((other % digit)/ (digit/BASE));
                numdigits++;
                digit *= BASE;
            }
        }
        return *this;
    }
    huge operator+(const huge & rhs) const;
    huge operator+(const long & rhs) const
    {
        huge hrhs = rhs;
        return *this+hrhs;
    }
    char lsb_pop(void)
    {
        char returnChar = digits[0];
        short i;
        for (i = 1; i<numdigits; i++)
        {
            digits[i-1] = digits[i]; // shift everything toward LSB
        }
        if (numdigits > 0)
            numdigits--;

//        std::cerr << "\nreturnChar is " << static_cast<char>(returnChar+'0');
        return returnChar;
    }
    huge append(const char & digit)
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
    huge operator-(const huge & rhs) const;
    huge operator-(const long & rhs) const;
    huge operator*(const long & rhs) const;
    huge operator*(const huge & rhs) const;
    huge operator--(int)
    {
        *this = *this - static_cast<long>(1);
        return *this;
    }
    bool operator>(const huge & rhs) const
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
    bool operator>(const long & rhs) const
    {
        huge hrhs = rhs;
        //std::cerr << "\nProblem in huge > long??";
        return *this > hrhs;
    }
    bool operator==(const huge & rhs) const
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
    bool operator!=(const huge & rhs) const
    {
        return !(*this == rhs);
    }
    bool operator==(const short & rhs) const
    {
        huge hrhs; 
        hrhs = rhs;
        return *this == hrhs;
    }
    bool operator==(const long & rhs) const
    {
        huge hrhs; 
        hrhs = rhs;
        return *this == hrhs;
    }
    huge operator/(const huge & rhs) const;
    /*huge operator/(const long & rhs) const
    {
        huge hrhs;
        hrhs = rhs;
        return *this/hrhs;
    }*/
    huge operator%(const huge & rhs) const
    {   
        //return *this - (rhs * (*this/rhs));
        huge holder;
        if (rhs == static_cast<long>(1) || 
           (rhs == static_cast<long>(2) && digits[0] % 2 == 0))
        {
            //std::cerr << "\nmod 2 test works!";
            return static_cast<long>(0);
        }
        else if (*this > rhs)
        {
          //  std::cerr << "\nFirst branch of operator %";
          //  holder = *this/rhs;
          //  std::cerr << "\n*this/rhs = ";
         //   holder.print(std::cerr);
         //   holder = (*this/rhs)*rhs;
         //   std::cerr << "\n*this/rhs*rhs = ";
         //   holder.print(std::cerr);
            //std::cin.ignore(INT_MAX, '\n');
            return *this - ((*this / rhs) * rhs);
        }
        else if (*this == rhs)
        {
            return static_cast<long>(0);
        }
        
        else
        {
           // std::cerr << "\nElse branch of operator %";
            //std::cin.ignore(INT_MAX, '\n');
            return *this;
        }
    }
    huge operator%(const long & rhs) const
    {
        huge hrhs;
        hrhs = rhs;
        return *this % hrhs;
    }
    std::istream & read(std::istream & in);
    std::ostream & print(std::ostream & out) const;
    
};


std::istream & operator>>(std::istream & in, huge & num);
std::ostream & operator<<(std::ostream & out, const huge & num);
huge readWord(std::string word);
std::string printWord(const huge h);
#endif        //  #ifndef HUGE_H



