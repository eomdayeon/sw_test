#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cmath>
#define MAX 500

using namespace std;

int map[MAX][MAX];
bool visited[MAX][MAX]={false};

int dx[4]={0,1,0,-1};
int dy[4]={-1,0,1,0};
int N,M;
int res = 0;



void dfs(int i,int j,int cnt,int sum){
    if(cnt == 4){
        res = max(res, sum);
        return;
    }
    int nx,ny;
    for(int k=0;k<4;k++){
        ny = i + dy[k];
        nx = j + dx[k];
        if(ny<0 || ny >=N || nx<0 || nx >= M)
            continue;

        if(visited[ny][nx])
            continue;

        visited[ny][nx] = true;    
        dfs(ny,nx,cnt+1,sum+map[ny][nx]);
        visited[ny][nx] = false;
    }
}

void except(int i, int j){
    int sum = 0;
    //ㅗ
    if (i - 1 >= 0 && j + 2 < M) {
        sum = map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i - 1][j + 1];
        res = max(res,sum);
    }
    //ㅏ
    if (i + 2 < N && j + 1 < M) {
        sum = map[i][j] + map[i + 1][j] + map[i + 2][j] + map[i + 1][j + 1];
        res = max(res,sum);
    }
    //ㅜ
    if (i + 1 < N && j + 2 < M) {
        sum = map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i + 1][j + 1];
        res = max(res,sum);
    }
    //ㅓ
    if (i + 2 < N && j - 1 >= 0) {
        sum = map[i][j] + map[i + 1][j] + map[i + 2][j] + map[i + 1][j - 1];
        res = max(res,sum);
    }
}

int main(){

    int num;
    scanf("%d %d",&N,&M);
    for(int i=0; i<N; i++){
        for(int j=0;j<M;j++){
            scanf("%d",&num);
            map[i][j] = num;
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0;j<M;j++){
            visited[i][j] = true;
            dfs(i,j,1,map[i][j]);
            visited[i][j] = false;
            except(i,j);
        }
    }
    printf("%d",res);
    return 0;

}
