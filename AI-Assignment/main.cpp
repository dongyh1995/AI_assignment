#include <iostream>
#include<vector>
#include<math.h>
#define N 10        //size of board
#define m 5
using namespace std;

class Agent{
public:
//    Agent(char sym,double delta1,double delta2){
//        id = (sym=='X') ? 1 : 2;
//
//        for(int i=0;i<m;i++){       //initialize weight1
//            double result = (i-m+1) * (i-m+1) * -1.0 / 2 * delta1 * delta1;
//            weights1[i] = exp(result);
//        }
//
//        for(int i=0;i<m;i++){
//            double result = (i-m+1) * (i-m+1) * -1.0 / 2* delta2 * delta2;
//            weights2[i] = exp(result);
//        }
//    }

    Agent(char sym){                    //Constructor w1:1,10,100,1000...    w2:0,5,50,500...
        id = (sym=='X') ? 1 : 2;

        for(int i=0;i<m;i++){
            weights1[i] = pow(10,i);
        }

        for(int i=0;i<m;i++){
            weights2[i] = weights1[i]/2;
        }

        if(id==2)   swap(weights1,weights2);        //If player is 'O',swap weights1 and weights2, weights1<weights2
    }

    /**
     * Display current board status
     */
    static void display(){
        cout<<"  ";
        for(int i=0;i<N;i++){
            cout<<i%10<<" ";
        }
        cout<<endl;
        for(int i=0;i<N;i++){
            cout<<i%10<<" ";
            for(int j=0;j<N;j++) {
                if(board[i][j]==0)  cout<<" "<<" ";
                else    cout << board[i][j] << " ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    /**
     * Count how many allies can we connect
     * @param row
     * @param col
     * @return
     */
    vector<int> countAllies(int row,int col){
        vector<int> ret(m,0);
        int cnt = 0;
        int i=1,j=1;        //offset of two directions
        int oppo_id = (id==1) ? 2 : 1;

        while(row+i<N && board[row+i][col]==id){           //vertical
            cnt++;
            i++;
        }
        if(row+i<N && board[row+i][col]==oppo_id && cnt>0)    //if one side is blocked, then subtract level by one
            cnt--;
        while(row-j>=0 && board[row-j][col]==id){
            cnt++;
            j++;
        }
        if(row-j>=0 && board[row-j][col]==oppo_id && cnt>0)
            cnt--;
        ret[cnt]++;
        i = j = 1;
        cnt = 0;

        while(col+i<N && board[row][col+i]==id){           //horizontal
            cnt++;
            i++;
        }
        if(col+i<N && board[row][col+i]==oppo_id && cnt>0)
            cnt--;
        while(col-j>=0 && board[row][col-j]==id){
            cnt++;
            j++;
        }
        if(col-j>=0 && board[row][col-j]==oppo_id && cnt>0)
            cnt--;
        ret[cnt]++;
        i = j = 1;
        cnt = 0;

        while(row-i>=0 && col-i>=0 && board[row-i][col-i]==id){         //diagonal
            cnt++;
            i++;
        }
        if(row-i>=0 && col-i>=0 && board[row-i][col-i]==oppo_id && cnt>0)
            cnt--;
        while(row+j<N && col+j<N && board[row+j][col+j]==id){
            cnt++;
            j++;
        }
        if(row+j<N && col+j<N && board[row+j][col+j]==oppo_id && cnt>0)
            cnt--;
        if(row==0 && col==N-1 || row==N-1 && col==0)    ;
        else    ret[cnt]++;
        i = j = 1;
        cnt = 0;

        while(row+i<N && col-i>=0 && board[row+i][col-i]==id){          //diagonal'
            cnt++;
            i++;
        }
        if(row+i<N && col-i>=0 && board[row+i][col-i]==oppo_id && cnt>0)
            cnt--;
        while(row-j>=0 && col+j<N && board[row-j][col+j]==id){
            cnt++;
            j++;
        }
        if(row-j>=0 && col+j<N && board[row-j][col+j]==oppo_id && cnt>0)
            cnt--;
        if(row==0 && col==0 || row==N-1 && col==N-1)    ;
        else    ret[cnt]++;

        return ret;
    }

    /**
     * Count how many opponents can we connect
     * @param row
     * @param col
     * @return
     */
    vector<int> countOpponent(int row,int col){
        vector<int> ret(m,0);
        int oppo_id = (id==1) ? 2 : 1;
        int cnt = 0;
        int i=1,j=1;        //offset of two directions

        while(row+i<N && board[row+i][col]==oppo_id){           //vertical
            cnt++;
            i++;
        }
        if(row+i<N && board[row+i][col]==id && cnt>0)
            cnt--;
        while(row-j>=0 && board[row-j][col]==oppo_id){
            cnt++;
            j++;
        }
        if(row-j>=0 && board[row-j][col]==id && cnt>0)
            cnt--;
        ret[cnt]++;
        i = j = 1;
        cnt = 0;

        while(col+i<N && board[row][col+i]==oppo_id){           //horizontal
            cnt++;
            i++;
        }
        if(col+i<N && board[row][col+i]==id && cnt>0)
            cnt--;
        while(col-j>=0 && board[row][col-j]==oppo_id){
            cnt++;
            j++;
        }
        if(col-j>=0 && board[row][col-j]==id && cnt>0)
            cnt--;
        ret[cnt]++;
        i = j = 1;
        cnt = 0;

        while(row-i>=0 && col-i>=0 && board[row-i][col-i]==oppo_id){         //diagonal
            cnt++;
            i++;
        }
        if(row-i>=0 && col-i>=0 && board[row-i][col-i]==id && cnt>0)
            cnt--;
        while(row+j<N && col+j<N && board[row+j][col+j]==oppo_id){
            cnt++;
            j++;
        }
        if(row+j<N && col+j<N && board[row+j][col+j]==id && cnt>0)
            cnt--;
        if(row==0 && col==N-1 || row==N-1 && col==0)    ;
        else    ret[cnt]++;
        i = j = 1;
        cnt = 0;

        while(row+i<N && col-i>=0 && board[row+i][col-i]==oppo_id){
            cnt++;
            i++;
        }
        if(row+i<N && col-i>=0 && board[row+i][col-i]==id && cnt>0)
            cnt--;
        while(row-j>=0 && col+j<N && board[row-j][col+j]==oppo_id){
            cnt++;
            j++;
        }
        if(row-j>=0 && col+j<N && board[row-j][col+j]==id && cnt>0)
            cnt--;
        if(row==0 && col==0 || row==N-1 && col==N-1)    ;
        else    ret[cnt]++;

        return ret;
    }

//    /**
//     * Simulate opponent's next move
//     * @return Score of next move that considers weights1 only
//     */
//    long OneStepForward(){
//
//    }

    /**
     * Calculate most optimal move
     * @return
     */
    pair<int,int> calculation(){
        double max_scores = 0;
        int row,col;                    // max_score position
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                vector<int> count1(m,0),count2(m,0);    //count1:allies     count2:opponent
                double scores = 0;
                if(board[i][j]==0){

                    count1 = countAllies(i,j);
                    count2 = countOpponent(i,j);

                    for(int k=0;k<m;k++)        //compute overall score
                        scores += weights1[k] * count1[k] + weights2[k] * count2[k];
                    if(max_scores<scores){
                        max_scores = scores;
                        row = i;
                        col = j;
                    }
                }
            }
        }
        return make_pair(row,col);
    }

    /**
     * Move one step
     */
    void move(){
        pair<int,int> pos = calculation();

//        cout<<pos.first<<" "<<pos.second<<endl;

        board[pos.first][pos.second] = id;
    }

    static int board[N][N];

private:
    int id;
    long weights1[m];
    long weights2[m];

};

int Agent::board[N][N] = {{0}};

void Initialize(){
    Agent::board[3][5] = 1;
    Agent::board[4][5] = 2;
    Agent::board[4][8] = 1;
    Agent::board[4][6] = 2;
    Agent::board[5][3] = 1;
    Agent::board[5][2] = 2;
    Agent::board[5][4] = 1;
    Agent::board[5][7] = 2;
    Agent::board[5][5] = 1;
    Agent::board[4][7] = 2;
    Agent::board[5][6] = 1;
    Agent::board[6][6] = 2;
    Agent::board[6][5] = 1;
    Agent::board[6][7] = 2;
    Agent::board[6][9] = 1;
    Agent::board[6][8] = 2;
    Agent::board[8][4] = 1;
    Agent::board[7][5] = 2;
//    Agent::board[][] = 1;
//    Agent::board[][] = 2;
}

int main() {
    Agent player1('X');
    Agent player2('O');
    int i=8;
    int pos_i,pos_j;
//    Initialize();
    Agent::board[5][5] = 1;
    Agent::board[4][4] = 2;
    Agent::display();
    while(1){
        player1.move();
        Agent::display();
        cout<<"Your turn"<<endl;
        cin>>pos_i>>pos_j;
        Agent::board[pos_i][pos_j] = 2;
//        player2.move();
    }
}
