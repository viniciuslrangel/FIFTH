//
// Created by vinic on 05/09/18.
//

#include <stdio.h>
#include "file_utils.h"

unsigned long ReadFile(char *path, char **buffer) {
    FILE *f;
	if ((f = fopen(path, "rb")) == NULL)
        return 0UL;
    fseek(f, 0, SEEK_END);
    unsigned long length = (unsigned long) ftell(f);
    fseek(f, 0, SEEK_SET);
    *buffer = malloc(sizeof(char) * length);
    if (*buffer == NULL)
        FATAL("Could not allocate memory for reading file");
    fread(*buffer, 1, length, f);
    fclose(f);
    return length;
}
