#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
#define MAX 52

using namespace std;

int map[MAX][MAX]; 
bool visited[MAX][MAX]; 
int N,M;

//위(0), 오른(1), 아래(2) ,왼(3)
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};
int dir = 0;    //방향 
int cleancnt = 0; //청소 횟수
pair<int,int> robot; //로봇 위치


bool isleftcan(){
    int lefty, leftx;
    if(dir == 0){
        lefty = robot.first + dy[dir+3];
        leftx = robot.second + dx[dir+3];
    }
    else{
        lefty = robot.first + dy[dir-1];
        leftx = robot.second + dx[dir-1];
    }

    if(0< lefty && lefty<N-1 && 0<leftx && leftx < M-1){
        if(!visited[lefty][leftx] && map[lefty][leftx] != 1) return true;
    }
    return false;
}

int main() {
   int r, c, d;
   int num;
   scanf("%d %d", &N, &M);
   scanf("%d %d %d", &r, &c, &d);

   robot = make_pair(r,c);    //로봇의 위치(y,x)
   dir = d;

   for(int i=0;i<N;i++){
       for(int j=0;j<M;j++){
           scanf("%d",&num);        
           map[i][j] = num;
       }   
   }

   int excute = 0;
   while(1){
       if(!visited[robot.first][robot.second]){
           visited[robot.first][robot.second] = true; 
           cleancnt++;
       }

       if(excute == 4){
            int newdir = (dir + 2) % 4;
            int backy = robot.first + dy[newdir];
            int backx = robot.second + dx[newdir];
            if(map[backy][backx]==0){
                robot.first = backy;
                robot.second = backx;
                excute = 0;
                continue;
            }
            else{
                break;
            }
       }
       
       if (isleftcan() == true){
           dir = (dir+3) % 4;
           robot.first += dy[dir];
           robot.second += dx[dir];
           excute = 0;
           continue;    
       }
       else if(isleftcan() == false){
           dir = (dir+3) % 4;
           excute ++;
       }
   }

   printf("%d",cleancnt);
   return 0;
}
