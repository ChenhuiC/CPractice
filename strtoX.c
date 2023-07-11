/**
 * @file strtoX.c
 * @author your name (you@domain.com)
 * @brief 测试代码
 * @version 0.1
 * @date 2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "include/io_utils.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#ifdef DEBUG
int main(void)
{
    // PRINT_INT(isdigit('0'));
    // PRINT_INT(isxdigit('f'));
    // PRINT_INT(isalpha('a'));
    // PRINT_INT(isspace(' '));
    // PRINT_INT(islower('a'));
    // PRINT_INT(isupper('A'));
    // PRINT_INT(ispunct('!'));
    // PRINT_BINARY(11);

    // PRINT_INT(atoi("23a"));

    char const *const kInput = "1 20000000000000000000000000000000 3 -4 5abcd bye";
    PRINTLNF("Parsing: %s", kInput);

    char const *start = kInput;
    char *end;

    while(1){
        errno = 0;
        const long i = strtol(start, &end, 10);
        if(start == end){
            break;
        }
        printf("'%.*s' -> %ld\n", (int)(end - start), start, i);
        if(errno == ERANGE){
            perror("strtol");
        }
        putchar('\n');
        start = end;
    }

    PRINTLNF("Left: %s", end);

    return 0;
}
#endif