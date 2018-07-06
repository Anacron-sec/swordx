#include <stdlib.h>
#include <argp.h>
#include <argz.h>
#include "utils.h"

const char *argp_program_bug_address = "michelebiondi01@gmail.com";
const char *argp_program_version = "version 0.0.0";

struct arguments {
    char *argz;
    size_t argz_len;
};

static int parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *a = state->input;
    switch(key) {
        case 'r': printf("recursive\n"); break;
        case 'f': printf("follow\n"); break;
        case 'e': printf("exclude -> %s\n", arg); break;
        case 'a': printf("alpha\n"); break;
        case 'm': {
            long num = strtoul(arg, NULL, 10);
            num ? printf("minimum -> %ld \n", num) : printf("minimum:invalid");
        } break;
        case 'i': printf("ignore -> %s\n", arg); break;
        case 's': printf("Sort by occurences\n"); break;
        case 'o': printf("Output file --> %s\n", arg); break;
                                                                                                                                                                                                                                                                                                                                                                         case 1337: pirate(); break;
        case ARGP_KEY_ARG: {
            argz_add (&a->argz, &a->argz_len, arg);
        } break;
        case ARGP_KEY_INIT: {
            a->argz = 0;
            a->argz_len = 0;
        } break;
        case ARGP_KEY_END:
        {
            size_t arg_count = argz_count(a->argz, a->argz_len);
            if (arg_count <= 0) 
                argp_failure(state, 1, 0, "Expected at least one file to process, use --help for more info.");
        } break;
    }
    return 0;
}

int main(int argc, char **argv)
{
    struct argp_option options[] = {
        {"recursive", 'r', 0, 0, "Follows subdirectories during file processing."},
        {"follow", 'f', 0, 0, "Follows links inside directories."},
        {"exclude", 'e', "<file>", 0, "The specified file is not used for processing."},
        {"alpha", 'a', 0, 0, "Treats only words with alphabet characters."},
        {"min", 'm', "<num>", 0, "Only words with a minimum length of <num> are processed."},
        {"ignore", 'i', "<file>", 0, "Uses target file as a blacklist (words must be written one per line)."},
        {"sortbyoccurrences", 's', 0, 0, "Words inserted in the output file are sorted by occurences."},
        {"output", 'o', "<file>", 0,"Sets the name of the output file."},
                                                                                                                                                                                                                                                                                                                                                                        {"pirate", 1337, 0, OPTION_HIDDEN, "海盜"},
        {0}
    };

    struct argp argp = {
        options, parse_opt, "<input1> <input2> … <inputn>", 
        "Counts the number of word occurences in files and saves the report to a text file."
    };
    struct arguments arguments;
    if (argp_parse (&argp, argc, argv, 0, 0, &arguments) == 0) {
        const char *prev = NULL;
        char *argument;
        while ((argument = argz_next (arguments.argz, arguments.argz_len, prev))) {
            printf ("Called with %s\n", argument);
            prev = argument;
        }
        printf ("\n");
        free (arguments.argz);
    } 
    exit(EXIT_SUCCESS);
}
