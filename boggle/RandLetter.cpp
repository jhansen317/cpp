#include "RandLetter.h"

char RandLetter(void)
{
    return letters[ rand() % L_SIZE ];
}

std::string RandString(size_t s)
{
    std::string ret;
    for (size_t i = 0; i < s; i++)
    {
        ret += RandLetter();
    }   
    return ret;
}
