/**
 * @file quickSort.c
 * @author Chanhuni
 * @brief 快速排序
 *          采用分而治之的思想(分治法)，即找一个点 pivot 把数组分为两部分，每趟排序过程只解决一个问题，
 *          那就是让分出来的这两部分左边的不大于这个 pivot，右边的不小于这个 pivot.
 *          根据pivot的选取，主要有两种实现思路，下面pivot选取方式是最后一个元素的方法，
 * @version 0.1
 * @date 2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "include/io_utils.h"
#include "shuffleArray.h"


/**
 * @brief 对数组元素进行切分，返回切分点
 * 
 * @param array 
 * @param low 
 * @param high 
 * @return int 
 */
int Partition(int array[], int low, int high)
{
    int pivot = array[high];
    int partition = low;
    for(int i = low; i < high; i++){
        if(array[i] <= pivot){
            SwapElement(array, i, partition++);
        }
    }
    SwapElement(array, partition, high);
    return partition;
}

/**
 * @brief 
 * 
 * @param array 
 * @param low 
 * @param high 
 */
void QuickSort(int array[], int low, int high)
{
    if(low >= high){
        return;
    }
    int partition = Partition(array, low, high);
    QuickSort(array, low, partition - 1);
    QuickSort(array, partition + 1, high);
}

#define SIZE 50
int main(void)
{
    int players[SIZE];
    for(int i = 0; i < SIZE; i++){
        players[i] = i;
    }
    PRINT_INT_ARRAY(players, SIZE);
    puts("");
    ShuffleArray(players, SIZE);
    PRINT_INT_ARRAY(players, SIZE);
    puts("");
    QuickSort(players, 0, SIZE - 1);
    PRINT_INT_ARRAY(players, SIZE);
    return 0;
}
