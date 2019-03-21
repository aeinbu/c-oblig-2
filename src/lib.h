#include <stdbool.h>
#include <stdio.h>

#ifndef __LIB_H
#define __LIB_H

void encode(FILE *fromFile, FILE *toFile);
void decode(FILE *fromFile, FILE *toFile);

#endif