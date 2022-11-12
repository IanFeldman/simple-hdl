#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define EXT "module"
#define TOP "top.module"

// returns str ptr to filename extension
char *GetFilenameExt(char *filename) {
    // returns pointer to last occurance of '.'
    char *dot = strrchr(filename, '.');
    // returns null pointer if cannot find char
    if(!dot || dot == filename) return "";
    // return string following '.'
    return dot + 1;
}

// reads files in given directory
// return 0: success
int LookUp(const char *arg) {
    // create dir vars
    DIR *dirp;
    struct dirent *dp;

    // open directory
    if ((dirp = opendir(arg)) == NULL) {
        printf("Error: couldn't open '%s'\n", arg);
        closedir(dirp);
        return 1;
    }

    // found directory
    printf("%s\n", arg);

    int topModule = 0;
    // iterate over files
    while ((dp = readdir(dirp)) != NULL) {
        // check extension
        if (strcmp(GetFilenameExt(dp->d_name), EXT) == 0) {
            // print name
            printf("\u2517%s\n", dp->d_name);
            // check for top
            if (strcmp(dp->d_name, TOP) == 0)
                topModule++;
        }
    }

    // close dir
    closedir(dirp);

    // check that top exists
    if (topModule == 0) {
        printf("Error: 'top' module not found\n");
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // check for correct number of arguments
    if (argc != 2) {
        printf("Error: invalid arguments\n");
        return 1;
    }

    int lookUpStatus = LookUp(argv[1]);
    if (lookUpStatus)
        return 1;

    return 0;
}

