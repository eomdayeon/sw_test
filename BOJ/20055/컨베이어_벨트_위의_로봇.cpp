#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <queue>
#include <cstring>
#define MAX 200
using namespace std;

int conv[MAX] = {0};  //내구성을 기록하기 위한 컨베이어 벨트 배열
int robot[MAX];       //로봇 유무를 기록하기 위한 로봇 배열(사실상, 컨베이어 벨트의 반 크기)
int t = 0;

int main(){
    int N,K;
    int N2;
    int A;

    scanf("%d %d",&N,&K);
    N2 = N * 2;

    for(int i=1; i<=N2;i++){
        scanf("%d",&conv[i]);
        robot[i] = 0;
    }

    while(1){
        ++t;    //단계 수행

        //1 전체 칸 회전
        //칸 이동
        int tempconv = conv[N2] ; //2N위치의 칸은 1로 이동하기 위해 tempconv에 담아줌
        for(int i=N2; i>1; i--){
            conv[i] = conv[i-1];
        }
        conv[1] = tempconv;      

        //로봇 이동 (로봇은 1에 올라가고 N에서 내려주므로 항상 컨베이어 1~N칸에만 위치한다.)
        for(int i=N; i>1; i--){
            robot[i] = robot[i-1];
        }
        robot[1] = 0; //주의(robot[2]에 robot[1]을 이동시키고 나면 robot[1]은 0으로 바꿔줘야함)
        if(robot[N] == 1) robot[N] = 0;  //내리는 위치(N)에 로봇이 도착하면 내려줘야하므로 바로 0으로 바꿔준다.
        

        //2 가장 먼저 들어온 로봇부터 한칸씩 이동
        for(int idx=N-1; idx>=1; idx--){
            if(robot[idx]==1){                 //현재칸에 로봇이 있다면 (1~N까지)
                if(robot[idx+1] == 0 && conv[idx+1] >= 1){     // 다음 위치에 로봇이 없고, 내구도가 1 이상일때 
                    robot[idx+1] = robot[idx]; //다음칸으로 로봇이동
                    conv[idx+1]--;             //다음칸 내구성감소
                    robot[idx] = 0;
                }                    
            }
            if(robot[N]==1) robot[N] = 0;       //이때도 마찬가지로, 이동한 로봇이 N에 위치하게 되면 바로 내려줘야함( 따라서 , 0값으로 바꿔준다.)
        }    
    

        //3 conv[1]칸의 내구도가 0이 아니면 로봇을 올려준다.
        if(conv[1] > 0){
            robot[1] = 1; //로봇을 올려줌
            conv[1]--;    //올리는 칸 내구도 1 감소시켜줌
        }


        int cnt = 0;
        //4 내구도가 0인 칸의 개수가 K개 이상인 경우 종료
        for(int i=1; i<=N2; i++){
            if(conv[i]==0)
                cnt++;
        }
        if(cnt >= K){
            break;
        }

    }

    printf("%d",t);
    return 0;
}
