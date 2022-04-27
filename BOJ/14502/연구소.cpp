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
//void dfs(int x, int y, int cnt);
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
                copy();                 //벽3개 추가하는 temp배열 초기화
                temp[i][j] = 1;         //벽세움
                dfs(1);             //dfs 재귀를 통해 3개 벽 찾음
                temp[i][j] = 0;
            }
        }
    }

    printf("%d", result);

    return 0;
}

//void dfs(int i, int j, int cnt) {
//
//    if (cnt == 3) {
//        bfs(); //해당 벽 3개 설치한 상황에 대해 bfs실시 (2의 인접노드 spread 후의 0인 개수 탐색)
//        return;
//    }
//
//    for (int x = i; x < N; x++) {
//        for (int y = j; y < M; y++) {
//            if (temp[x][y] == 0) {
//                temp[x][y] = 1;
//                dfs(x,y,cnt + 1);
//                temp[x][y] = 0;
//            }
//        }
//    }
//}

void dfs(int cnt) {

    if (cnt == 3) {
        bfs(); //해당 벽 3개 설치한 상황에 대해 bfs실시 (2의 인접노드 spread 후의 0인 개수 탐색)
        return;
    }

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (temp[x][y] == 0) {
                temp[x][y] = 1;
                dfs(cnt + 1);
                temp[x][y] = 0;
            }
        }
    }
}

void bfs() {

    int spread[8][8];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            spread[i][j] = temp[i][j];
        }
    }
    queue<pair<int, int>> q;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (spread[i][j] == 2)            //바이러스 있으면 큐에 푸시
                q.push(make_pair(i, j));


    int cury, curx, ny, nx;
    int cnt = 0;
    while (!q.empty()) {
        cury = q.front().first;
        curx = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            ny = cury + dy[i];
            nx = curx + dx[i];
            if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
                if (spread[ny][nx] == 0) {
                    q.push(make_pair(ny, nx));
                    spread[ny][nx] = 2;
                    /*visited[ny][nx] = true;*/
                }
            }
        }
    }


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (spread[i][j] == 0)
                cnt++;
        }
    }


    //for (int i = 0; i < N; i++) {
    //    for (int j = 0; j < M; j++) {
    //        if (spread[i][j] == 1)
    //            printf("y: %d x: %d\n", i, j);
    //    }
    //}
    //printf("%d\n\n", cnt);

    result = max(result, cnt);
}
