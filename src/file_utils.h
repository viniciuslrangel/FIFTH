//
// Created by vinic on 05/09/18.
//

#ifndef FIFTH_FILEBUFFER_H
#define FIFTH_FILEBUFFER_H

#include "base.h"

/**
 * @param path File path
 * @param buffer Variable to store the buffer
 * @return The file size (if it exists) or -1 on error
 */
unsigned long readFile(char* path, _OUT_ char** buffer);

#endif //FIFTH_FILEBUFFER_H
