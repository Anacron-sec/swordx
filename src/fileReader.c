#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
//#include "utils.h" //TODO integrare nel makefile

char *openFile(char *);
char *readFile(char *);
int seekFile(FILE *);
void *tok(char *);

int main()
{   
    char* s = openFile("//home//samuele//Desktop//text.txt");
    if(strcmp(s, "errore") == 0) printf("errore");
    return 0;
}

char *openFile(char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return "error";
    else
        return readFile(path);
}

char *readFile(char *path)
{ //rewrite
    FILE *ptrfile = fopen(path, "r");
    int size = seekFile(ptrfile);
    char *buf = (char *)malloc(size * sizeof(char));
    //check_heap(buf);
    fread(buf, size * sizeof(char), 1, ptrfile);
    fclose(ptrfile);
    tok(buf);
    return buf;
}

int seekFile(FILE *ptrfile)
{
    fseek(ptrfile, 0L, SEEK_END);
    int size = ftell(ptrfile);
    fseek(ptrfile, 0L, SEEK_SET);
    return size;
}

void *tok(char *str)
{
    const char delim[2] = " ";
    char *token;

    /* get the first token */
    token = strtok(str, delim);

    /* walk through other tokens */
    while (token != NULL)
    {
        printf("%s\n", token);

        token = strtok(NULL, delim);
    }
}