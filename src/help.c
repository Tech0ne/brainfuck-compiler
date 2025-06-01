/**********
 *
 *    @
 *      @
 *  @ @ @
 *
 **********/

#include "brainfuck.h"

bool handle_help(int argc, const char** argv)
{
    if (argc == 1)
        return true;
    for (int i = 0; i < argc; ++i)
        if (f_anystrcmp(argv[i], (const char*[]){"-h", "--help", 0}))
            return true;
    return false;
}

int display_help(const char* filename, int error_code)
{
    f_display("Usage: "PURPLE, STDOUT_FILENO);
    f_display(filename, STDOUT_FILENO);
    f_display(WHITE" [options]\n", STDOUT_FILENO);
    f_display("  "CYAN"-h | --help"WHITE"                       : Show this help message and exit\n", STDOUT_FILENO);
    f_display("  "CYAN"-s | --source [source file]"WHITE"       : Provide brainfuck source file\n", STDOUT_FILENO);
    f_display("  "CYAN"-c | --code [source code]"WHITE"         : Provide brainfuck source code\n", STDOUT_FILENO);
    f_display("  "CYAN"-o | --output [output C filename]"WHITE" : Provide output C code  filename\n", STDOUT_FILENO);
    f_display("  "CYAN"-e | --execute"WHITE"                    : Execute provided source code\n\n", STDOUT_FILENO);
    f_display("You "BLUE"need"WHITE" one of each -o/-e and -s/-c :\n", STDOUT_FILENO);
    f_display("  "GREEN, STDOUT_FILENO);
    f_display(filename, STDOUT_FILENO);
    f_display(" -o \"./some_display.c\" -c \"++++++++[>+++++++++<-]>.<++++++++++.\""WHITE, STDOUT_FILENO);
    f_display(WHITE"\nThat command will compile the given code into a \""RED"./some_display.c"WHITE"\" file\n", STDOUT_FILENO);
    f_display("Feel free to check out the associated "YELLOW"README"WHITE" file for more explanations on how BrainFuck works\n", STDOUT_FILENO);

    return error_code;
}

int display_error(const char* filename, const char* message, int error_code)
{
    f_display(PURPLE, STDOUT_FILENO);
    f_display(filename, STDOUT_FILENO);
    f_display(WHITE": "RED, STDOUT_FILENO);
    f_display(message, STDOUT_FILENO);
    f_display(WHITE"\n\n", STDOUT_FILENO);
    return display_help(filename, error_code);
}
