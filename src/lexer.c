//
// Created by vinic on 05/09/18.
//

#include <string.h>
#ifdef _WIN32
#else
#include <unistd.h>
#endif
#include "lexer.h"
#include "vm.h"
#include "words.h"
#include "file_utils.h"

#define IS_NUMBER(x) ('0' <= (x) && (x) <= '9')
#define TOKEN_ERROR(x) FATAL("Error on token %d:%d (%s)\n%s", currentLine, currentColumn, filePath, x)
#define BLANK() state = STATE_BLANK

enum {
    STATE_BLANK,
    STATE_NUMBER,
    STATE_STRING,
    STATE_WORD,
    STATE_COMMENT,
    STATE_INCLUDE
} state = STATE_BLANK;

bool lineCommment;

unsigned int currentLine = 1;
unsigned int currentColumn = 1;

unsigned long stringStart;

void Lexer(VmState vm, char *filePath, char *buffer, unsigned long length) {
    unsigned long pos = 0;
    while (pos <= length) {

        char c = buffer[pos];
        char cNext = c ? buffer[pos + 1] : c;

        bool isNumber = IS_NUMBER(c);
        bool eof = pos == length;
        bool isNewLine = c == '\n' || c == '\r';
        bool isBlank = c == ' ' || isNewLine || eof;
        switch (state) {
            case STATE_BLANK: {
                if(isBlank) {
                    break;
                } else if (c == '/' && cNext == '/') {
                    state = STATE_COMMENT;
                    lineCommment = true;
                } else if (c == '(') {
                    state = STATE_COMMENT;
                    lineCommment = false;
                } else if (c == '{') {
                    state = STATE_INCLUDE;
                    stringStart = pos;
                } else if ((c == '-' && (IS_NUMBER(cNext) || cNext == '.')) || c == '.' || isNumber) {
                    state = STATE_NUMBER;
                    stringStart = pos;
                } else if (c == '"') {
                    state = STATE_STRING;
                    stringStart = pos;
                } else {
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
                    op.data.str = DString_create(s);
                    InsertInstruction(vm, op);
                }
            }
                break;
            case STATE_WORD: {
                if (isBlank) {
                    BLANK();
                    char *s = malloc(pos - stringStart + 1);
                    for (unsigned long i = 0; i < pos - stringStart; ++i) {
                        s[i] = UPPER(buffer[stringStart + i]);
                    }
                    s[pos - stringStart] = 0;
                    struct ProgramOp op;
                    op.op = OP_WORD_CALL;
                    DString word = DString_create(s);
                    op.data.str = word;
                    InsertInstruction(vm, op);
                }
            }
                break;
            case STATE_INCLUDE: {
                if (isNewLine || eof) {
                    TOKEN_ERROR("Invalid file name");
                } else if (c == '}') {
                    char *s = malloc(pos - stringStart - 1 + 6); // + .fifth length
                    for (unsigned long i = 1; i < pos - stringStart; ++i) {
                        s[i - 1] = buffer[stringStart + i];
                    }
                    char *sP = s + pos - stringStart - 1;
                    const char * sP_ = ".fifth";
                    for(char i = 0; i < 6; i++) {
                        sP[i] = sP_[i];
                    }
                    s[pos - stringStart - 1 + 6] = 0;

                    char *newBuffer;
                    unsigned long newLength;
#ifdef _WIN32
                    // TODO Win32
#else
                    DString fileAbs = DString_create(realpath(filePath, NULL));
                    int index = DString_lastIndexOf(fileAbs, '/');
                    DString fileDir = DString_substr(fileAbs, 0, index);
                    DString_delete(fileAbs);

                    char wd[4096];
                    getcwd(wd, 4096);

                    chdir(DString_raw(fileDir));
                    DString_delete(fileDir);

                    newLength = ReadFile(s, &newBuffer);
                    chdir(wd);
#endif

                    free(s);
                    if (newLength) {
                        unsigned int numColumn = currentColumn;
                        unsigned int numLine = currentLine;
                        currentColumn = 0;
                        currentLine = 0;
                        state = STATE_BLANK;
                        Lexer(vm, s, newBuffer, newLength);
                        state = STATE_BLANK;
                        currentLine = numLine;
                        currentColumn = numColumn;
                    } else {
                        ERRORLN("Could not read %s", s);
                        TOKEN_ERROR("");
                    }
                }
            }
            case STATE_COMMENT: {
                if (lineCommment) {
                    if (isNewLine) {
                        state = STATE_BLANK;
                    }
                } else if (c == ')') {
                    state = STATE_BLANK;
                } else if (eof) {
                    TOKEN_ERROR("Unfinished comment");
                }
            }
        }

        if (c == '\n') {
            currentColumn = 1;
            currentLine++;
        } else {
            currentColumn++;
        }
        pos++;
    }
}
