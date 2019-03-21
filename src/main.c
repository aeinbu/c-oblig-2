#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "lib.h"


const char *COMMAND_ENCODE = "e";
const char *COMMAND_DECODE = "d";
const char *COMMAND_PRINT = "p";


int main(int argc, char *argv[]) {
    assert(argc > 2);
    char *command = argv[1];

	FILE *fromFile = argc >= 3 ? fopen(argv[2], "r") : stdin;
	FILE *toFile = argc >= 4 ? fopen(argv[3], "w") : stdout;

    if (strncmp(COMMAND_ENCODE, command, 2) == 0) {

        encode(fromFile, toFile);

    }
    if (strncmp(COMMAND_DECODE, command, 2) == 0) {

        decode(fromFile, toFile);

    }
    if (strncmp(COMMAND_PRINT, command, 2) == 0) {
        FILE *toFile = stdout;

        decode(fromFile, toFile);
    }

	if(fromFile != stdin) fclose(fromFile);
	if(toFile != stdout) fclose(toFile);
}
