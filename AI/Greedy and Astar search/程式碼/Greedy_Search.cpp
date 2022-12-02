#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;

typedef struct MapNode{
    char map[12];
    short level;
    char action;
    char score;
    MapNode *ptr;
} MapNode;

// sort
struct MoreThanByScore
{
  bool operator()(const MapNode& lhs, const MapNode& rhs) const
  {
    return lhs.score > rhs.score;
  }
};

long long int VISITED[2000000] = {0};
MapNode TREE[2000000];
int COUNT = 0, TOTAL = 0, TNode = 0;
char ACTION_STRING[5][15] = {"             ", " jump left,  ", " move left,  ", " jump right, ", " move right, "};

// calculate the heuristic score
int cal_score_3(char *map, int *target_map, int num){
    int sum = 0;
    for(int i = 0;i < num;i++){
        if(map[i] != target_map[i]){
            sum++;
        }
    }
    return sum;
}
// calculate the heuristic score
/*int cal_score(char *map, int *target_map, int num){
    int sum = 0;
    for(int i = 0;i < num;i++){
        sum += abs(map[i] - target_map[i]);
    }
    return sum;
}

int cal_score_2(char *map, int *target_map, int num){
    int sum = 0;
    for(int i = 0;i < num;i++){
        sum += (map[i] - target_map[i]) * (map[i] - target_map[i]);
    }
    sum = sum / num;
    sum = sqrt(sum);
    return sum;
}*/

int binary_search(long long int content){
    int low = 0, high = TOTAL - 1, mid;
    while(low <= high){
        mid = (low + high) / 2;
        if(VISITED[mid] == content){
            return -1;
        }
        else if(VISITED[mid] > content){
            high = mid - 1;
        }
        else if(VISITED[mid] < content){
            low = mid + 1;
        }
    }
    return low;
}

int main(){
    int num, map[10] = {0}, target[10] = {0};
    while(cin >> num){
        // input
        for(int i = 0; i < num; i++){
            cin >> map[i];
        }
        for(int i = 0; i < num; i++){
            cin >> target[i];
        }
        // global variable initialize
        memset(VISITED, 0, sizeof(long long int) * 2000000);
        memset(TREE, 0, sizeof(MapNode) * 2000000);
        COUNT = 0;
        TOTAL = 0;
        // queue initialize
        priority_queue<MapNode, vector<MapNode>, MoreThanByScore> q;
        MapNode initial, *result;
        for(int i = 0; i < num; i++){
            initial.map[i] = map[i];
        }
        initial.level = 1;
        initial.action = 0;
        initial.ptr = 0;
        initial.score = 0;

        q.push(initial);
        // use queue to search
        while(q.empty() == false){

            MapNode node = q.top();
            q.pop();
            // check if duplicated
            long long int sum = 0;
            for(int s = 0; s < num; s++){
                sum *= 10;
                sum += node.map[s];
            }
            int index = binary_search(sum);
            if(index == -1){
                continue;
            }
            else{
                // insert position
                for(int j = TOTAL; j > index; j--){
                    VISITED[j] = VISITED[j - 1];
                }
                VISITED[index] = sum;
                TOTAL++;
            }
            // add node to tree array
            TREE[COUNT] = node;
            // check if found the target
            bool found = true;
            for(int i = 0; i < num; i++){
                if(node.map[i] != target[i])
                {
                    found = false;
                    break;
                }
            }
            if(found){
                result = &TREE[COUNT]; // get the address for every action
                break;
            }
            // get position of zero
            int zero_pos;
            for(zero_pos = 0; zero_pos < num; zero_pos++){
                if(node.map[zero_pos] == 0){
                    break;
                }
            }
            // search
            int exchange[4] = {zero_pos - 2, zero_pos - 1, zero_pos + 2, zero_pos + 1};
            for(int i = 0; i < 4; i++){
                if(exchange[i] >= 0 && exchange[i] < num){
                    MapNode b = node;
                    b.ptr = &TREE[COUNT];
                    b.action = i + 1;
                    b.level++;
                    b.map[exchange[i]] = 0;
                    b.map[zero_pos] = node.map[exchange[i]];
                    b.score = cal_score_3(b.map, target, num);
                    q.push(b);
                    TNode++;
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
        fstream file;
        file.open("log.txt", ios::out|ios::app);
        file << "find depth = " << s.size() - 1 << endl;
        file << "total nodes = " << COUNT << " (visited)" << endl;
        cout << "find depth = " << s.size() - 1 << endl;
        cout << "total nodes = " << COUNT << " (visited)" << endl;
        cout << "total nodes = " << TNode << " (generated)" << endl;
        while(s.empty() == false){
            MapNode node = s.top();
            s.pop();
            file << (int)(node.level - 1) << ACTION_STRING[node.action];
            cout << (int)(node.level - 1) << ACTION_STRING[node.action];
            for(int i = 0; i < num; i++)
            {
                file << (int)node.map[i];
                cout << (int)node.map[i];
            }
            file << endl;
            cout << endl;
        }
        file.close();
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
