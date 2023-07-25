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
#include "../include/io_utils.h"
#include <stdlib.h>
#include <time.h>
#include "sort/shuffleArray.h"

/*--------------------------------------数组版本开始-------------------------------------------*/
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
        // SwapInt(&array[i], &array[random]);
    }
}
/*--------------------------------------数组版本结束-------------------------------------------*/

/*--------------------------------------指针版本开始-------------------------------------------*/
void SwapInt(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

/**
 * @brief 交换任意类型数据（可以是字符串）
 * 
 * @param first     第一个数据地址
 * @param second    第二个数据地址
 * @param size      数据长度
 */
void Swap(void *first, void *second, size_t size)
{
    void *temp = malloc(size);
    if(temp == NULL){
        //TODO: handle erro
        return;
    }
    memcpy(temp, first, size);
    memcpy(first, second, size);
    memcpy(second, temp, size);
}

void Shuffle(int *array, int length)
{
    srand(time(NULL));                          /* 设置随机种子数 */
    for (int i = length - 1; i > 0; i--) {
        int random = rand() % i;                /*已经换过的位置不再进行交换*/
        SwapInt(&array[i], &array[random]);
    }
}

/*--------------------------------------指针版本结束-------------------------------------------*/


/*简单测试*/
#define DEBUG (0)
#if DEBUG
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
