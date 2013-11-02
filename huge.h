#ifndef HUGE_H
#define HUGE_H
#include <cmath>
#include <string>
#include <vector>

const size_t MAX_DIGITS = 100;

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
    huge operator-(const huge & rhs) const;
    huge operator-(const long & rhs) const;
    huge operator*(const long & rhs) const;
    huge operator*(const huge & rhs) const;

    bool operator>(const huge & rhs) const
    {
        bool returnval = false;
        size_t i = numdigits-2;
       // std::cerr << "\nOperator > passed *this = ";
      //  this->print(std::cerr);
        //std::cerr << " and rhs = ";
       // rhs.print(std::cerr);
      //  std::cerr << '\n';
       // std::cerr << "\nleft hand digits = " << numdigits;
        //std::cerr << "\nright hand digits = " << rhs.numdigits;
       // std::cerr << "\nleft hand sign = " << static_cast<char>(sign+'0');
       // std::cerr << "\nright hand sign = " << static_cast<char>(rhs.sign+'0');
        if (*this == rhs)
        {
           // std::cerr << "\nPre test for equality";
            returnval = false;
        }
        else if ((numdigits == rhs.numdigits) && 
                 (digits[numdigits-1] == rhs.digits[rhs.numdigits-1]) 
                   && (sign == 1 && rhs.sign == 1))
        {
          //  std::cerr << "\nfirst if in > operator";
            while (digits[i] == rhs.digits[i] && i != 0 )
            {
             //   std::cerr << "\nComparing left hand digit: " 
                 //         << static_cast<char>(digits[i] + '0');
            //    std::cerr << " and right hand digit: " << static_cast<char>(rhs.digits[i] + '0');
                i--;
            }
            if (digits[i] <= rhs.digits[i])
            {
                returnval = false;
            }
            else
            {
                returnval = true; 
            }                     
        }
        else if ((numdigits == rhs.numdigits) && 
                 (digits[numdigits-1] > rhs.digits[rhs.numdigits-1])
                 && (sign == 1 && rhs.sign == 1) )
        {
           // std::cerr << "\nthird if in > operator";
            returnval = true;
        }
        else if (numdigits > rhs.numdigits && sign == 1 && rhs.sign == 1)
        {
           // std::cerr << "\nsecond if in > operator?";
            returnval = true;
           // std::cerr << "\n>function is true in first branch...";
        }
        
        
        else if (sign == 1 && rhs.sign == -1)
        {
           // std::cerr << "\nfourth if in > operator";
            returnval = true;
        }
        else if (sign == 1 && rhs.sign == 0)
        {
           // std::cerr << "\nfifth if in > operator";
            returnval = true;
        }
        else if (sign == -1 && rhs.sign == 1)
        {
            //std::cerr << "\nsixth if in > operator";
            returnval = false;
        }
        else if(numdigits > rhs.numdigits && sign == -1
                           && rhs.sign == -1)
        {
            //std::cerr << "\nseventh if in > operator";
            returnval = false;
        } 
        else if (numdigits == rhs.numdigits && 
                 digits[numdigits-1] == rhs.digits[rhs.numdigits-1] 
                   && sign == -1 && rhs.sign == -1)
        {
            while (digits[i] == rhs.digits[i] && i != 0 )
            {
                //std::cerr << "\nComparing left hand digit: " 
                 //         << static_cast<char>(digits[i] + '0');
                //std::cerr << " and right hand digit: " << static_cast<char>(rhs.digits[i] + '0');
                i--;
            }
            if (digits[i] <= rhs.digits[i])
            {
                returnval = true;
            }
            else
            {
                returnval = false; 
            }                     
        }

        //std::cerr << "\nOr in huge > huge??";
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
    huge operator/(const long & rhs) const
    {
        huge hrhs;
        hrhs = rhs;
        return *this/hrhs;
    }
    huge operator%(const huge & rhs) const
    {   
       // huge holder;
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
std::vector<huge> readWord(std::string word);
std::string printWord(std::vector<huge> huges);
#endif        //  #ifndef HUGE_H



