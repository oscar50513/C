#include "pq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap(void *elementA, void* elementB, int elementSize){
    void *temp = malloc(elementSize);
    memcpy(temp, elementA, elementSize);
    memcpy(elementA, elementB, elementSize);
    memcpy(elementB, temp, elementSize);
    free(temp);
}

void createHeap(Heap_t *heep, int size){
    heep->elements = malloc(size); //配置 size大小的記憶體位址給heep->elements，並將第一個位址存進heep->elements中
    heep->numElements = 0;
}


void createPQ(PQ_t *pq, H_class pqClass, int elementSize, int maxSize, int (*compare)(void* elementA, void *elementB)){
    createHeap(&(pq->heap),sizeof(elementSize)*maxSize);
    pq->pqClass = pqClass;
    pq->maxSize = maxSize;
    pq->elementSize = elementSize;
    pq->compare = compare;
}

int IsEmpty(PQ_t *pq){
    return pq->heap.numElements == 0;
}
int IsFull(PQ_t *pq){
    return pq->maxSize == pq->heap.numElements;
}

int Enqueue(PQ_t *pq, void * elementA){
    printf("%p\n",elementA);
    pq->heap.numElements++;
    // void 型態指標不可取值!!
 	*(PQ_t *)(pq->heap.elements+(pq->heap.numElements-1)*sizeof(elementA)) = *(PQ_t *)elementA;
    ReheapUp(&(pq->heap), pq->pqClass, 0, pq->heap.numElements-1,pq->compare,sizeof(elementA));

}

static void ReheapUp(Heap_t *heap, H_class maxOrmin, int root, int bottom,int (*compare)(void* elementA, void *elementB),int size){
    int parent;
        if(bottom > root) { // tree is not empty
            parent = (bottom-1)/2;
            int compare_num = compare(heap->elements+(bottom*size),heap->elements+(parent*size));
            printf("compare_num: %d\n",compare_num);
            if(compare_num) {
                    swap(heap->elements+(bottom*size), heap->elements+(parent*size), sizeof(heap->elements[parent]));
                    ReheapUp(heap,maxOrmin,root, parent,compare,size);
                }
        }
}


void * Dequeue(PQ_t *pq){
    void *item = pq->heap.elements;
 	pq->heap.elements = (pq->heap.elements+(pq->heap.numElements-1)*sizeof(pq->elementSize));
 	pq->heap.numElements--;
 	ReheapDown(&(pq->heap), pq->pqClass,0, pq->heap.numElements-1,pq->compare,pq->elementSize);
	return item;
}
static void ReheapDown(Heap_t *heap, H_class maxOrmin, int root, int bottom,int (*compare)(void* elementA, void *elementB),int size){
    int maxChild, rightChild, leftChild; // index
    leftChild = 2*root+1;
    rightChild = 2*root+2;
    if(leftChild <= bottom) {  // left child is part of the heap
        if(leftChild == bottom) // only one child
                maxChild = leftChild;
        else {
            int compare_num = compare(heap->elements+(leftChild*size),heap->elements+(rightChild*size));
            if(compare_num) // leftChild > rightChild
                maxChild = leftChild;                
            else
                maxChild = rightChild;
        }
        int compare_num = compare(heap->elements+(maxChild*size),heap->elements+(root*size));
        if(compare_num) {
                swap(heap->elements+(maxChild*size), heap->elements+(root*size), sizeof(heap->elements[root]));
                ReheapDown(heap,maxOrmin, maxChild, bottom, compare,size);
            }
    }
}


