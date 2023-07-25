/**
* @file: quickSort.c
* @brief: 快排
*           采用分而治之的思想(分治法)，即找一个点 pivot 把数组分为两部分，每趟排序过程只解决一个问题，
*          那就是让分出来的这两部分左边的不大于这个 pivot，右边的不小于这个 pivot.
*          根据pivot的选取，主要有两种实现思路，下面pivot选取方式是中间元素的方法（与使用数组实现的选取不同）
* @author: chenhui
* @created: 2023-07-25 23:26:37
* 
* @copyright (C), 2008-2023
* 
*/
/* includes ------------------------------------------------------------------*/
#include "sort/quickSort.h"
#include "../include/io_utils.h"
#include "sort/shuffleArray.h"
#include "stdlib.h"

/* private marcos ------------------------------------------------------------*/
/* private types -------------------------------------------------------------*/
/* private variables ---------------------------------------------------------*/
/* private functions ---------------------------------------------------------*/

static int *Partition(int *low, int *high)
{
    int pivot = *(low + (high - low) / 2);
    while (1){
        while (*low < pivot) low++;
        while (*high > pivot) high--;
        if (low >= high) break;
        SwapInt(low++, high--);
    }
    return high;
}


void QuickSort(int *low, int *high)
{
    if(low >= high) return;
    int *pivot = Partition(low, high);
    QuickSort(low, pivot);
    QuickSort(pivot+1, high);
}

#define DEBUG_QUICK_SORT 1

#if DEBUG_QUICK_SORT

int main(void)
{
    int *players = malloc(sizeof(int) * 50);
    printf("---------------test quick sort start--------------------\n");
    if(players == NULL) return -1;
    for(int i = 0; i < 50; i++){
        players[i] = i;
    }
    PRINT_INT_ARRAY(players, 50);
    Shuffle(players, 50);
    PRINT_INT_ARRAY(players, 50);
    QuickSort(players, players + 49);
    PRINT_INT_ARRAY(players, 50);
    free(players);
    printf("---------------test quick sort end--------------------\n");
    return 0;
}


#endif

