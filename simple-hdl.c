#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define EXT "module"

char *get_filename_ext(char *filename) {
    // returns pointer to last occurance of '.'
    char *dot = strrchr(filename, '.');
    // returns null pointer if cannot find char
    if(!dot || dot == filename) return "";
    // return string following '.'
    return dot + 1;
}

void lookup(const char *arg)
{
    // create dir vars
    DIR *dirp;
    struct dirent *dp;

    // open directory
    if ((dirp = opendir(arg)) == NULL) {
        printf("couldn't open '%s'\n", arg);
        return;
    }

    // found directory
    printf("%s\n", arg);

    // iterate over files
    while ((dp = readdir(dirp)) != NULL) {
        if (strcmp(get_filename_ext(dp->d_name), EXT) == 0)
            printf("\u2517%s\n", dp->d_name);
    }

    closedir(dirp);
}

int main(int argc, char *argv[])
{
    // check for correct number of arguments
    if (argc != 2) {
        printf("invalid arguments\n");
        return 1;
    }

    lookup(argv[1]);
    return 0;
}

