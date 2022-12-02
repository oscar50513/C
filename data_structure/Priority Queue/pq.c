#include "pq.h"
#include <stdio.h>

void createPQ(PQ_t *pq, H_class pqClass, int elementSize, int maxSize, int (*compare)(void* elementA, void *elementB)){
    pq->heap.elements = (int*)malloc(sizeof(elementSize)*maxSize);
    pq->heap.numElements = 0;
    pq->pqClass = pqClass;
    pq->maxSize = maxSize;
    pq->elementSize = elementSize;
    pq->compare = compare;
}
int Enqueue(PQ_t *pq, void * elementA){
    pq->heap.numElements++;
 	pq->heap.elements[pq->heap.numElements-1] = elementA;
    ReheapUp(&(pq->heap), 0, pq->heap.numElements-1);

}
int IsEmpty(PQ_t *pq){
     return pq->heap.numElements == 0;
}
int IsFull(PQ_t *pq){
    return pq->maxSize == pq->heap.numElements;
}
void * Dequeue(PQ_t *pq){
    int item = pq->heap.elements[0];
 	pq->heap.elements[0] = 
			pq->heap.elements[pq->heap.numElements-1];
 	pq->heap.numElements--;
 	ReheapDown(&(pq->heap), 0, pq->heap.numElements-1);
	return item;
}
static void ReheapDown(Heap_t *heap, H_class maxOrmin, int root, int bottom){
    int maxChild, rightChild, leftChild;
        leftChild = 2*root+1;
        rightChild = 2*root+2;
        if(leftChild <= bottom) {  // left child is part of the heap
            if(leftChild == bottom) // only one child
                    maxChild = leftChild;
            else {
                    if(heap->elements[leftChild] <= heap->elements[rightChild])
                    maxChild = rightChild;
                    else
                    maxChild = leftChild;
            }

            if(heap->elements[root] < heap->elements[maxChild]) {
                    Swap(heap->elements, root, maxChild);
                    ReheapDown(maxChild,maxOrmin, root, bottom);
                }
        }
}
static void ReheapUp(Heap_t *heap, H_class maxOrmin, int root, int bottom){
    int parent;
        if(bottom > root) { // tree is not empty
        parent = (bottom-1)/2;
        if(heap->elements[parent] < heap->elements[bottom]) {
                Swap(heap->elements, parent, bottom);
                ReheapUp(heap,maxOrmin,root, parent);
            }
        }
}
static void swap(void *elementA, void* elementB, int elementSize){

}
