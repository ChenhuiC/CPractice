/**
 * @file strcmp.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "include/io_utils.h"
#include <string.h>

/* 结合快速排序，对演职人员名单进行排序 */

#ifdef DEBUG
int main(void)
{
    char *left = "Hello World";
    char *right = "Hello C Programming";

    PRINT_INT(strcmp(left, right));
    PRINT_INT(strncmp(left, right, 5));

    

    return 0;
}
#endif