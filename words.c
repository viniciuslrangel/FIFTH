//
// Created by vinic on 06/09/18.
//

#include <string.h>
#include "words.h"

#define SIZE sizeof(struct WordEntry)
struct WordEntry *wordList;
int wordListLength = 0;

bool RegisterWords(struct WordEntry *entry, int length) {
    struct WordEntry *newList = realloc(wordList, SIZE * (wordListLength + length));
    if (!newList) {
        return false;
    }
    wordList = newList;
    memcpy(&wordList[wordListLength], entry, SIZE * length);
    wordListLength += length;
    return true;
}

WordCall FindWordByName(char *name) {
    for (int i = 0; i < wordListLength; i++) {
        if (strcmp(wordList[i].name, name) == 0)
            return wordList[i].func;
    }
    return NULL;
}

#undef SIZE