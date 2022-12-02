#include "dllSpec.h"
#include <stdio.h>  
#include <stdlib.h>

typedef struct mynode {
    struct mynode * prev;
    struct mynode * next;
    int number;
}node_t;
void print_list(node_t * list);

int main(){

    // 建立一顆node
    node_t * first = (node_t *)malloc(sizeof(node_t));
    first->number = 20;
    node_t * second = (node_t *)malloc(sizeof(node_t));
    second->number = 30;
    node_t * third = (node_t *)malloc(sizeof(node_t));
    third->number = 500;

    //建構一個空的 list
    node_t * head = (node_t *)DLL_init();
    //將first node 加入 list 中的第一顆
    DLL_add_first((dllNode_t *)first,(dllNode_t *)head);
    //將third node 加入 list 中的第一顆
    DLL_add_first((dllNode_t *)third,(dllNode_t *)head);
    //second node 加入 list 中 third的後面一顆
    DLL_addto_next((dllNode_t *)second,(dllNode_t *)third);
    
    printf("list number = %d\n",DLL_num_nodes((dllNode_t *)head));
    //打印整個 list
    print_list(head);
    printf("\n");
}
void print_list(node_t * list){
    dllNode_t * temp = DLL_next_node((dllNode_t *)list);
    while (temp != NULL)
    {
        printf("%d ", ((node_t *)temp)->number);
        temp = DLL_next_node(temp);
    }
}