#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

queue <pair <pair<int, int>, int> > q; //(y,x)좌표 , length
queue <pair <pair<int, int>, int> > caneat; //(y,x)좌표 , length

// vector< vector<int> > map;
int map[21][21] = { 0 };
bool visited[21][21] = {false};

pair <int, int> shark_cur;   //map 현재 상어의 좌표 (y,x)

//위, 오른, 아래, 왼
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

int totaltime = 0;
int sharksize = 2;


int main() {

    int i, j;
    int N, num;
    int eatcount = 0;
    scanf("%d", &N);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &num);
            if (num == 9) {
                shark_cur.first = i; shark_cur.second = j;
            }
            map[i][j] = num;
        }
    }


    while (1) {
        q = queue< pair <pair<int, int>, int> >();     //큐초기화
        bool visited[21][21] = { false };              //방문 배열 초기화
        q.push(make_pair(shark_cur, 0));              //큐에 처음 위치(상어) 삽입 :  (y,x)좌표, length


        pair <pair<int, int>, int> cur;                // queue front  
        while (!q.empty()) { // bfs 종료 조건이 필요함 (while문 안에 넣거나 if문 해서 break) -> q가 빌때까지 계속 해줌
            cur = q.front(); // from
            q.pop();

            for (int dir = 0; dir < 4; dir++) {
                pair <pair<int, int>, int> next;                 //queue front의 인접 노드 next
                next.first.first = cur.first.first + dy[dir];  // 다음 노드의 y 좌표 = 현재 노드의 y 좌표 + dy
                next.first.second = cur.first.second + dx[dir];
                next.second = cur.second + 1;
                if (0 <= next.first.first && next.first.first < N && 0 <= next.first.second && next.first.second < N) {
                    if (map[next.first.first][next.first.second] <= sharksize && !visited[next.first.first][next.first.second]) {
                        q.push(next);
                        visited[next.first.first][next.first.second] = true;
                    }
                }
            }
            if (map[cur.first.first][cur.first.second] > 0 && map[cur.first.first][cur.first.second] < sharksize) {
                caneat.push(cur);
            }
        }


        if (caneat.empty()) break;       //만약 먹을수 있는 물고기가 없다면 (먹을수있는 노드가 큐에 하나도 안집어 넣어진경우) 전체 종료


        //pair <pair<int, int>, int> min; min.first.first = 999; min.first.second = 999; min.second = 999;

        int minX = 999;
        int minY = 999;
        int minL = 999;

        while (!caneat.empty()) {
            cur = caneat.front();
            caneat.pop();
            if (cur.second < minL) { // 만약에 현재 물고기까지의 거리가 가장 작은 거리보다 작다면
                minL = cur.second; // 업데이트해줌
                minY = cur.first.first;
                minX = cur.first.second;
            }
            else if (cur.second == minL) { // 만약에 현재 물고기까지의 거리가 가장 작은 거리와 같다면
                if (cur.first.first < minY) {
                    minL = cur.second;
                    minY = cur.first.first;
                    minX = cur.first.second;
                }
                else if (cur.first.first == minY) {
                    if (cur.first.second < minX) {
                        minL = cur.second;
                        minY = cur.first.first;
                        minX = cur.first.second;
                    }
                }
            }
        }

        map[shark_cur.first][shark_cur.second] = 0;   //맵에 상어 없애줌
        shark_cur.first = minY; shark_cur.second = minX; //상어위치좌표에 이동할 min위치좌표 대입
        map[minY][minX] = 0;  //맵에 이동한 상어 반영
        totaltime = totaltime + minL;                     //이동 시간(=이동 길이) 더해줌
        eatcount++;
        if (eatcount == sharksize) {
            sharksize++;
            eatcount = 0;                            //물고기 먹은횟수 초기화
        }

    }

    printf("%d", totaltime);

    return 0;
}
