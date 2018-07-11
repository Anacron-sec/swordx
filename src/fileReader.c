#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
char *testFile(char *);
char *readFile(char *);

char *testFile(char *path)
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
}