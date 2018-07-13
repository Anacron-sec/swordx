#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
//#include "utils.h" //TODO integrare nel makefile

char *openFile(char *);
char *readFile(char *);
int seekFile(FILE *);
char *tok(char *);

int main()
{
    printf("%s\n", openFile("//home//samuele//Desktop//text.txt"));
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
    /*for (int i = 0; i < size; i++)
    {
        putc(buf[i], stdout);
    }*/
    fclose(ptrfile);
    return buf;
}

int seekFile(FILE *ptrfile)
{
    fseek(ptrfile, 0L, SEEK_END);
    int size = ftell(ptrfile);
    fseek(ptrfile, 0L, SEEK_SET);
    return size;
}

char *tok(char *str)
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

    return "done";
}