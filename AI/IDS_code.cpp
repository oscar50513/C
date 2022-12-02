#include <iostream>
#include <cstring>
#include<cmath>
using namespace std;

int num, Initial[100] = {0}, Goal[100] = {0}, History[100][100] = {0}, Action[100] = {0};
int draw[100][100] = {0};
int _count = 0, _max_depth;// IDS search
char Str_Action[5][15] = {"", " jump left,  ", " move left,  ", " jump right, ", " move right, "};
char Visited[1000000000];

void pos_exchange(int, int);
bool dfs(int);
void map_copy(int);

bool dfs(int depth){
    _count++;
    // check if found the target
    bool found = true;
    for(int i = 0;i < num;i++){
        if(Initial[i] != Goal[i]){
            found = false;
            break;
        }
    }
    if(found){
        return true;
    }

    // check if duplicate
    int sum = 0;
    for(int i = 0;i < num;i++){
        sum *= 10;
        sum += Initial[i];
    }
    if(Visited[sum] < depth){
        //cout << "sum: " << sum << "     VISITED[" << sum << "] : " << (int) Visited[sum] << "  depth: " << depth << endl;
        Visited[sum] = depth;  //顯示出現在第幾層
    }
    else{
        //cout << "used" << endl;
        //return false;
    }
//-----------------------------------------------------------------
    // if this is a leaf node
    if(depth == 0){
        return false;
    }
    
    // search
    int zero_pos;
    //找出零的位置
    for(zero_pos = 0;zero_pos < num;zero_pos++){
        if(Initial[zero_pos] == 0){
            break;
        }
    }
    //判斷能移動的路徑，執行pos_exchange和map_copy
    int exchange[4] = {zero_pos - 2, zero_pos - 1, zero_pos + 2, zero_pos + 1};
    for(int i = 0; i < 4; i++){
        if(exchange[i] >= 0 && exchange[i] < num){
            //cout << "count: "<< _count << endl;
            pos_exchange(zero_pos, exchange[i]); // 先交換找是否為Goal
            for(int i =0;i<num;i++){
                draw[_count][i] = Initial[i];
            }
            if(dfs(depth - 1)){
                map_copy(_max_depth - depth);
                Action[_max_depth - depth] = i + 1;
                pos_exchange(zero_pos, exchange[i]);
                return true;
            }
            pos_exchange(zero_pos, exchange[i]); // 換回來
        }
    }
    return false;
}

void pos_exchange(int pos1, int pos2){
    int temp = Initial[pos1];
    Initial[pos1] = Initial[pos2];
    Initial[pos2] = temp;
}

void map_copy(int pos){
    for(int i = 0;i < num;i++){
        History[pos][i] = Initial[i];
    }
}

int main(){
    // input #number
    cout << "num of nodes = ";
    cin >> num;
    cout << "starting order:" << endl;
    for(int i = 0;i < num;i++){
        cin >> Initial[i];
    }
    cout << "final order:" << endl;
    for(int i = 0;i < num;i++){
        cin >> Goal[i];
    }
    
    // IDS search
    for(_max_depth = 1;;_max_depth++){
        memset(Visited, 0, sizeof(char) * 1000000000);
        if(dfs(_max_depth)){
            break;
        }
    }
    // output
    cout << endl << "find depth = " << _max_depth << endl;
    cout << "total nodes = " << _count << endl;
    cout << "              ";
    for(int j = 0;j < num;j++){
        cout << Initial[j];
    }
    cout << endl;
    int i = 0;
    while(true){
        cout << i +1 << Str_Action[Action[i]];
        for(int j = 0;j < num;j++){
            cout << History[i][j];
        }
        cout << endl;
        if(Action[i + 1] == 0){
            break;
        }
        i++;
    }
    /*
    for(int i=1;i<=_count;i++){
        cout<< endl << "_count = " << i << ", node = ";
        for(int j=0;j<num;j++){
            cout << draw[i][j];  
        }
    }*/
    cout << endl << " depth = 0 ";
    for(int i=0;i<num;i++){
        cout << Initial[i];
    }
    int temp = 0,d=1,c_num = temp;
    while(true){
        cout << endl << " depth = "  << d << " ";
        int n = temp+pow(2,d);
        for(c_num=temp+1; c_num<=n ;c_num = c_num+1){
            if(c_num>=_count){
                break;
                }
            for(int k=0;k<num;k++){
                cout << draw[c_num][k];
            }
            cout << " ";
        }
        temp = temp + 4*d;
        d = d+1;
        if (d>_max_depth){
            break;
        }
    }
}
/*
1, 2, 3
4, 5, 6
7, 8, 0

0 1 2
3 4 5
6 7 8

3
1 0 2 //起始棋盤
2 0 1 //目標 find depth = 3
15
5
1 2 0 1 2 //起始棋盤
2 1 2 1 0 //目標 find depth = 4
96

5
1 1 0 2 2
1 2 1 2 0 // 3
5
1 1 0 2 2
2 1 1 2 0// 6
5
1 1 0 2 2 //起始棋盤
2 2 0 1 1 //目標 find depth = 8
9027
9
1 1 1 1 0 2 2 2 2 //起始棋盤
2 1 2 1 0 1 2 1 2 //目標find depth = 12
9
1 2 3 1 0 1 1 1 1  //起始棋盤
1 1 1 1 0 1 3 2 1  //目標 find depth = 14
147216703
15
29147
6
0 5 4 3 2 1  //起始棋盤
0 1 2 3 4 5  //目標 find depth = 16
7
0 6 5 4 3 2 1 //起始棋盤
1 2 5 3 4 0 6 //目標 find depth = 20
9
8 1 4 0 3 2 7 6 5 //起始棋盤
0 1 2 3 4 5 6 7 8 //目標 find depth = 22

*/