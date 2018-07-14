#include <stdlib.h>
#include <argp.h>
#include <argz.h>
#include "utils.h"
#include "trie.h"

int sort_by_occurences = 0;

const char *argp_program_bug_address = "michelebiondi01@gmail.com";
const char *argp_program_version = "SwordX version 0.0.0";

struct arguments {
    char *argz;
    size_t argz_len;
};

static int parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *a = state->input;
    switch(key) {
        case 'r': printf("TODO: recursive\n"); break;
        case 'f': printf("TODO: follow\n"); break;
        case 'e': printf("TOOD: exclude -> %s\n", arg); break;
        case 'a': printf("TODO: alpha\n"); break;
        case 'm': {
            long num = strtoul(arg, NULL, 10);
            num ? printf("TODO: minimum -> %ld \n", num) : printf("TOOD: minimum:invalid");
        } break;
        case 'i': printf("TODO: ignore -> %s\n", arg); break;
        case 's': sort_by_occurences = 1; break;
        case 'o': printf("TOOD: Output file --> %s\n", arg); break;
                                                                                                                                                                                                                                                                                                                                                                         case 1337: pirate(); break;
        /* Main arguments */
        case ARGP_KEY_INIT: {
            a->argz = 0;
            a->argz_len = 0;
        } break;
        case ARGP_KEY_ARG: {
            argz_add (&a->argz, &a->argz_len, arg);
        } break;
        case ARGP_KEY_END:
        {
            size_t arg_count = argz_count(a->argz, a->argz_len);
            if (arg_count <= 0) 
                argp_failure(state, 1, 0, "Expected at least one file to process. Use --help for more info.");
        } break;
    }
    return 0;
}

int main(int argc, char **argv)
{
    struct argp_option options[] = {
        { 0, 0, 0, 0, "Files and folders options:", 1},
        {"recursive", 'r', 0, 0, "Follows subdirectories during file processing."},
        {"follow", 'f', 0, 0, "Follows links inside directories."},
        {"exclude", 'e', "<file>", 0, "The specified file is not used for processing."},

        { 0, 0, 0, 0, "Words options:", 2},
        {"alpha", 'a', 0, 0, "Treats only words with alphabet characters."},
        {"min", 'm', "<num>", 0, "Only words with a minimum length of <num> are processed."},
        {"ignore", 'i', "<file>", 0, "Uses target file as a blacklist (words must be written one per line)."},
        {"sortbyoccurrences", 's', 0, 0, "Words inserted in the output file are sorted by occurences."},

        { 0, 0, 0, 0, "Output Options:", 3},
        {"output", 'o', "<file>", 0,"Sets the name of the output file."},

                                                                                                                                                                                                                                                                                                                                                                        {"pirate", 1337, 0, OPTION_HIDDEN, "海盜"},
        
        { 0, 0, 0, 0, "Informational Options:", -1},
        {0}
    };

    struct argp argp = {
        options, parse_opt, "<input1> <input2> … <inputn>", 
        "Counts the number of word occurences in the specified files and saves the report to a text file."
    };
    struct arguments arguments;

    // Creates trie to hold words
    TriePtr trie = create_trie();

    // Processes arguments one by one
    if (argp_parse (&argp, argc, argv, 0, 0, &arguments) == 0) {
        const char *prev = NULL;
        char *argument;
        while ((argument = argz_next (arguments.argz, arguments.argz_len, prev))) {
            //TODO Regexp interpreter
            trie_bulk_insert(trie, argument) == OK_BULK ? 
                printf("Successfully inserted words from: %s\n", argument) : printf("Couldn't read: %s\n", argument);
            
            prev = argument;
        }

        free (arguments.argz);
    }

    writeStatus ws = sort_by_occurences ? write_trie_by_occurrences(trie, "swordx.out") : write_trie(trie, "swordx.out");
    ws == OK_WRITE ? printf("\nResults saved in file swordx.out\n") : printf("\nError while saving results.\n");
    
    destroy_trie(trie);
    exit(EXIT_SUCCESS);
}
