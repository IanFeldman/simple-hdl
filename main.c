#include <stdio.h>
#include <string.h>

#define EXT "module"
#define WORDWIDTH 8
#define MAXPORTS 32 

struct port {
    char name[WORDWIDTH];
    int value;
    char type; // i, o, l
};

// returns str ptr to filename extension
char *GetFilenameExt(char *filename) {
    // returns pointer to last occurance of '.'
    char *dot = strrchr(filename, '.');
    // returns null pointer if cannot find char
    if(!dot || dot == filename) return "";
    // return string following '.'
    return dot + 1;
}

int Nand(int a, int b) {
    if (a && b) return 0;
    return 1;
}

int Simulate(char *entryFile) {
    // open file
    FILE *fp;
    char buff[WORDWIDTH];

    fp = fopen(entryFile, "r");
    if (fp == NULL) {
        perror("Error");
        return 1;
    }

    struct port ports[MAXPORTS];
    int portCount = 0;

    // get word
    while (fscanf(fp, "%s", buff) != EOF) {
        // io ports
        // input
        if (!strcmp(buff, "input")) {
            struct port p;
            fscanf(fp, "%s", p.name);
            fscanf(fp, "%d", &p.value); // scan in val for now
            p.type = 'i';
            ports[portCount] = p;
            portCount++;
        }
        // output
        else if (!strcmp(buff, "output")) {
            struct port p;
            fscanf(fp, "%s", p.name);
            p.value = 0;
            p.type ='o';
            ports[portCount] = p;
            portCount++;
        }
        // logic
        else if (!strcmp(buff, "logic")) {
            struct port p;
            fscanf(fp, "%s", p.name);
            p.value = 0;
            p.type = 'l';
            // check for init
            FILE* fpNext = fp;
            fscanf(fpNext, "%s", buff);
            if (!strcmp(buff, "=")) {
                fscanf(fpNext, "$d", &p.value);
                fp = fpNext;
            }
            ports[portCount] = p;
            portCount++;
        }
        // functionality
        else if (!strcmp(buff, "nand")) {
            // find input 1
            struct port *in1;
            fscanf(fp, "%s", buff);
            int found = 0;
            for (int i=0; i<portCount; i++) {
                if (ports[i].type == 'o') continue;
                if (!strcmp(ports[i].name, buff)) {
                    in1 = &ports[i];
                    found = 1;
                }
            }
            if (!found) {
                printf("Error: no such port '%s'\n", buff);
                return 1;
            }

            // find input 2
            struct port *in2;
            fscanf(fp, "%s", buff);
            found = 0;
            for (int i=0; i<portCount; i++) {
                if (ports[i].type == 'o') continue;
                if (!strcmp(ports[i].name, buff)) {
                    in2 = &ports[i];
                    found = 1;
                }
            }
            if (!found) {
                printf("Error: no such port '%s'\n", buff);
                return 1;
            }

            // find output
            struct port *out;
            fscanf(fp, "%s", buff);
            found = 0;
            for (int i=0; i<portCount; i++) {
                if (ports[i].type == 'i') continue;
                if (!strcmp(ports[i].name, buff)) {
                    out = &ports[i];
                    found = 1;
                }
            }
            if (!found) {
                printf("Error: no such port '%s'\n", buff);
                return 1;
            }

            in2->value = Nand(in1->value, in2->value);
            printf("%d\n", in2->value);
        }
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

    if (strcmp(GetFilenameExt(argv[1]), EXT) != 0) {
        printf("Error: entry point must be a .%s file\n", EXT);
        return 1;
    }

    // evaluate
    //printf("%i\n", Simulate(argv[1]));
    Simulate(argv[1]);

    return 0;
}

