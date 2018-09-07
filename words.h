//
// Created by vinic on 06/09/18.
//

#ifndef FIFTH_STDWORDS_H
#define FIFTH_STDWORDS_H

#include "base.h"
#include "vm.h"

struct WordEntry {
    char* name;
    WordCall func;
};

bool RegisterWords(struct WordEntry* entry, int length);

WordCall FindWordByName(char* name);

#endif //FIFTH_STDWORDS_H
