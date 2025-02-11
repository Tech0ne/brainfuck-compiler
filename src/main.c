/**********
 *
 *    @
 *      @
 *  @ @ @
 *
 **********/

#include "brainfuck.h"

int main(int argc, const char** argv)
{
    if (handle_help(argc, argv))
        return display_help(argv[0], 0);

    bool output_execute = false;
    bool input_filename = false;
    char* output = NULL;
    char* input = NULL;

    for (int i = 1; i < argc; ++i) {
        if (f_anystrcmp(argv[i], (const char*[]){"-s", "--source", 0})) {
            if (input)
                return display_error(argv[0], "Multiple inputs provided", 1);
            input = *(char**)&argv[++i];
            input_filename = true;
        } else if (f_anystrcmp(argv[i], (const char*[]){"-c", "--code", 0})) {
            if (input)
                return display_error(argv[0], "Multiple inputs provided", 1);
            input = *(char**)&argv[++i];
        } else if (f_anystrcmp(argv[i], (const char*[]){"-o", "--output", 0})) {
            if (output || output_execute)
                return display_error(argv[0], "Multiple outputs provided", 1);
            output = *(char**)&argv[++i];
        } else if (f_anystrcmp(argv[i], (const char*[]){"-e", "--execute", 0})) {
            if (output || output_execute)
                return display_error(argv[0], "Multiple outputs provided", 1);
            output_execute = true;
        } else {
            return display_error(argv[0], "Invalid parameter", 1);
        }
    }

    if (!input || (input[0] == '-' && input_filename))
        return display_error(argv[0], "Missing input parameter", 1);
    if (!output_execute && (!output || output[0] == '-'))
        return display_error(argv[0], "Missing output parameter", 1);

    run_with_input(input, input_filename, (output_execute ? -1 : open_output_file(output)));
}