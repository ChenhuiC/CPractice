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
/* export marcos -------------------------------------------------------------*/
/* export types --------------------------------------------------------------*/
/* export variables ----------------------------------------------------------*/
/* export functions ----------------------------------------------------------*/
/* swap element in array */
void SwapElement(int array[], int first, int second);
/* shuffle array */
void ShuffleArray(int array[], int length);


#ifdef __cplusplus
}
#endif

#endif
