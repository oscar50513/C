#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;

typedef struct MapNode{
    char amap[10];
    char level;
    char action;
    MapNode *ptr;
} MapNode;

char VISITED[1000000000];
MapNode TREE[2000000];
int COUNT = 1, TotalNode=1, depth=0;
bool draw = true;
char ACTION_STRING[5][15] = {"             ", " jump left,  ", " move left,  ", " jump right, ", " move right, "};
int main(){
    memset(VISITED, 0, sizeof(char) * 1000000000); //初始化字串全部設成 \0 字元  initialize
    int num, amap[10] = {0}, target[10] = {0}; //初始化陣列amap, target  initialize
    // input
    cout << "num of nodes = ";
    cin >> num;
    cout << "starting order:" << endl;
    for(int i = 0;i < num;i++){
        cin >> amap[i];
    }
    cout << "final order:" << endl;
    for(int i = 0;i < num;i++){
        cin >> target[i];
    }
    
    // queue initialize
    queue<MapNode> q;
    MapNode initial, *result;
    for(int i = 0;i < num;i++){
        initial.amap[i] = amap[i];
        initial.level = 1;
        initial.action = 0;
        initial.ptr = 0;
    }
    q.push(initial);
    
    // use queue to search
    while(q.empty() == false){
        MapNode node = q.front();
        q.pop();
        // check if duplicated
        int sum = 0;      
        for(int i = 0;i < num;i++){
            sum *= 10;
            sum += node.amap[i];
        }
        if( !VISITED[sum] ){
            //cout << "sum: " << sum << "     VISITED[" << sum << "] : " << (int) VISITED[sum] << endl;
            VISITED[sum] = true;
        }
        else{
            //cout << "used" << endl;
            //continue;
        }
        // add node to tree array
        TREE[COUNT] = node;
        
        // check if found the target
        bool found = true;
        for(int i = 0;i < num;i++){
            if(node.amap[i] != target[i]){
                found = false;
                break;
            }
        }
        if(found){
            result = &TREE[COUNT]; // get the address for every action
            COUNT++;
            break;
        }

        // get position of zero  找零的位置
        int zero_pos;
        for(zero_pos = 0;zero_pos < num;zero_pos++){
            if(node.amap[zero_pos] == 0){
                break;
            }
        }
        // search and draw
        // print the depth
        
        
        if(depth != (int)node.level-1){
            depth = (int)node.level-1;
            draw = true;
        }
        
        else if(depth==0){
            cout << endl << " depth = " << depth <<" ";
            for(int i = 0;i < num;i++){
                cout << (int)node.amap[i];
                }
            draw = true;
        }
        
        int exchange[4] = {zero_pos - 2, zero_pos - 1, zero_pos + 2, zero_pos + 1};
        for(int i = 0; i < 4; i++){
            if(exchange[i] >= 0 && exchange[i] < num){
                MapNode b = node;
                b.ptr = &TREE[COUNT];
                b.action = i + 1;
                b.level++;
                b.amap[exchange[i]] = 0;
                b.amap[zero_pos] = node.amap[exchange[i]];
                q.push(b);
                
                if(draw){
                    cout << endl << " depth = " << depth+1 <<" ";
                    draw = false;
                }
                for(int i = 0;i < num;i++){
                    cout << (int)b.amap[i];
                }
                cout << " ";
                TotalNode++; // 產生新的節點 node

            }
        }
        COUNT++;
       
    }

    // add node to stack,for print
    stack<MapNode> s;
    while(true){
        s.push(*result);
        if(result->ptr == 0){
            break;
        }
        *result = *result->ptr;
    }
    // output
    cout << endl << endl << "find depth = " << s.size() - 1 << endl;
    cout << "total nodes(visited) = " << COUNT << endl;
    cout << "total nodes(generated) = " << TotalNode << endl;

    while(s.empty() == false){
        MapNode node = s.top();
        s.pop();
        cout << (int)(node.level - 1) << ACTION_STRING[node.action];
        for(int i = 0;i < num;i++){
            cout << (int)node.amap[i];
        }
        cout << endl;
    }
    return 0;
}

/*
3
1 0 2 //起始棋盤
2 0 1 //目標 find depth = 3
5
1 2 0 1 2 //起始棋盤
2 1 2 1 0 //目標 find depth = 4
5
1 1 0 2 2 //起始棋盤
2 2 0 1 1 //目標 find depth = 5
9
1 1 1 1 0 2 2 2 2 //起始棋盤
2 1 2 1 0 1 2 1 2 //目標find depth = 12
9
1 2 3 1 0 1 1 1 1  //起始棋盤
1 1 1 1 0 1 3 2 1  //目標 find depth = 15
6
0 5 4 3 2 1  //起始棋盤
0 1 2 3 4 5  //目標 find depth = 16
7
0 6 5 4 3 2 1 //起始棋盤
1 2 5 3 4 0 6 //目標 find depth = 20
9
8 1 4 0 3 2 7 6 5 //起始棋盤
0 1 2 3 4 5 6 7 8 //目標 find depth = 22

1, 2, 3
4, 5, 6
7, 8, 0

0 1 2
3 4 5
6 7 8
*/