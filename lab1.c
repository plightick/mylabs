#include "header.h"

int main(int argc, char *argv[]) {

    int function;

    if (argc < 2) {
        printf("Use: %s <name_file>\n", argv[0]);
        return 1;
    }

    fillingOutTheFile (argv[1]);

    printf("What question you want? (if 3 - input 1, if 4 - input 2)");

    if (checker(function) == 1){
        maxValueToMin(argv[1]);
    } else bubble(argv[1]);

    return 0;
}