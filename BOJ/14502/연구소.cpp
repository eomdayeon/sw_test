#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>

#define MAX 8
using namespace std;

int map[MAX][MAX];
int temp[MAX][MAX];
int N, M;
int result = 0;
queue < pair<int, int> > q;
pair <int, int> p;

//위,오른,아래,왼
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
bool visited[MAX][MAX] = { false };

void bfs();
void dfs(int cnt);

void copy() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            temp[i][j] = map[i][j];
        }
    }
}

int main() {
    int num, i, j;
    scanf("%d %d", &N, &M);

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", &num);
            map[i][j] = num;
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (map[i][j] == 0) {
                copy();                 //벽 설치를 위한 temp 배열에 map 배열을 복사
                temp[i][j] = 1;         //돌아가면서 map[i][j]가 0인 노드에 대해 벽을 세운다.
                dfs(1);             //dfs 재귀를 통해 3개의 벽 세울 곳 탐색 (map[i][j]에 벽이 세워진 상황이므로 두번만 탐색하면 된다.)
                temp[i][j] = 0;
            }
        }
    }

    printf("%d", result);

    return 0;
}


void dfs(int cnt) {  //벽 3개를 돌아가면서 계속해서 설치한다.

    if (cnt == 3) {
        bfs(); // cnt값이 3이면 벽 3개가 설치되었으므로 bfs를 통해 spread를 한다.(인접노드에 전파)
        return;
    }

    //이 부분이 제일 이해가 힘들었다. 
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (temp[x][y] == 0) {      //노드가 0이라면 (벽이 세워지지 않았고 바이러스가 없는 노드)
                temp[x][y] = 1;         //벽을 설치해준다
                dfs(cnt + 1);           //벽을 하나 더 설치했으므로 cnt+1 값을 매개변수로 다시 dfs를 수행한다.
                temp[x][y] = 0;         //dfs(cnt+1)이 호출되고 리턴되면 이전의 노드에 대해 temp[x][y]=0을 수행해줌으로써 벽을 지워주는게 필요하다. 다음 x,y값에 대해 벽을 새로 세울거기 때문.
            }
        }
    }
}

void bfs() {        //벽이 3개 설치된 맵에 대해서, 각각 바이러스 spread를 진행하고 진행한 후 0 노드 개수를 count해서 최대값이면 result에 갱신해준다.

    int spread[8][8];       //바이러스 전파를 위한 배열 (벽 설치를 위한 temp 배열은 계속해서 벽 설치를 위해 사용되므로 전파를 위한 배열을 따로 선언해줘야 함)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            spread[i][j] = temp[i][j];      //벽이 설치된 배열 temp를 spread 배열에 복사해줌
        }
    }
    queue<pair<int, int>> q;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (spread[i][j] == 2)            //전체 바이러스 노드를 큐에 푸시해준다.
                q.push(make_pair(i, j));


    int cury, curx, ny, nx;
    int cnt = 0;
    while (!q.empty()) {                //바이러스 큐가 빌 때 까지 bfs를 수행
        cury = q.front().first;         //바이러스 노드 좌표 (y,x) => (cury, curx)
        curx = q.front().second;
        q.pop();                        

        for (int i = 0; i < 4; i++) {       //pop한 바이러스 노드에 대해 인접노드를 4방향 탐색한다
            ny = cury + dy[i];          
            nx = curx + dx[i];
            if (ny >= 0 && ny < N && nx >= 0 && nx < M) {       //인접노드가 맵 내부에 있고
                if (spread[ny][nx] == 0) {                      //인접노드가 0이라면 (벽(1)도 아니고 바이러스(2)도 아님)
                    spread[ny][nx] = 2;                         //전파시켜준다.
                    q.push(make_pair(ny, nx));                  //전파된 노드를 큐에 push 해준다.
                }
            }
        }
    }


    for (int i = 0; i < N; i++) {           
        for (int j = 0; j < M; j++) {
            if (spread[i][j] == 0)          //전체 spread배열을 돌면서 0인 노드를 세알려준다.
                cnt++;
        }
    }
    result = max(result, cnt);              //최대값이 담긴 result와 비교해서 더 큰값이라면 Result에 반영해준다.

}
