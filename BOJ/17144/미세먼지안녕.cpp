#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdio>
#include <queue>
#define MAX 51
using namespace std;

int map[MAX][MAX] = {0};
int add[MAX][MAX] = {0};
queue <int> air;    //air.front -> 로봇청소기 첫행 air.back -> 로봇청소기 두번째행


//위, 오른, 아래, 왼
int dx[4]={0,1,0,-1};
int dy[4]={-1,0,1,0};
int dir = 0;
int R,C,T;
void spread();
void clean();
int result = 0;

int main(){
    int A;
    scanf("%d %d %d",&R,&C,&T);
    for(int i=1; i<=R;i++){
        for(int j=1; j<=C;j++){
            scanf("%d",&A);
            map[i][j] = A;
            if(A == -1){
                air.push(i);
            }
        }
    }

    while(T--){
        spread();
        clean();  
    }

    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            if(map[i][j]>0)
                result += map[i][j];
        }
    }

    printf("%d",result);
}
void spread(){
    int nx, ny;
    int w, spreadcnt;

    for(int i=1; i<=R; i++){
        for(int j=1;j<=C;j++){

            spreadcnt = 0;
            w = map[i][j]/5;
            if(map[i][j]==-1 || map[i][j]==0) 
                continue;

            for(int k=0;k<4;k++){
                ny = i + dy[k];
                nx = j + dx[k];
                if(1 <= ny && ny <= R && 1 <= nx && nx <= C){ //인접노드가 map안에 존재하고
                    if(map[ny][nx]!=-1){    //인접노드가 로봇청소기가 아니면
                        add[ny][nx] += w;     //확산된 미세먼지양 기록
                        spreadcnt++;
                    }
                }
            }
            add[i][j] -= (w * spreadcnt);
        }
    }
    for(int i=1; i<=R; i++){
        for(int j=1;j<=C;j++){
            if(map[i][j]==-1)
                continue;
            map[i][j] += add[i][j];
            add[i][j] = 0;
        }
    }
    
}


void clean (){
    //반시계
    for(int i = air.front()-1; i>0; i--)        //아래로
        map[i][1] = map[i-1][1];

    for(int j=1; j<C; j++){             //왼쪽으로
        map[1][j] = map[1][j+1];
    }
    
    for(int i=1; i<air.front(); i++){       //위로
        map[i][C] = map[i+1][C];
    }

    for(int j=C; j>1; j--)             //오른쪽으로
        map[air.front()][j] = map[air.front()][j-1];
    map[air.front()][2] = 0;

    //시계
    for(int i=air.back()+1; i<R; i++)        //위로
        map[i][1] = map[i+1][1];

    for(int j=1; j<C; j++){             //왼쪽으로
        map[R][j] = map[R][j+1];
    }
    
    for(int i=R; i>air.back(); i--){       //아래로
        map[i][C] = map[i-1][C];
    }

    for(int j=C; j>2; j--)             //오른쪽으로
        map[air.back()][j] = map[air.back()][j-1];
    map[air.back()][2] = 0;

}
