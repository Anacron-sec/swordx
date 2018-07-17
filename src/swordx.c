#include <stdlib.h>
#include <argp.h>
#include <argz.h>
#include <stdbool.h>
#include <dirent.h>
#include "utils.h"
#include "trie.h"

static void process_file(TriePtr, char *);
static void process_folder(TriePtr, char *);
static char** add_file_to_blacklist(char**, char *);

bool sort_by_occurences = false;
bool recursive = false;
bool follow = false;
bool alpha = false;

char **file_blacklist = NULL;
size_t file_blacklist_size = 0;

/* Used to track if the program found at least one file to process */
bool processing = false;


char *output_file = "swordx.out";

const char *argp_program_bug_address = "michelebiondi01@gmail.com";
const char *argp_program_version = "SwordX version 1.1.1";

struct arguments {
    char *argz;
    size_t argz_len;
};

static int parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *a = state->input;
    switch(key) {
        case 'r': recursive = true; break;
        case 'f': follow = true; break;
        case 'e': file_blacklist = add_file_to_blacklist(file_blacklist, arg); break;
        case 'a': alpha = true; printf("TODO: alpha\n"); break;
        case 'm': {
            long num = strtoul(arg, NULL, 10);
            num ? printf("TODO: minimum -> %ld \n", num) : printf("TOOD: minimum:invalid");
        } break;
        case 'i': printf("TODO: ignore -> %s\n", arg); break;
        case 's': sort_by_occurences = true; break;
        case 'o': {
            output_file = (char *) malloc((strlen(arg) + 1)*sizeof(char)); check_heap(output_file);
            strcpy(output_file, arg);
        } break;
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
        {"follow", 'f', 0, 0, "Follows links."},
        {"exclude", 'e', "<file>", 0, "The specified file is not used for processing."},

        { 0, 0, 0, 0, "Words options:", 2},
        {"alpha", 'a', 0, OPTION_HIDDEN, "Treats only words with alphabet characters."},
        {"min", 'm', "<num>", OPTION_HIDDEN, "Only words with a minimum length of <num> are processed."},
        {"ignore", 'i', "<file>", OPTION_HIDDEN, "Uses target file as a blacklist (words must be written one per line)."},
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
    TriePtr trie;

    if (argp_parse (&argp, argc, argv, 0, 0, &arguments) == 0) {
        
        /* Creates a trie to store words */
        trie = create_trie();

        const char *prev = NULL;
        char *argument;

        // Processes arguments one by one
        while ((argument = argz_next (arguments.argz, arguments.argz_len, prev))) {
            prev = argument;

            //TODO Regexp interpreter

            switch(type_of_file(argument)) {
                case REGULAR_FILE:
                    process_file(trie, argument); break;
                case DIRECTORY:
                    process_folder(trie, argument); break;
                case OTHER:
                    printf("[ERROR] %s: Processing of this type of file is currently not supported.\n", argument); break;
                default:
                    printf("[ERROR] %s: The file doesn't exist.\n", argument);
            }
            
        }

        free (arguments.argz);
    }

    if(processing) {
        writeStatus ws = sort_by_occurences ? write_trie_by_occurrences(trie, output_file) : write_trie(trie, output_file);
        ws == OK_WRITE ? printf("\nResults saved in file %s\n", output_file) : printf("\nError while saving results.\n");
    } else {
        printf("\nNothing to process.\n");
    }
    
    destroy_trie(trie);
    exit(EXIT_SUCCESS);
}

/* AUXILIARY FUNCTIONS */

static void process_file(TriePtr trie, char *argument) {
    
    if(isSymlink(argument) == true && follow == false) {
        printf("[SKIP] Skipping \"%s\", use -f or --follow to follow symbolic links\n", argument);
        return;
    }

    bool file_is_blacklisted = false;
    
    /* Checks if file is blacklised */
    for(int i = 0; i < file_blacklist_size ; i++) {
        if(strcmp(argument, file_blacklist[i]) == 0) file_is_blacklisted = true;
    }

    if(!file_is_blacklisted) {
        if(trie_bulk_insert(trie, argument) == OK_BULK) {
            printf("[OK] Successfully inserted words from: %s\n", argument);
            processing = true;
        } else {
            printf("[ERROR] You don't have permission to read file %s\n", argument);
        }
    } else {
        printf("[SKIP] File %s is blacklisted\n", argument);
    }
}

static void process_folder(TriePtr trie, char *argument) {

    if(isSymlink(argument) == true && follow == false) {
        printf("[SKIP] Skipping \"%s\", use -f or --follow to follow symbolic links\n", argument);
        return;
    }

    printf("Reading files inside directory %s ...\n", argument);
        DIR *dir;
        struct dirent *ent;
        if( (dir = opendir(argument)) != NULL) {
            while((ent = readdir(dir)) != NULL) {
                char *filename = ent->d_name;
                if(strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0) {
                    size_t pathsize = (strlen(argument) + strlen(filename) + 1 + 1 );
                    char* path = (char*) malloc(  pathsize * sizeof(char) ); check_heap(path);
                    strcpy(path, argument);
                    strcat(path, "/");
                    strcat(path, filename);
                    if(type_of_file(path) == REGULAR_FILE) process_file(trie, path);
                    if(type_of_file(path) == DIRECTORY && recursive == true) process_folder(trie, path);
                    free(path);
                }
            }
        }

        printf("Done.\n\n");
}

static char** add_file_to_blacklist(char** blacklist, char *file) {
    char **tmp_blacklist = blacklist;
    

    tmp_blacklist = realloc(blacklist, (file_blacklist_size + 1)*sizeof(char*));
    if(tmp_blacklist != NULL) {
        tmp_blacklist[file_blacklist_size] = (char*) malloc(strlen(file));
        strcpy(tmp_blacklist[file_blacklist_size], file);
    }

    file_blacklist_size++;
    return tmp_blacklist;
}