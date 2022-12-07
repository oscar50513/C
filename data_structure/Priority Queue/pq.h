#ifndef PQ_H_INCLUDED
#define PQ_H_INCLUDED

typedef struct HeapType {
    void *elements; // element array
    int numElements; // number of elements
} Heap_t;

typedef enum {
    MINHEAP=0,
    MAXHEAP
} H_class;

typedef struct PQ {
    Heap_t  heap;
    H_class pqClass;
    int maxSize;
    int elementSize;
    int (*compare)(void* elementA, void* elementB);
} PQ_t;

/* 建立一個 pq, 其中 pqClass為此PQ的種類(MINHEAP or MAXHEAP)，元素大小為 elementSize, 最多元數個數為 maxSize, compare 是函數指標 */
void createPQ(PQ_t *pq, H_class pqClass, int elementSize, int maxSize, int (*compare)(void* elementA, void *elementB));
int Enqueue(PQ_t *pq, void * elementA); // add an element into PQ
int IsEmpty(PQ_t *pq);// return 0: not empty, 1: empty
int IsFull(PQ_t *pq); // return 0: not full, 1:full
void * Dequeue(PQ_t *pq); // delete an element from PQ 
static void ReheapDown(Heap_t *, H_class maxOrmin, int root, int bottom,int (*compare)(void* elementA, void *elementB),int size);
static void ReheapUp(Heap_t*, H_class maxOrmin, int root, int bottom, int (*compare)(void* elementA, void *elementB),int size); 
static void swap(void *elementA, void* elementB, int elementSize); //利用 memcpy 實作 swap
#endif // DOUBLELINK_H_INCLUDED

/*跟第一個作業一樣，這是一個 library， 所以你設計時根本不知道，
使用這個library的人節點的結構，所以使用的人必須自行設計相關的自用functions，
例如 鍵值得比較function 例如叫 compareID, 還有 列印節點的function 例如print 等等，
再以函數指標的方式傳進你的 library. 達到你的library 能適用各種不一樣的結構內容。
Note: 可能你設計的有些function，外部使用者不需要知道或是不要讓使用者呼叫，
在C++裡稱為 private function，在C裡你可以用 static這個字放在函數前就可以有相同的功能，
例如你會用到*/