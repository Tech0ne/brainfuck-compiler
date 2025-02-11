/**********
 *
 *    @
 *      @
 *  @ @ @
 *
 **********/

#include "brainfuck.h"

static bool is_in(char c, const char* str)
{
    for (size_t i = 0; str[i]; ++i)
        if (str[i] == c)
            return true;
    return false;
}

static void write_size_t_to_file(int fd, size_t value)
{
    size_t q = value / 10;
    size_t r = (value % 10) + '0';
    if (!q) {
        write(fd, &r, 1);
        return;
    }
    write_size_t_to_file(fd, q);
    write(fd, &r, 1);
}

// Not quite beautifull, but keeps it simple
void add_base_code(int fd)
{
    write(fd, "// Made with <3 by Tech0ne\n\n\
#include <unistd.h>\n\
int main()\n\
{\n\
    unsigned long size = ", 86);

    write_size_t_to_file(fd, MAX_BOXES);

    write(fd, ";\n\
    unsigned char buffer[size];\n\
    while(size) buffer[size--] = 0;\n\
    buffer[0] = 0;\n\
    unsigned char* p = buffer;\n\n\
    // Actual code:\n\n", 142);
}

void add_bf_code(int fd, const char* bf_code)
{
    bool commenting = false;
    bool is_new_line = true;
    size_t indent = 1;
    for (size_t i = 0; bf_code[i]; ++i) {
        if (bf_code[i] == '/')
            commenting = true;
        if (bf_code[i] == '\n') {
            write(fd, "\n", 1);
            commenting = false;
            is_new_line = true;
        }
        if (commenting || !is_in(bf_code[i], "<>+-.,[]"))
            continue;
        if (bf_code[i] == ']')
            --indent;
        if (is_new_line) {
            for (size_t j = 0; j < indent; ++j)
                write(fd, "    ", 4);
            is_new_line = false;
        } else {
            write(fd, " ", 1);
        }
        switch (bf_code[i]) {
            case '>':
                write(fd, "p++;", 4);
                break;
            case '<':
                write(fd, "p--;", 4);
                break;
            case '+':
                write(fd, "++(*p);", 7);
                break;
            case '-':
                write(fd, "--(*p);", 7);
                break;
            case '.':
                write(fd, "write(STDOUT_FILENO, p, 1);", 27);
#if PUTCHAR_FLUSHES
                write(fd, " fsync(STDOUT_FILENO);", 22);
#endif
                break;
            case ',':
                write(fd, "read(STDIN_FILENO, p, 1);", 25);
                break;
            case '[':
                ++indent;
                write(fd, "while (*p) {", 12);
                break;
            case ']':
                write(fd, "}", 1);
                break;
            default:
                break;
        }
    }
}

void add_closing_code(int fd)
{
    write(fd, "\n\n    // Hope you didn't mess your code up !\n\n    return 0;\n}", 61);
}