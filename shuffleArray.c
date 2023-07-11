/**
 * @file shuffleArray.c
 * @author Chanhuni
 * @brief 打乱数组中元素的顺序
 * @version 0.1
 * @date 2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "include/io_utils.h"
#include <stdlib.h>
#include <time.h>

/**
 * @brief 交换两个元素位置
 * 
 * @param array 
 * @param first 
 * @param second 
 */
void SwapElement(int array[], int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}


/**
 * @brief 打乱数组中元素的顺序
 * 
 * @param array 
 * @param length 
 */
void ShuffleArray(int array[], int length)
{
    srand(time(NULL));              /* 设置随机数种子 */
    for (int i = 0; i < length; i++) {
        int random = rand() % length;
        SwapElement(array, i, random);
    }
}

#ifdef DEBUG
#define ARRAY_SIZE 50

int main(void)
{
    int players[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        players[i] = i;
    }
    PRINT_INT_ARRAY(players, ARRAY_SIZE);
    ShuffleArray(players, ARRAY_SIZE);
    puts("");
    PRINT_INT_ARRAY(players, ARRAY_SIZE);

    return 0;
}
#endif
