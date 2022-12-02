#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;

// reference : https://en.wikipedia.org/wiki/A*_search_algorithm

typedef struct MapNode{
    char map[12];
    short level;
    char action;
    char cost;
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
// H1(h=differences)
int cal_score_H1(char *map, int *target_map, int num){
    int sum = 0;
    for(int i = 0;i < num;i++){
        if(map[i] != target_map[i]){
            sum+=1;
        }
    }
    return sum;
}
// calculate the heuristic score
int cal_score_H2(char *map, int *target_map, int num){
    int sum = 0;
    for(int i = 0;i < num;i++){
        sum += abs(map[i] - target_map[i]);
    }
    return sum;
}

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
    int num, map[12] = {0}, target[12] = {0};
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
        MapNode initial, *result = &initial;
        for(int i = 0; i < num; i++){
            initial.map[i] = map[i];
            initial.level = 1;
            initial.action = 0;
            initial.ptr = 0;
            initial.cost = 0;
            initial.score = 0;
        }
        q.push(initial);
        // initial node was VISITED
        long long int sum = 0;
        for(int s = 0; s < num; s++){
            sum *= 10;
            sum += initial.map[s];
        }
        VISITED[TOTAL] = sum;
        TOTAL++;
        // use queue to search
        while(q.empty() == false){
            MapNode node = q.top();
            q.pop();
            // add node to tree array
            TREE[COUNT] = node;
            // check if found the target
            bool found = true;
            for(int i = 0; i < num; i++){
                if(node.map[i] != target[i]){
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
                    b.map[exchange[i]] = 0;
                    b.map[zero_pos] = node.map[exchange[i]];
                    // check if duplicated
                    long long int sum = 0;
                    for(int s = 0; s < num; s++){
                        sum *= 10;
                        sum += b.map[s];
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
                    // add node to queue for next search
                    b.ptr = &TREE[COUNT];
                    b.action = i + 1;
                    b.level++;
                    b.cost = b.level + 1;
                    b.score = b.cost + cal_score_H2(b.map, target, num);
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
