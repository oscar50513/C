#include <iostream>
#include <cstring>
using namespace std;

int num, Initial[100] = {0}, Goal[100] = {0}, History[100][100] = {0}, Action[100] = {0};
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
        Visited[sum] = depth;
    }
    else{
        //cout << "used" << endl;
        return false;
    }
//-----------------------------------------------------------------
    // if this is a leaf node
    if(depth == 0){
        return false;
    }
    // search
    int zero_pos;
    for(zero_pos = 0;zero_pos < num;zero_pos++){
        if(Initial[zero_pos] == 0){
            break;
        }
    }
    int exchange[4] = {zero_pos - 2, zero_pos - 1, zero_pos + 2, zero_pos + 1};
    for(int i = 0; i < 4; i++){
        if(exchange[i] >= 0 && exchange[i] < num){
            pos_exchange(zero_pos, exchange[i]);
            if(dfs(depth - 1)){
                map_copy(_max_depth - depth);
                Action[_max_depth - depth] = i + 1;
                pos_exchange(zero_pos, exchange[i]);
                return true;
            }
            pos_exchange(zero_pos, exchange[i]);
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
    cout << "find depth = " << _max_depth << endl;
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