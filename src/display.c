/**********
 *
 *    @
 *      @
 *  @ @ @
 *
 **********/

#include "brainfuck.h"

void f_display(const char* data, int fd)
{
    size_t i = 0;
    while (data[i])
        write(fd, &data[i++], 1);
}