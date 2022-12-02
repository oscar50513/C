#include "dllSpec.h"
#include <stdio.h>  
#include <stdlib.h>

dllNode_t * DLL_init(){
    dllNode_t* head = (dllNode_t*)malloc(sizeof(dllNode_t));
    head->next = NULL;
    head->prev = NULL;
    return head;
}
int DLL_isEmpty(const dllNode_t *head){
    if(head->next == NULL && head->prev == NULL){
        return 1;
    } 
    else{
        return 0;
    } 
}
dllNode_t * DLL_next_node(const dllNode_t * node){
    return node->next;
}
dllNode_t * DLL_prev_node(const dllNode_t * node){
    return node->prev;
}
unsigned int DLL_num_nodes(const dllNode_t *head){
    unsigned int num = 0;
    head = head->next;
    while (head != NULL)
    {
        num++;
        head = head->next;
    }
    return num;
}
void DLL_add_first(dllNode_t * new_node, dllNode_t * head){
    if (head->next==NULL)
    {
        head->next = new_node;
        new_node->prev = head;
        new_node->next = NULL;
    }
    else{
        head->next->prev = new_node;
        new_node->next = head->next;
        new_node->prev = head;
        head->next = new_node;
    }
}
void DLL_add_tail(dllNode_t * new_node, dllNode_t * head){
    if (DLL_isEmpty(head))
    {
        head->next = new_node;
        new_node->prev = head;
        new_node->next = NULL;
    }
    else{
        dllNode_t * tail = head;
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = new_node;
        new_node->prev = tail;
        new_node->next = NULL;
    }
}
static int isHeadNode(dllNode_t *node){
    if(node->prev == NULL){
        return 1;
    }
    else{
        return 0;
    }
}
static int isTailNode(dllNode_t *node){
    if (node->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void DLL_addto_prev(dllNode_t *new_node, dllNode_t *node){
    if(isHeadNode(node)){
        printf("wrong operation: Unable to add node in front of head");
    }
    else
    {
        node->prev->next = new_node;
        new_node->prev = node->prev;
        new_node->next = node;
        node->prev = new_node;
    }
    
}
void DLL_addto_next(dllNode_t *new_node, dllNode_t *node){
    if (isTailNode(node))
    {
        node->next = new_node;
        new_node->prev = node;
        new_node->next = NULL;
    }
    else
    {
        new_node->next = node->next;
        node->next->prev = new_node;
        new_node->prev = node;
        node->next = new_node;
    }
}
void DLL_delete(dllNode_t * node){
    if(isHeadNode(node)){
        printf("wrong operation: head cannot be deleted");
    }
    else if (isTailNode(node))
    {
        node->prev->next = NULL;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
}
dllNode_t * DLL_concate(dllNode_t *srcList, dllNode_t * dstList){
    dllNode_t * tail = dstList;
    while (tail!=NULL)
    {
        tail = tail->next;
    }
    srcList = srcList->next; // (移除srcList的head結點)
    tail->next = srcList;
    srcList->prev = tail;
    return dstList;
}
