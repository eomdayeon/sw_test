#include <iostream> // C언어의 <stdio.h>격
#include <queue>
#include <algorithm>
#include <vector>
#include <utility>
#define MAX 101
using namespace std; // 표준 네임스페이스를 사용하겠다는 의미


int map[MAX][MAX] = {0};

//오,아래,왼,위
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

queue< pair<int,int> > snake;
vector< pair<int,char> > command;


int main()
{
    int N,K,L;
    int i;
    scanf("%d", &N);
    scanf("%d", &K);

    int ax,ay;
    for(i=0;i<K;i++){
        scanf("%d %d",&ax,&ay);
        map[ax][ay] = 1;
    }

    int t; char d; pair<int, char> p;
    scanf("%d",&L);
    for(i=0;i<L;i++){
        scanf("%d %c",&t,&d);
        p = make_pair(t,d);
        command.push_back(make_pair(t,d));
    }

    snake.push(make_pair(1,1));
    map[1][1] = -1;


    int dir = 0;
    int time = 0;
    int cmd_idx = 0;

    while(1){
        if(time == command[cmd_idx].first){
            //방향 바꿔줌
            if(command[cmd_idx].second == 'D'){
                dir = (dir+1) % 4;
            }
            else if(command[cmd_idx].second == 'L'){
                if (dir == 0){
                    dir = 3;
                }
                else {
                    dir = dir - 1;
                }
            }
            cmd_idx++;
        }
        
        int tox,toy;
        tox = snake.back().first + dy[dir];
        toy = snake.back().second + dx[dir];

        if(tox > N || toy > N || tox < 1 || toy < 1 || (map[tox][toy] == -1)){
            //새로 가려는 뱀 머리 위치가 N, 1을 넘어갈 경우 or 뱀 좌표에 닿을 경우
            time ++;
            break;
        }        

        if( map[tox][toy] == 1){
            // 사과 위치로 갈 경우
            // 새로운 위치 push만 해준다
            map[tox][toy] = -1;
            snake.push(make_pair(tox,toy));

            time ++;
        }
        else{
            //사과 위치가 아닐 경우 queue pop and 새로운 위치를 push
            map[snake.front().first][snake.front().second] = 0;
            snake.pop(); 

            map[tox][toy] = -1;
            snake.push(make_pair(tox,toy)); 
            time ++;
        }

    }
    printf("%d",time);
    return 0;
}
