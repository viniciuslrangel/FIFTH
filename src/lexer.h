//
// Created by vinic on 05/09/18.
//

#ifndef FIFTH_LEXER_H
#define FIFTH_LEXER_H

#include "base.h"
#include "vm.h"

void PushNumber(number_t number);

void Lexer(VmState vmState, char* filePath, char *buffer, unsigned long length);

#endif //FIFTH_LEXER_H
