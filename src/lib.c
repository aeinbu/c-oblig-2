#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

char encodeCharacter(char input) {
    if (input == ' ')
        return 0;
    if (input == ':')
        return 1;
    if (input == '@')
        return 2;
    // if (input == '\n')
        return 3;
}


char decodeCharacter(char input) {
    if (input == 0)
        return ' ';
    if (input == 1)
        return ':';
    if (input == 2)
        return '@';
    // if (input == 3)
        return '\n';
}


char encodeCharacterAndShift(char input[], size_t pos) {
	return encodeCharacter(input[pos]) << 6 >> 2*pos;
	// return encodeCharacter(input[pos]) << 2*(3-pos);
}


void encode(FILE *fromFile, FILE *toFile) {
    assert(fromFile);
    assert(toFile);

    char buffer[4];
    while (fread(buffer, sizeof(char), 4, fromFile) != 0) {
        // read byte(s)

        // encode
        char c =
			encodeCharacterAndShift(buffer, 0) |
			encodeCharacterAndShift(buffer, 1) |
			encodeCharacterAndShift(buffer, 2) |
			encodeCharacterAndShift(buffer, 3);

        // write
        fputc(c, toFile);
    }

    free(buffer);
}


char decodeCharacterAtPos(char buffer, size_t pos) {
	char mask = 0b00000011;
	return decodeCharacter((buffer >> 2*(3-pos)) & mask);
}


void decode(FILE *fromFile, FILE *toFile) {
    char buffer[0];
    for (;;) {
        // read byte(s)
        if(fread(buffer, sizeof(char), 1, fromFile) == 0) break;

        // decode and write to file
		fputc(decodeCharacterAtPos(buffer[0], 0), toFile);
		fputc(decodeCharacterAtPos(buffer[0], 1), toFile);
		fputc(decodeCharacterAtPos(buffer[0], 2), toFile);
		fputc(decodeCharacterAtPos(buffer[0], 3), toFile);
    }

}