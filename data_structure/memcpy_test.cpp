
/*https://shengyu7697.github.io/cpp-memcpy/*/

/*memcpy 是用來複製一段記憶體區塊的函式,需要引入的標頭檔 <string.h>*
void * memcpy(void * destination, const void * source, size_t num);
memcpy() 將 source 指向的記憶體區塊複製 num 個到 destination 指向的記憶體區塊，
memcpy 跟 strcpy 不同的是 strcpy 遇到 \0 結束字元就停止複製了，
所以 strcpy() 只能用來複製字串*/

#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[64];
};

int main() {
    struct Student student;
    student.id = 123456;

    char name[] = "Tom";
    memcpy(student.name, name, strlen(name)+1);
    // or strcpy(student.name, name);
    printf("student: %d, %s\n", student.id, student.name);

    struct Student student2;
    memcpy(&student2, &student, sizeof(student));
    printf("student2: %d, %s\n", student2.id, student2.name);
    return 0;
}


