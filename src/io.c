/**********
 *
 *    @
 *      @
 *  @ @ @
 *
 **********/

#include "brainfuck.h"

static size_t get_file_size(const char* filename)
{
    struct stat st;
    stat(filename, &st);
    if (st.st_size < 0)
        return 0;
    return (size_t)st.st_size;
}

int open_output_file(const char* filename)
{
    return open(filename, O_RDWR | O_CREAT | O_TRUNC, 0664);
}

void run_with_input(const char* input, bool is_input_file, int output)
{
    char* ptr = *(char**)(&input);
    if (is_input_file) {
        size_t buffer_size = get_file_size(input);

        char buffer[buffer_size + 1];
        int fd = open(input, O_RDONLY);
        read(fd, buffer, buffer_size);
        ptr = buffer;
    }

    if (output == -1) {
        execute_brainfuck_code(ptr);
        return;
    }
    add_base_code(output);
    add_bf_code(output, ptr);
    add_closing_code(output);
}