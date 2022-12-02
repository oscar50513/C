#include "BST.h"
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

// gcc -o name main_bst.c BST.c

typedef struct myBST {
    btreeNode_t treeNode;
    char ID[10];
    int math;
    int eng;
} student_t;

void copy(void *elementA, void *elementB){
    strncpy(((student_t *)elementA)->ID, ((student_t *)elementB)->ID,10);
    ((student_t *)elementA)->math = ((student_t *)elementB)->math;
    ((student_t *)elementA)->eng = ((student_t *)elementB)->eng;
}
int compareID(void *elementA, void *elementB) {
     char *aid = ((student_t *)elementA)->ID;
     char *bid = ((student_t *)elementB)->ID;
     //printf("aid%s",aid);
     //printf("   bid%s\n",bid);
     for (int i=0;i<10;i++) {
         if(aid[i]>bid[i]) {
            return 1;
        }else if(aid[i]<bid[i]){
            return -1;
        }
     }
     return 0;
}

// 把 Node 的 ID 值印出來
void print_node(void *elemant){
    if(elemant){
        char *id = ((student_t * )elemant)->ID;
        int eng = ((student_t * )elemant)->eng;
        printf("id = %s  ",id);
        printf("eng = %d",eng);
        printf("\n");
    }
    else
    printf("this node is null!");
    
}

int main()
{
    student_t *root =NULL;
    btreeNode_t * treeRoot = (btreeNode_t*)root;

    student_t *insert_node = (student_t*)malloc(sizeof(student_t));
    strncpy(insert_node->ID, "123",10);
    insert_node->eng = 100;
    treeRoot = BST_insertNode((btreeNode_t*)insert_node, treeRoot, compareID);
    
    student_t *node2 = (student_t*)malloc(sizeof(student_t));
    strncpy(node2->ID, "120",10);
    node2->eng = 80;
    treeRoot = BST_insertNode((btreeNode_t*)node2, treeRoot, compareID);

    student_t *node3 = (student_t*)malloc(sizeof(student_t));
    strncpy(node3->ID, "125",10);
    node3->eng = 70;
    treeRoot = BST_insertNode((btreeNode_t*)node3, treeRoot, compareID);

    student_t *node4 = (student_t*)malloc(sizeof(student_t));
    strncpy(node4->ID, "119",10);
    node4->eng = 50;
    treeRoot = BST_insertNode((btreeNode_t*)node4, treeRoot, compareID);

    printf("\ninOrder search:\n");
    BST_inOrder(treeRoot,print_node);
    
    printf("\nmin_node:\n");
    student_t *min_node = (student_t*)BST_findMinNode(treeRoot);
    print_node(min_node);

    printf("\nmax_node:\n");
    student_t *max_node = (student_t*)BST_findMaxNode(treeRoot);
    print_node(max_node);

    student_t *need = (student_t*)BST_findNode(node4, treeRoot, compareID);
    printf("\nfind_node(id 119):\n");
    print_node(need);
    printf("\n");

    printf("delete node2(id 120)\n");
    treeRoot = BST_delete(node2,treeRoot,compareID,copy);
    
    student_t *need1 = (student_t*)BST_findNode(node2, treeRoot, compareID);
    print_node(need1);

    printf("\n");
    printf("\nnew tree inorder:\n");
    BST_inOrder(treeRoot,print_node);
    printf("\n");

    printf("copy tree\n");
    student_t *root2 = NULL;
    btreeNode_t * treeRoot2 = (btreeNode_t*)root;
    treeRoot2 = BST_treeCopy(treeRoot,copy,sizeof(student_t));
    BST_inOrder(treeRoot2,print_node);

    printf("\ntree and tree2 Equal?\n");
    bool ans = BST_treeEqual(treeRoot,treeRoot2,compareID);
    if(ans)
        printf("Equal!!\n");
    else
        printf("not Equal\n");
    
    printf("\ninsert node2(120) to treeRoot2\n");
    treeRoot2 = BST_insertNode((btreeNode_t*)node2, treeRoot2, compareID);
    BST_inOrder(treeRoot2,print_node);

    printf("\ntree and tree2 Equal?\n");
    ans = BST_treeEqual(treeRoot,treeRoot2,compareID);
    if(ans)
        printf("Equal!!\n");
    else
        printf("not Equal\n");
}