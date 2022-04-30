#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;
struct micro {
	int r;
	int c;
	int num;
	int dir;
};

micro kset[1000]; //현재 미생물 군집의 정보
micro newset[1000]; //이동 미생물 군집의 정보
int N, M, K;//셀의개수 N, 격리시간 M, 군집개수 K
int map[101][101]; //구역
queue < pair<int,int> > q; //r,c가 같은 군집 정보를 넣는 큐(군집 번호, 군집 미생물수)

//상,하,좌,우
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

void init();
void input();
int solve();
void merge();


int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{

		init(); //각 testcase실행하기에 앞서 전체 변수 초기화
		input(); //각 testcase에 대한 input을 입력 받음
		int ans = solve(); //각 testcae에 대한 정답 실행
		printf("#%d %d\n", test_case, ans);

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

void init() {
	N = 0; M = 0; K = 0;
	kset[1000] = { 0 ,};
	map[100][100] = { -1, };
	newset[1000] = { 0 ,};
	q = queue < pair<int, int> > ();
}

void input() {

	int dir = -1;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d %d %d", &kset[i].r, &kset[i].c, &kset[i].num, &dir);
		kset[i].dir = dir - 1;
	}

}

int solve() {
	int res = 0;

	for (int i = 0; i < K; i++) {
		int r = kset[i].r;
		int c = kset[i].c;
		map[r][c] = i;
	}

	//M번 반복(즉, 한번돌때마다 한번 전체 군집이 이동함)
	for(int m = 0; m < M; m++) {

		//각 군집들이 이동방향에 있는 다음 셀로 이동
		for (int i = 0; i < K; i++) {
			int cr = kset[i].r;
			int cc = kset[i].c;
			int cnum = kset[i].num;
			int cdir = kset[i].dir;
			int nr = cr + dr[cdir];	//이동할 셀의 r
			int nc = cc + dc[cdir];	//이동할 셀의 c

			if (nr == 0 || nr == N - 1 || nc == 0 || nc == N - 1) {
				//약품에 도착한 경우
				newset[i].r = nr; 
				newset[i].c = nc;
				newset[i].num = cnum / 2;
				if (cdir % 2 == 0) cdir++;
				else cdir--;
				newset[i].dir = cdir;
				continue;
			}
			newset[i].r = nr;
			newset[i].c = nc;
			newset[i].num = cnum;
			newset[i].dir = cdir;
		}
		 
		int check = 0;
		//각 군집에 대해 r,c가 같은 군집은 서로 num을 비교해서 가장큰 num을 가진 군집으로 합치고 나머지 군집은 0으로 초기화
		for (int i = 0; i < K; i++) {
			micro cur = newset[i];	//비교할 군집 i를 나타냄.
			if (cur.num == 0) continue; //중요중요중요중요!!!!! 이거 안적으면 시간초과 뜬다,, cur.num이 0이라는 것은 이미 죽은 군집을 의미하므로 continue해서 넘어가줘야 시간을 줄일 수 있다.
			q.push(make_pair(i, cur.num));
			for (int j = 0; j < K; j++) {
				micro temp = newset[j];	//비교할 군집 j를 나타냄
				if (i == j) continue;
				//만약 군집i와 r,c가 같은 군집j가 있다면 비교 큐에 넣어준다.
				if (cur.num == 0) continue; //num이 0인 경우 사라진 군집이므로 넘어감			
				if (cur.r == temp.r && cur.c == temp.c) {
					q.push(make_pair(j,temp.num));
					check = 1;
				}
			}
			if (check == 0) q.pop();
			//가장 큰 군집을 찾아서 해당 군집을 기준으로 합쳐준다.
			if(check) merge();
		 }

		//map에 이동한 군집 정보 반영
		for (int i = 0; i < K; i++) {
			int r = newset[i].r;
			int c = newset[i].c;
			map[r][c] = i;
		}
		//kset에 이동한 군집 newset정보 갱신
		for (int i = 0; i < K; i++) {
			kset[i] = newset[i];
		}
	}


	//M번 이동이 끝난 후, kset의 num을 모두 계산해줌
	for (int i = 0; i < K; i++) {
		res += kset[i].num;
	}

	return res;
}

void merge() {

	int maxset = 0;
	int maxnum = 0;
	queue < pair<int, int> > out; //삭제될 군집 정보 pair를 담는 큐 out
	pair<int, int> max;	//가장 큰 군집 정보 max pair
	pair<int, int> cur; //비교할 군집 정보 cur pair

	maxset = q.front().first;
	maxnum = q.front().second;
	max.first = maxset; max.second = maxnum;
	q.pop();

	while (!q.empty()) {
		cur = q.front();
		int curset = q.front().first;
		int curnum = q.front().second;
		q.pop();
		if (curnum > maxnum) {
			out.push(max); //기존의 max pair를 아웃큐에 넣어줌
			maxset = curset;	//maxset번호 갱신
			maxnum = curnum;	//maxnum 갱신
			max.first = maxset; //max set pair 갱신
			max.second = maxnum;
		}
		else {
			out.push(cur);
		}	
	}

	while (!out.empty()) {
		int outset = out.front().first;
		int outnum = out.front().second;
		newset[maxset].num += outnum;
		newset[outset].r = 0; newset[outset].c = 0; newset[outset].num = 0; newset[outset].dir = 0;
		out.pop();
	}
}
