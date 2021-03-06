#include "base.h"
#include "file_utils.h"
#include "lexer.h"
#include "vm.h"

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Use " NAME_STR " <filename.first>");
        return 0;
    }

    char* fileName = argv[1];

    DEBUGLN("Passing %s", fileName);

    char* data;
    unsigned long length = ReadFile(fileName, &data);
    ASSERT(length != 0, "Error reading file. %s", fileName);

    VmState vm = CreateVm();

    Lexer(vm, fileName, data, length);

    return (int) RunVm(vm);
}