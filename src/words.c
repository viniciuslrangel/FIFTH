//
// Created by vinic on 06/09/18.
//

#include <string.h>
#include "words.h"

// TODO Change this lists to trees (fast lookup structure)

#define SIZE sizeof(struct WordEntry)
struct WordEntry *wordList;
int wordListLength = 0;

struct CustomWordEntry *customWordList;
int customWordListLength = 0;

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

void RegisterCustomWords(struct CustomWordEntry cEntry) {
    struct CustomWordEntry *newList = realloc(customWordList, sizeof(struct CustomWordEntry) * ++customWordListLength);
    if (!newList) {
        customWordListLength--;
        return;
    }
    customWordList = newList;
    newList[customWordListLength - 1] = cEntry;
}

struct FindWordResult FindWordByName(char *name) {
    for (int i = 0; i < wordListLength; ++i) {
        if (strcmp(wordList[i].name, name) == 0) {
            return (struct FindWordResult) {
                    .native = true,
                    .data = {
                            .native = wordList[i].func
                    }
            };
        }
    }
    for (int i = 0; i < customWordListLength; ++i) {
        if (DString_rawEquals(customWordList[i].name, name)) {
            return (struct FindWordResult) {
                    .native = false,
                    .data = {
                            .startIndex = customWordList[i].startIndex
                    }
            };
        }
    }

    return (struct FindWordResult) {
            .native = true,
            .data = {
                    .native = NULL
            }
    };
}

#undef SIZE