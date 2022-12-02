#include <stdbool.h>
#ifndef BinarySearchTree_H_INCLUDED

#define BinarySearchTree_H_INCLUDED

typedef struct node {
    struct node * left;
    struct node * right;
} btreeNode_t;

btreeNode_t *  BST_insertNode(void * element, btreeNode_t * root, int
(*compare)(void * elementA, void * element)); //insertNode 插入一個節點進 BST 內

btreeNode_t * BST_delete(void * element, btreeNode_t * root, int
(*compare)(void * elementA, void * element), void(*copy)(void * elementA, void * element)); //deleteNode 刪除 BST 一個節點

btreeNode_t * BST_findMinNode(btreeNode_t * root); //findMinNode 找出 BST 中鍵值最小的節點
btreeNode_t * BST_findMaxNode(btreeNode_t * root); //findMaxNode 找出 BST 中鍵值最大的節點

btreeNode_t * BST_findNode(void * element, btreeNode_t * root, int
(*compare)(void * elementA, void * element)); //findNode 找出 BST 符合鍵值的節點

void BST_inOrder(btreeNode_t * root, void (*print_node)(void * element)); //inOrder 列印 BST 根據中序追蹤法每個節點內容

btreeNode_t * BST_treeCopy(btreeNode_t * root,void(*copy)(void * elementA, void * element),int struct_size); // treeCopy 複製 BST

bool BST_treeEqual(btreeNode_t * root, btreeNode_t * root_sec,int
(*compare)(void * elementA, void * element)); // treeEqual 比較二個 BST 是否相同

#endif // BinarySearchTree_H_INCLUDED

/*跟第一個作業一樣，這是一個 library， 所以你設計時根本不知道，使用這個
library 的人節點的結構，所以使用的人必須自行設計相關的自用 functions，例如 鍵值的比較 function 叫 compareID, 還有 列印節點的 function 例如是 print 等等，再以函數指標的方式傳進你的 library. 達到你的 library 能適用各種
不一樣的結構內容。*/