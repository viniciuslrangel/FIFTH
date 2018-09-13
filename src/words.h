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

struct CustomWordEntry {
    DString name;
    unsigned long startIndex;
};

struct FindWordResult {
    bool native;
    union {
        WordCall native;
        unsigned long startIndex;
    } data;
};

bool RegisterWords(struct WordEntry* entry, int length);

void RegisterCustomWords(struct CustomWordEntry cEntry);

struct FindWordResult FindWordByName(char* name);

#endif //FIFTH_STDWORDS_H
