#ifndef RAND_LETTER_INC
#define RAND_LETTER_INC
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>

static const char letters[] = "abcdefghijklmnopqrstuvwxyz";
static const size_t L_SIZE = 25;

char RandLetter(void);

std::string RandString(size_t s);

#endif
