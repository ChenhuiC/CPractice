/**
 * @file io_utils.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "io_utils.h"

void PrintBinary(unsigned int value) {
  for (unsigned int i = 8 * (value > USHRT_MAX ? sizeof(int) : sizeof(short)); i > 0; --i) {
    printf("%d", value >> (i - 1) & 1u);
  }
  printf("\n");
}