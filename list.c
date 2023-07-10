/**
 * @file list.c
 * @author Chanhuni
 * @brief C语言版单链表
 * @version 0.1
 * @date 2023-07-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "io_utils.h"

/* 定义节点类型 */
typedef struct ListNode{
    int value;
    struct ListNode *next;
}ListNode;

/* 创建一个独立节点 */
ListNode *CreateNode(int value)
{
    ListNode *node = malloc(sizeof(ListNode));
    if (!node)
    {
        exit(1);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

/* 释放一个节点 */
void DestroyNode(ListNode **node)    
{
    (*node)->next = NULL;
    free(*node);
    *node = NULL;
}

/**
 * @brief Create a List object
 * 
 * @param arr 
 * @param len 
 * @return ListNode* 
 */
ListNode *CreateList(int *arr, int len)
{
    if(len <= 0){
        return NULL;
    }
    ListNode *head = CreateNode(arr[0]);
    ListNode *current = head;
    for (size_t i = 1; i < len; i++)
    {
        current->next = CreateNode(arr[i]);
        current = current->next;
    }
    
    return head;
}

/**
 * @brief Destroy a list object
 * 
 * @param head 
 */
void DestroyList(ListNode **head)
{
    if(!head || !(*head)){
        return;
    }
    ListNode *current = *head;
    while (current){
        ListNode *to_be_destroy = current;
        current = current->next;
        DestroyNode(&to_be_destroy);
    }
    *head = NULL;
}

/**
 * @brief 
 * 
 * @param head 
 * @param value 
 * @param index 
 */
void InsertNode(ListNode **head, int value, int index)
{
    if(!head || !(*head)){return;}
    if(index < 0){return;}
    ListNode *new_node = CreateNode(value);
    if(index == 0){         /* 在头节点处插入，需要调整头结点的地址 */
        new_node->next = *head;
        *head = new_node;
    }else{
        ListNode *current = *head;
        for (size_t i = 0; i < index - 1; i++){
            if(!current->next){
                /*  如果下一个节点为NULL，那么创建一个空节点 */
                current->next = CreateNode(0);
            }
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }

}

void DeleteNode(ListNode **head, int index)
{
    if(!head || !(*head)){
        return;
    }
    /* 如果中删除第一个节点 */
    if(index == 0){
        ListNode *to_be_destroy = *head;
        *head = (*head)->next;
        DestroyNode(&to_be_destroy);
        return;
    }else{
        ListNode *current = *head;
        for (size_t i = 0; i < index - 1; i++){
            if(!current->next){
                printf("index out of range\r\n");
                return;
            }
            current = current->next;
        }
        ListNode *to_be_destroy = current->next;
        current->next = current->next->next;
        DestroyNode(&to_be_destroy);
        return;
    }
}

void PrintList(ListNode *head)
{
    while (head){
        printf("%d, ", head->value);
        head = head->next;
    }
    printf("\r\n");
}

int main(void)
{
    printf("Enter into %s\r\n", __func__);

    int arr[] = {1,2,3,4,5};
    int len = sizeof(arr)/sizeof(int);
    ListNode *head = CreateList(arr, len);
    PrintList(head);
    InsertNode(&head, 100, 3);
    PrintList(head);
    

    return 0;
}