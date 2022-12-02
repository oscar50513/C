#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <time.h>
#define MAX_SIZE 32
#define INF 9999
using namespace std;

int SIZE = 0;

int TIMES = 100;

typedef struct node{
    int board[MAX_SIZE];
    int conflict;
    int step;
} node;

/* sort by step first, then sort by conflict value */
struct cmp{
    bool operator()(const node& lhs, const node& rhs) const
    {
        if(lhs.step != rhs.step){
            return lhs.step > rhs.step;
        }
        return lhs.conflict > rhs.conflict;
    }
};

/* min-conflict heuristic */
int conflict(int board[MAX_SIZE], int pos){
    int sum = 0, i;
    for(i = 1;pos + i < SIZE;i++){
        if(board[pos + i] == board[pos]){
            sum++;
        }
        else if(board[pos + i] == board[pos] + i && board[pos] + i < SIZE){
            sum++;
        }
        else if(board[pos + i] == board[pos] - i && board[pos] - i >= 0){
            sum++;
        }
    }
    return sum;
}

/* manual input */
void input(int board[MAX_SIZE]){
    for(int i = 0;i < SIZE;i++){
        cin >> board[i];
    }
}

/* generate n-digit position and the number is not duplicated*/
void random_input(int board[MAX_SIZE]){
    int temp, r, r2;

    for(int i = 0;i < SIZE;i++){
        board[i] = i;
    }
    for(int i = 0;i < SIZE * 50;i++){
        r = rand() % SIZE;
        r2 = rand() % SIZE;
        temp = board[r];
        board[r] = board[r2];
        board[r2] = temp;
    }
}

/* output position to screen*/
void output(node o){
    cout << "---- step " << o.step << " con " << o.conflict << endl;
    for(int i = 0;i < SIZE;i++){
        printf("%2d ", o.board[i]);
    }
    cout << endl;
}

/* output position as a n*n board */
void board_output(int board[MAX_SIZE]){
    cout << "----" << endl;
    int r, c;
    for(r = SIZE - 1;r >= 0;r--){
        for(c = 0;c < SIZE;c++){
            if(board[r] == c){
                cout << "o ";
            }
            else{
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main(){
    unsigned seed, nb;
    int ns, total = 0;

    seed = (unsigned)time(NULL);
    srand(seed);

    cout << "Input board size:" ;
    cin >> SIZE;
    cout << "Input #generate board:" ;
    cin >> nb;
    cout << "Input #beam:" ;
    cin >> ns;

    int repeat = 0, node_count = 0;

    priority_queue<node, vector<node>, cmp> q;
    double START,END; START = clock();
    while(repeat < nb){
        int step[1000] = {0};
        node start;
        random_input(start.board);
        total++;

        start.conflict = INF;
        start.step = 0;
        q.push(start);
        int best_con = INF, min_con = INF - 1;

        while(q.empty() == false || best_con == min_con){
            node now = q.top();
            q.pop();

            // if step has more than k state, then skip
            if(step[now.step] == ns){
                continue;
            }
            step[now.step]++;
            node_count++;

            // stop if find the solution
            if(now.conflict == 0){
                
                output(now);
                repeat++;
                break;
            }

            // calculate the conflict value
            int sum, conflict_table[MAX_SIZE][MAX_SIZE] = {0};
            min_con = INF - 1;
            for(int r = 0;r < SIZE;r++){
                for(int c = 0;c < SIZE;c++){
                    int new_board[MAX_SIZE];
                    node test = now;
                    test.board[c] = r;
                    sum = 0;

                    for(int i = 0;i < SIZE;i++){
                        sum += conflict(test.board, i);
                    }
                    conflict_table[r][c] = sum;
                    if(min_con > sum){
                        min_con = sum;
                    }
                }
            }
            
            // add all successors to priority_queue
            for(int r = 0;r < SIZE;r++){
                for(int c = 0;c < SIZE;c++){
                    node next = now;
                    next.board[c] = r;
                    next.step++;
                    next.conflict = conflict_table[r][c];
                    q.push(next);

                }
            }
        }
    }
    
    cout << "total Generated nodes = " << node_count << endl;
    cout<<"Total Generated final boards ="<<total<<endl;
    cout << "average searched nodes = " << static_cast< float >(node_count)/static_cast< float >(total) << endl;
    cout << "stuck rate = " << static_cast< float >(total-nb)/static_cast< float >(total) << endl;
    END = clock();
    cout << "Execution time = " << (END - START)  <<"ms"<< endl;
    
    return 0;
}