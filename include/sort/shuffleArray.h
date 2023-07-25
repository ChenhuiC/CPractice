/**
* @file: shuffleArray.h
* @brief: 
* @author: chenhui
* @created: 2023-07-11 22:46:28
* 
* @copyright (C), 2008-2023
* 
*/
#ifndef __SHUFFLEARRAY_H__
#define __SHUFFLEARRAY_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* includes ------------------------------------------------------------------*/
#include <stdio.h>
/* export marcos -------------------------------------------------------------*/
/*  example:
    int a = 0;
    int b = 1;
    int *c = &a;
    int *d = &b;

    SWAP(a, b, int);
    SWAP(c, d, int*);

*/
#define SWAP(x, y, type) do { type temp = x; x = y; y = temp; } while(0)

/* gcc 对 C 语言添加了 typeof 的扩展支持, 用以获取变量的类型 
*/
#define SWAP_EXT(x, y) do { typeof(x) temp = x; x = y; y = temp; } while(0)


/* export types --------------------------------------------------------------*/
/* export variables ----------------------------------------------------------*/
/* export functions ----------------------------------------------------------*/
/* swap element in array */
void SwapElement(int array[], int first, int second);
/* shuffle array */
void ShuffleArray(int array[], int length);

void SwapInt(int *first, int *second);
void Swap(void *first, void *second, size_t size);
void Shuffle(int *array, int length);
#ifdef __cplusplus
}
#endif

#endif
