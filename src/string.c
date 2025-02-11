/**********
 *
 *    @
 *      @
 *  @ @ @
 *
 **********/

#include "brainfuck.h"

bool f_strcmp(const char* alpha, const char* bravo)
{
    size_t i = 0;
    for (; alpha[i] == bravo[i] && alpha[i]; ++i);
    return alpha[i] == bravo[i];
}

bool f_anystrcmp(const char* target, const char** src)
{
    for (size_t i = 0; src[i]; ++i)
        if (f_strcmp(target, src[i]))
            return true;
    return false;
}