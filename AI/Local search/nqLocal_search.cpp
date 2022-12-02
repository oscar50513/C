#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#define MAX_SIZE 32
#define INF 9999
using namespace std;

int SIZE = 0;

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
    /*unsigned seed;

    seed = (unsigned)time(NULL);
    srand(seed); */
    for(int i = 0;i < SIZE;i++){
        board[i] = i;
    }
    for(int i = 0;i < SIZE * 10;i++){
        r = rand() % SIZE;
        r2 = rand() % SIZE;
        temp = board[r];
        board[r] = board[r2];
        board[r2] = temp;
    }
    //cin >> r;
}

/* output position to screen and file */
void output(int board[MAX_SIZE]){
    fstream file;
    file.open("result.txt", ios::out|ios::app);
    for(int i = 0;i < SIZE;i++){
        file << (board[i] + 1) << ' ';
    }
    file << endl;
    file.close();

    cout << "----" << endl;
    for(int i = 0;i < SIZE;i++){
        printf("%2d ", board[i]);
    }
    cout << endl;
}

/* copy position */
void copy(int dest[MAX_SIZE], int origin[MAX_SIZE]){
    for(int i = 0;i < SIZE;i++){
         dest[i] = origin[i];
    }
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
    
    seed = (unsigned)time(NULL);
    srand(seed);

    cout << "Input board size:" ;
    cin >> SIZE;
    cout << "Input #generate board:" ;
    cin >> nb;

    int board[MAX_SIZE] = {0};

    int best_count = 0, node_count = 0, repeat = 0, total = 0;
    double START,END; START = clock();
    while(repeat < nb){
        int conflict_table[MAX_SIZE][MAX_SIZE] = {0};
        int best = INF, best_con = INF - 1;
        random_input(board);
        
        for(int i = 0;i < SIZE;i++){
            printf("%2d ", board[i]);
        }
        cout << "當前盤面(隨機生成)" << endl;

        // if last move has a same conflict value, then stop
        while(best != best_con){
            node_count++;
            best = best_con;
            // calculate the conflict value
            int sum;
            for(int r = 0;r < SIZE;r++){
                for(int c = 0;c < SIZE;c++){
                    int new_board[MAX_SIZE];
                    copy(new_board, board);
                    new_board[c] = r;
                    sum = 0;

                    for(int i = 0;i < SIZE;i++){
                        sum += conflict(new_board, i);
                    }
                    conflict_table[r][c] = sum;
                }
            }
            // select the min conflict move
            int best_row = 0, best_col = 0;
            best_con = INF;
            for(int r = 0;r < SIZE;r++){
                for(int c = 0;c < SIZE;c++){
                    if(conflict_table[r][c] < best_con){
                        best_con = conflict_table[r][c];
                        best_col = c;
                        best_row = r;
                    }
                }
            }

            board[best_col] = best_row;
            cout << "node_count = " << node_count << ':';
            for(int i = 0;i < SIZE;i++){
                printf("%2d ", board[i]); 
            }
            cout<<endl;
        }
        // output position if find the local maximum
        if ( best == 0 )
        {
            output(board);
            board_output(board);
            repeat++;
            
        }
        total++;
        

    }
    cout << "total Generated nodes = " << node_count << endl;
    cout<<"Total Generated final boards ="<<total<<endl;
    cout << "average searched nodes = " << static_cast< float >(node_count)/static_cast< float >(total) << endl;
    cout << "stuck rate = " << static_cast< float >(total-nb)/static_cast< float >(total) << endl;
    END = clock();
    cout << "Execution time = " << (END - START)  <<"ms"<< endl;
    return 0;
}