/**********
 *
 *    @
 *      @
 *  @ @ @
 *
 **********/

#include "brainfuck.h"

static void execute_inner_block(const char* code, size_t* i, unsigned char* ptr)
{
    while (*ptr) {
        for (; code[*i] && code[*i] != ']'; ++(*i)) {
            switch (code[*i]) {
                case '>':
                    ptr++;
                    break;
                case '<':
                    ptr--;
                    break;
                case '+':
                    ++(*ptr);
                    break;
                case '-':
                    --(*ptr);
                    break;
                case '.':
                    write(STDOUT_FILENO, ptr, 1);
#if PUTCHAR_FLUSHES
                    fsync(STDOUT_FILENO);
#endif
                    break;
                case ',':
                    read(STDIN_FILENO, ptr, 1);
                    break;
                case '[':
                    ++(*i);
                    execute_inner_block(code, i, ptr);
                    --(*i);
                    break;
                default:
                    break;
            }
        }
    }
}

void execute_brainfuck_code(const char* code)
{
    size_t size = MAX_BOXES;
    unsigned char buffer[size];
    while (size) buffer[size--] = 0;
    buffer[0] = 0;
    unsigned char* ptr = buffer;

    for (size_t i = 0; code[i]; ++i) {
        switch (code[i]) {
            case '>':
                ptr++;
                break;
            case '<':
                ptr--;
                break;
            case '+':
                ++(*ptr);
                break;
            case '-':
                --(*ptr);
                break;
            case '.':
                write(STDOUT_FILENO, ptr, 1);
#if PUTCHAR_FLUSHES
                fsync(STDOUT_FILENO);
#endif
                break;
            case ',':
                read(STDIN_FILENO, ptr, 1);
                break;
            case '[':
                ++i;
                execute_inner_block(code, &i, ptr);
                --i;
                break;
            case ']':
                // Well, that's a problem
                break;
            default:
                break;
        }
    }
}