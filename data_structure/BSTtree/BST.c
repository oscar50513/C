#include "BST.h"
#include <stdio.h>  
#include <stdlib.h>

//insertNode 插入一個節點進 BST 內
btreeNode_t *  BST_insertNode(void * element, btreeNode_t * root, int
(*compare)(void * elementA, void * element)){
    btreeNode_t* temp_node = (btreeNode_t*)element;
    if(root==NULL) 
    {
        root = temp_node;
        root->left=NULL;
        root->right=NULL;
        //printf("\nnow root: %d\n",root);
        return root;
    }
    else{
        //printf("have treeRoot!\n");
        //printf("left %d ",root->left);
        //printf("right %d \n",root->right);
        int temp = compare(root,element);
        //printf("compare: %d\n",temp);
        if (temp == -1) // root < element
        {
            root->right =  BST_insertNode(element,root->right,compare);
        }
        else if(temp == 1) // root > element
        {
            root->left =  BST_insertNode(element,root->left,compare);
        }
        else{ //elemant = root
            printf("Node ID is same!");
            return root;
        }
        return root;
    } 
}

btreeNode_t * BST_findMinNode(btreeNode_t * root){
    btreeNode_t *ptr = root;
    printf("now ptr: %d\n",root);
    while(ptr->left != NULL){
        ptr = ptr->left;
    }
    return ptr;
}

btreeNode_t * BST_findMaxNode(btreeNode_t * root){
    btreeNode_t *ptr = root;
    printf("now ptr: %d\n",root);
    while(ptr->right != NULL){
        ptr = ptr->right;
    }
    return ptr;
}

btreeNode_t * BST_findNode(void * element, btreeNode_t * root, int(*compare)(void * elementA, void * element)){
    btreeNode_t* ptr = root;
    while (ptr)
    {
        int temp = compare(element,ptr);
        //printf("temp:%d\n",temp);
        if (temp == -1) // element < root 
        {
            ptr = ptr->left;
        }
        else if(temp == 1) // element > root 
        {
            ptr = ptr->right;
        }
        else{ //elemant = root
            return ptr;
            }
    }
    printf("no node!");
    return NULL;
}
//inOrder 列印 BST 根據中序追蹤法每個節點內容
void BST_inOrder(btreeNode_t * root, void(*print_node)(void * element)){
    btreeNode_t* ptr = root;
    //printf("ptr:%d\n",ptr);
    if(ptr){
        //printf("BST_inOrder have node\n");
        BST_inOrder(ptr->left,print_node);
        print_node(ptr);
        BST_inOrder(ptr->right,print_node);
    }
}

btreeNode_t * BST_delete(void * element, btreeNode_t * root, 
int(*compare)(void * elementA, void * element),void(*copy)(void * elementA, void * element)){
    btreeNode_t* temp_node = (btreeNode_t*)element;
    if(root==NULL) //判斷是否為第一顆 Node
    {
        printf("This tree is NULL!\n");
    }
    else{
        int temp = compare(root,element);
        //printf("temp: %d\n",temp);
        if (temp == -1) // root < element
        {
            root->right = BST_delete(element,root->right,compare,copy);
        }
        else if(temp == 1) // element < root 
        {
            root->left = BST_delete(element,root->left,compare,copy);
        }
        else{ //elemant = root
            temp_node=root;
            //printf("Find!");
            if(!root->left && !root->right) //the node is a leaf
            { 
                root=NULL;
            }
            else 
            {
                 if (root->left && root->right) //the node has 2 children
                 {
                    btreeNode_t* min_node = BST_findMinNode(root->right);
                    copy(root,min_node);
                    root->right = BST_delete(min_node,root->right,compare,copy);
                 }
                 else if (root->left) //the node has one child(left)
                 {
                    //printf("the node has one child(left)\n");
                    //printf("root->left:%d\n",root->left);
                    root = root->left;
                    //printf("root:%d\n",root);
                    //printf("root->left:%d\n",root->left);

                 }
                 else{//the node has one child(right)
                    //printf("the node has one child(right)\n");
                    root = root->right;
                 }
                 
            }
            return root;
        }
    }
    return root; 
}
btreeNode_t * BST_treeCopy(btreeNode_t * root,void(*copy)(void * elementA, void * element),int struct_size){
    if(root)
    {
        btreeNode_t * new = (btreeNode_t*)malloc(struct_size);
        new->left=NULL;
        new->right=NULL;
        //printf("new:%d\n",new);
        copy(new,root);
        if (root->left)
        {
            new->left = BST_treeCopy(root->left,copy,struct_size);
        }
        if(root->right)
        {
            new->right =  BST_treeCopy(root->right,copy,struct_size);
        }
        return new;

    }
}

bool BST_treeEqual(btreeNode_t * rootA, btreeNode_t * rootB,int(*compare)(void * elementA, void * element)){
    bool answer = true;
        if(rootA && rootB){
            if(compare(rootA,rootB)==0){
                answer = BST_treeEqual(rootA->left,rootB->left,compare);
                if(answer)
                    answer = BST_treeEqual(rootA->right,rootB->right,compare);
                else
                    return answer;
            }
            else
                return answer;
        }
        else if((rootA && !rootB) || (!rootA && rootB)){
            //printf("one have left, one no!");
            answer = false;
        }
        else if(!(rootA && rootB))
            answer = true;
        else
            answer = false;
        return answer;
}