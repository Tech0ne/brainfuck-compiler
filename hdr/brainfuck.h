/**********
 *
 *    @
 *      @
 *  @ @ @
 *
 **********/

#ifndef INCLUDED_BRAINFUCK_H
    #define INCLUDED_BRAINFUCK_H

    #include <fcntl.h>
    #include <sys/stat.h>
    #include <unistd.h>

    #include "configs.h"

typedef unsigned char bool;

void f_display(const char* data, int fd);
bool f_strcmp(const char* alpha, const char* bravo);
bool f_anystrcmp(const char* target, const char** src);
bool handle_help(int argc, const char** argv);
int display_help(const char* filename, int error_code);
int display_error(const char* filename, const char* message, int error_code);

void add_base_code(int fd);
void add_bf_code(int fd, const char* bf_code);
void add_closing_code(int fd);

void execute_brainfuck_code(const char* code);

int open_output_file(const char* filename);
void run_with_input(const char* input, bool is_input_file, int output);

#endif