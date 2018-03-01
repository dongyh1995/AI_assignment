#include <iostream>
#include<vector>
#include<math.h>
#define N 20        //size of board

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define m 5

using namespace std;


#define N_SIZE 20
#define MARGIN 0.08

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
    pair<int,int> move(){
        pair<int,int> pos = calculation();

//        cout<<pos.first<<" "<<pos.second<<endl;

        board[pos.first][pos.second] = id;
        return pos;
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


Agent player1('X');
Agent player2('O');



double myround(double r)
{
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

void draw_solid_circle(float x, float y, float radius, bool user)
{
    int count;
    int sections=200;

    GLfloat TWOPI=2.0f * 3.14159f;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    cout << "here" << endl;
    for(count=0; count<=sections; count++)
    {
        if(user) {
            glColor3f(0.0f,0.0f, 0.0f);
        }else {
            glColor3f(1.0f,1.0f, 1.0f);
        }
        glVertex2f(x+radius*cos(count*TWOPI/sections), y+radius*sin(count*TWOPI/sections));
    }
    glEnd();

    glFlush();
}

void draw(double x_index, double y_index, bool user) {
    double each_width = (2.0 - 2 * MARGIN) / (N_SIZE - 1);
    double draw_x = x_index * each_width + MARGIN - 1;
    double draw_y = y_index * each_width + MARGIN - 1;

//    draw_solid_circle(draw_x,draw_y, each_width / 3,user);

    cout << x_index << "," <<y_index << endl;

    if(user) {
        glColor3f(1.0f,1.0f, 1.0f);
    }else {
        glColor3f(0.0f,0.0f, 0.0f);
    }

    glRectf(draw_x + each_width / 3, draw_y + each_width / 3, draw_x - each_width / 3, draw_y - each_width / 3);
    glFlush();
}

void DrawCircle(int x_index, int y_index,  bool user) {

    double each_width = (2.0 - 2 * MARGIN) / (N_SIZE - 1);
    double cx = x_index * each_width + MARGIN - 1;
    double cy = y_index * each_width + MARGIN - 1;
    int num_segments = 100;
    float r = each_width / 3;

    glBegin(GL_TRIANGLE_FAN);

    if(user) {
        glColor3f(1.0f,1.0f, 1.0f);
    }else {
        glColor3f(0.0f,0.0f, 0.0f);
    }

    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
    glFlush();
}

void RenderScene()

{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f,0.0f, 0.0f);

    GLfloat curSizeLine=1;

    double each_width = (2.0 - 2 * MARGIN) / (N_SIZE - 1);

    for(double current = -1 + MARGIN ; current < 1 - MARGIN ; current += each_width) {

        glLineWidth(curSizeLine);

        glBegin(GL_LINES);
        glVertex2f(current,-1 + MARGIN);
        glVertex2f(current, 1 - MARGIN);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(-1 + MARGIN,current);
        glVertex2f( 1 - MARGIN,current);
        glEnd();

    }
    glFlush();

//    draw(5,5,false);
//    draw(4,4,true);



}


//用于初始化，常用来设置场景的渲染状态

void SetupRC(void)
{
    glClearColor(0.8f,0.6f, 0.3f,1.0f);
}






void mouseCB(int button, int state, int x, int y)
{
    double mouseX = (double)x / 250 - 1, mouseY = 1 - (double)y / 250;

    double each_width = (2.0 - 2 * MARGIN) / (N_SIZE - 1);

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            // find the nearest index
            int x_index = round((mouseX + 1 - MARGIN) / each_width);
            int y_index = round((mouseY + 1 - MARGIN) / each_width);

            if(Agent::board[x_index][y_index] != 0)
                return;

            Agent::board[x_index][y_index] = 2;

            DrawCircle(x_index,y_index,true);

            pair<int,int> new_move = player1.move();

            DrawCircle(new_move.first,new_move.second,false);

        }
    }
}

void prevent_resize(int width, int height)  {
    glutReshapeWindow(500, 500);
}

void helper(int argc,char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_SINGLE |GLUT_RGB |GLUT_DEPTH);

    glutInitWindowSize (500,500);

    glutInitWindowPosition (100,100);

    glutCreateWindow ("大哥五子棋");

    glutMouseFunc(mouseCB);

    glutDisplayFunc(RenderScene);

    glutReshapeFunc(prevent_resize);

    SetupRC();

    glutMainLoop();
}



int main(int argn, char **arguments) {

    int i=8;
    int pos_i,pos_j;
//    Initialize();
//    Agent::board[5][5] = 1;
//    Agent::board[4][4] = 2;
    Agent::display();

    helper(argn, arguments);

}



