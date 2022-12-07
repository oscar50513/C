/*http://hackgrass.blogspot.com/2018/03/c-pointerint-foo-int-bar.html*/

int size = 2, i;
int arr[size];
int *ptr;
ptr = &arr;    //將ptr指向array
// 1.記憶體位址 
for(i=0; i<size; i++)
    printf("&arr[%d]: %p, ptr+%d: %p\n", i, &arr[i], i, ptr+i);
// 2.值的存取
arr[0] = 0;
*(ptr+1) = 1;
for(i=0; i<size; i++)
    printf("arr[%d]: %d, *(ptr+%d): %d\n", i, arr[i], i, *(ptr+i));

/*上面提過指標存取值，必須透過一把鑰匙，即用"*"去取值。
我們如果要取第一個值，很簡單的就是直接加上一個*即可，不過第二個以後的呢?
在前言有提到，指標變數本身存的就是記憶體位址，因此要取下一個的值，
就必須要「位移該變數型態的長度」，0和1之間記憶體位址差了4 bytes(因為int佔4 bytes)
，那我們要透過指標變數取值時，記憶體位址不是應該要ptr+4*n嗎?
但其實C會根據變數本身型態，去做記憶體位址的位移，
因此int型態的指標寫+n時，他會自動位移為4*n bytes，
並且再加上取值運算子*去取值，其他的型態亦同。/