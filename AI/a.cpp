// 引入標準程式庫中相關的輸入、輸出程式
#include <iostream>
// 引入標準程式庫中相關的字串程式
#include <string>

// std 為標準程式庫的命名空間
using namespace std;

int main(void) {
    // 下面建立名稱為 m ， string 型態的物件
    // 小括弧為 string 的建構子，雙引號為字串字面常數
    string m("There is no spoon.");

    // cout 用來輸出的物件， endl 為新行符號 '\n'
    cout << endl << m << endl << endl << endl;

    // 最後回傳 0 給作業系統
    return 0;
}