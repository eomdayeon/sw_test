#include <iostream>
 
using namespace std;
const int MAX = 110;
 
int board[MAX][MAX][2];    //0번은 그 위치에 있는 군집 번호, 1번은 현재까지 그 군집에 모인 미생물 수
int dy[5]={0,-1,1,0,0};
int dx[5]={0,0,0,-1,1};
int N,M,K;
 
struct microbe{
    int y;
    int x;
    int num;
    int dir;
};
 
microbe m[1010];
 
int main(){
    int T,tc;
    cin>>T;
    for(tc=1;tc<=T;++tc){
        cin>>N>>M>>K;
        for(int i=1;i<=K;i++){
            cin>>m[i].y>>m[i].x>>m[i].num>>m[i].dir;
        }
        for(int e=0;e<M;e++){ //M번 돌아
             
            for(int i=1;i<=K;i++){
                 
                if(m[i].num>0){  // 미생물 수가 0인 군집은 죽은 군집
                    m[i].y+=dy[m[i].dir];
                    m[i].x+=dx[m[i].dir];
                    if(m[i].y==0 || m[i].x==0 || m[i].y==N-1 && m[i].x==N-1){
                        m[i].num/=2;
                        if(m[i].dir==1) m[i].dir=2;
                        else if(m[i].dir==2) m[i].dir=1;
                        else if(m[i].dir==3) m[i].dir=4;
                        else if(m[i].dir==4) m[i].dir=3;
                    }
                    if(board[m[i].y][m[i].x][0]>0){
                        int idx=board[m[i].y][m[i].x][0]; 
                        board[m[i].y][m[i].x][1]+=m[i].num;
                        if(m[idx].num<m[i].num){
                           board[m[i].y][m[i].x][0]=i;
                           m[idx].num=0;
                        }
                        else m[i].num=0;
                    }
                    else if(m[i].num>0 && board[m[i].y][m[i].x][0]==0){
                        board[m[i].y][m[i].x][0]=i;
                        board[m[i].y][m[i].x][1]=m[i].num;
                    }
                }
            }
            for(int i=1;i<=K;i++){
                if(m[i].num>0){
                    m[i].num=board[m[i].y][m[i].x][1];
                    board[m[i].y][m[i].x][1]=0;
                    board[m[i].y][m[i].x][0]=0;
                }
            }
        }
        int sum=0;
        for(int i=1;i<=K;i++){
            if(m[i].num>0)    sum+=m[i].num;
        }
        cout<<"#"<<tc<<" "<<sum<<"\n";
    }
    return 0;
}
