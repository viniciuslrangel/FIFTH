//
// Created by vinic on 05/09/18.
//

#include <string.h>
#include "lexer.h"
#include "vm.h"
#include "words.h"

#define IS_NUMBER(x) ('0' <= (x) && (x) <= '9')
#define TOKEN_ERROR(x) FATAL("Error on token %d:%d\n%s", currentLine, currentColumn, x)
#define BLANK() state = STATE_BLANK

enum {
    STATE_BLANK,
    STATE_NUMBER,
    STATE_STRING,
    STATE_WORD
} state = STATE_BLANK;

unsigned int currentLine = 0;
unsigned int currentColumn = 0;

unsigned long stringStart;

void Lexer(VmState vm, char *buffer, unsigned long length) {
    unsigned long pos = 0;
    while (pos <= length) {

        char c = buffer[pos];
        char cNext = c ? buffer[pos + 1] : c;

        bool isNumber = IS_NUMBER(c);
        bool eof = pos == length;
        bool isBlank = c == ' ' || c == '\n' || c == '\r' || eof;

        switch (state) {
            case STATE_BLANK: {
                if ((c == '-' && IS_NUMBER(cNext) && cNext == '.') || c == '.' || isNumber) {
                    state = STATE_NUMBER;
                    stringStart = pos;
                } else if (c == '"') {
                    state = STATE_STRING;
                    stringStart = pos;
                } else if (!isBlank) {
                    c = UPPER(c);
                    if (0x21 <= c && c <= 0x7E) {
                        state = STATE_WORD;
                        stringStart = pos;
                    } else {
                        TOKEN_ERROR("Unexpected symbol");
                    }
                }
            }
                break;
            case STATE_NUMBER: {
                if (isBlank) {
                    BLANK();
                    buffer[pos] = '\0';
                    char *err;
                    double n = strtod(&buffer[stringStart], &err);
                    if (*err != 0) {
                        TOKEN_ERROR("Invalid number literal");
                    }
                    struct ProgramOp op;
                    op.op = OP_PUSH_N;
                    op.data.number = n;
                    InsertInstruction(vm, op);
                }
            }
                break;
            case STATE_STRING: {
                if (eof) {
                    TOKEN_ERROR("Unfinished string");
                } else if (c == '"') {
                    BLANK();
                    char *s = malloc(pos - stringStart);
                    memcpy(s, buffer + stringStart + 1, pos - stringStart - 1);
                    s[pos - stringStart - 1] = 0;
                    struct ProgramOp op;
                    op.op = OP_PUSH_S;
                    op.data.str = DString_new(s);
                    InsertInstruction(vm, op);
                }
            }
                break;
            case STATE_WORD: {
                if (isBlank) {
                    BLANK();
                    char *s = malloc(pos - stringStart + 1);
                    for (int i = 0; i < pos - stringStart; ++i) {
                        s[i] = UPPER(buffer[stringStart + i]);
                    }
                    s[pos - stringStart] = 0;
                    struct ProgramOp op;
                    op.op = OP_WORD_CALL;
                    op.data.str = s;
                    InsertInstruction(vm, op);
                }
            }
                break;
        }

        if (c == '\n') {
            currentColumn = 0;
            currentLine++;
        } else {
            currentColumn++;
        }
        pos++;
    }
}
