#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstdio>
#define MAX 500

using namespace std;

int A[MAX][MAX] = { 0 };
int visited[MAX][MAX] = { 0 };

int dr[] = { 0,1,0,-1 };
int dc[] = { -1,0,+1,0 };

//int leftr[] = { 1,-1,2,-2,1,-1,1,-1,0 };
//int leftc[] = { 1,1,0,0,0,0,-1,-1,-2 };
//int downr[] = { -1,-1,0,0,0,0,1,1,2 };
//int downc[] = { 1,-1,2,-2,1,-1,1,-1,0 };
//int rightr[] = { -1,1,-2,2,-1,1,-1,1,0 };
//int rightc[] = { -1,-1,0,0,0,0,1,1,2 };
//int upr[] = { 1,1,0,0,0,0,-1,-1,-2 };
//int upc[] = { -1,1,-2,2,-1,1,-1,1,0 };
int percent[] = { 1,1,2,2,7,7,10,10,5 };

int windr[4][9] = {  
	 { 1,-1,2,-2,1,-1,1,-1,0 },
	 { -1,-1,0,0,0,0,1,1,2 },
	 { -1,1,-2,2,-1,1,-1,1,0 },
	 { 1,1,0,0,0,0,-1,-1,-2 }
};

int windc[4][9] = {
	{ 1,1,0,0,0,0,-1,-1,-2 },
	{ 1,-1,2,-2,1,-1,1,-1,0 },
	{ -1,-1,0,0,0,0,1,1,2 },
	{ -1,1,-2,2,-1,1,-1,1,0 }
};

int out = 0;
int dir = -1;

int main() {
	int N;
	int start;
	scanf("%d", &N);
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			scanf("%d", &A[r][c]);
		}
	}
	start = N / 2 + 1;
	int xr = start;
	int xc = start;
	visited[xr][xc] = 1;


	while (1) {

		//토네이도가 x에서 y로 한칸 움직이는 상황
		int nextdir = (dir + 1) % 4;
		int yr, yc, ar, ac;
		yr = xr + dr[nextdir];
		yc = xc + dc[nextdir];
		ar = yr + dr[nextdir];
		ac = yc + dc[nextdir];
		if (visited[yr][yc]) { // dir을 1 증가해서 계산된 next노드가 visited노드라면 dir그대로
			nextdir = dir; 
			yr = xr + dr[dir];
			yc = xc + dc[dir];
			ar = yr + dr[dir];
			ac = yc + dc[dir];
		}
		if (!visited[yr][yc]) {	//dir을 1 증가해서 계산된 next노드가 visited된 노드가 아니라면 dir을 1증가시킨다.
			dir = nextdir;
		}

		
		int sand = A[yr][yc];
		int nr, nc;
		int sum = 0;
		for (int i = 0; i < 9; i++) {
			nr = yr + windr[dir][i];
			nc = yc + windc[dir][i];
			int wind_sand = (sand * percent[i]) / 100;
			sum += wind_sand;

			if (nr<1 || nr>N || nc<1 || nc>N) {		// 만약 인접노드가 맵 바깥에 위치한다면 해당 모래는 out에 따로 더해줌 (A[nr][nc]가 map밖이라면 밖으로 나간 모래 양에 더해줌)
				out += wind_sand;
				continue;
			}
			else {									//A[nr][nc]가 map내부이므로 퍼센트만큼 더해준다.
				A[nr][nc] += wind_sand;
			}
		}
		if (ar<1 || ar>N || ac<1 || ac>N) {			// 만약 a노드가 맵 바깥에 위치
			out += (sand - sum);
		}
		else {
			A[ar][ac] += (sand - sum);			// 남은 모래를 계산해서 a에 저장함
		}
		A[yr][yc] = 0;


		//before 주석 참고 (각 DIR을 원래 IF문으로 따로 처리해줬었음.)

		//모래 움직임 계산을 완료하였으므로, yr,yc가 xr,xc가 된다.
		xr = yr;
		xc = yc;
		visited[xr][xc] = 1;
		if (xr == 1 && xc == 1)
			break;
	}

	printf("%d", out);
}



//before 주석
//왼쪽 움직임 모래 계산 함수 실행
////yr,yc에 대해 각 인접 노드에 비율이 적혀있는 칸으로 모래를 이동시켜서 더해줌 	
//if (dir == 0) {
//	int sand = A[yr][yc];
//	int nr, nc;
//	int sum = 0;
//	for (int i = 0; i < 9; i++) {
//		nr = yr + leftr[i];
//		nc = yc + leftc[i];
//		if (nr<1 || nr>N || nc<1 || nc>N) {		// 만약 인접노드가 맵 바깥에 위치한다면 해당 모래는 out에 따로 더해줌 (A[nr][nc]가 map밖이라면 밖으로 나간 모래 양에 더해줌)
//			out += (sand * percent[i]) / 100;
//		}
//		else {									//A[nr][nc]가 map내부이므로 퍼센트만큼 더해준다.
//			A[nr][nc] += (sand * percent[i]) / 100;
//			sum += (sand * percent[i]) / 100;
//		}
//	}
//	if (ar<1 || ar>N || ac<1 || ac>N) {
//		out += (A[yr][yc] - sum);
//	}
//	else {
//		A[ar][ac] += (A[yr][yc] - sum);			// 남은 모래를 계산해서 a에 저장함
//	}
//	A[yr][yc] = 0;
//}

//else if (dir == 1) {
//	//아래쪽 움직임 모래 계산 함수 실행
//	int sand = A[yr][yc];
//	int nr, nc;
//	int sum = 0;
//	for (int i = 0; i < 9; i++) {
//		nr = yr + downr[i];
//		nc = yc + downc[i];
//		if (nr<1 || nr>N || nc<1 || nc>N) {		// 만약 인접노드가 맵 바깥에 위치한다면 해당 모래는 out에 따로 더해줌 (A[nr][nc]가 map밖이라면 밖으로 나간 모래 양에 더해줌)
//			out += (sand * percent[i]) / 100;
//		}
//		else {									//A[nr][nc]가 map내부이므로 퍼센트만큼 더해준다.
//			A[nr][nc] += (sand * percent[i]) / 100;
//			sum += (sand * percent[i]) / 100;
//		}
//	}
//	if (ar<1 || ar>N || ac<1 || ac>N) {
//		out += (A[yr][yc] - sum);
//	}
//	else {
//		A[ar][ac] += (A[yr][yc] - sum);			// 남은 모래를 계산해서 a에 저장함
//	}
//	A[yr][yc] = 0;
//}

//else if (dir == 2) {
//	//오른쪽 움직임 모래 계산 함수 실행
//	int sand = A[yr][yc];
//	int nr, nc;
//	int sum = 0;
//	for (int i = 0; i < 9; i++) {
//		nr = yr + rightr[i];
//		nc = yc + rightc[i];
//		if (nr<1 || nr>N || nc<1 || nc>N) {		// 만약 인접노드가 맵 바깥에 위치한다면 해당 모래는 out에 따로 더해줌 (A[nr][nc]가 map밖이라면 밖으로 나간 모래 양에 더해줌)
//			out += (sand * percent[i]) / 100;
//		}
//		else {									//A[nr][nc]가 map내부이므로 퍼센트만큼 더해준다.
//			A[nr][nc] += (sand * percent[i]) / 100;
//			sum += (sand * percent[i]) / 100;
//		}
//	}
//	if (ar<1 || ar>N || ac<1 || ac>N) {
//		out += (A[yr][yc] - sum);
//	}
//	else {
//		A[ar][ac] += (A[yr][yc] - sum);			// 남은 모래를 계산해서 a에 저장함
//	}
//	A[yr][yc] = 0;
//}


//else if (dir == 3) {
//	//위쪽 움직임 모래 계산 함수 실행
//	int sand = A[yr][yc];
//	int nr, nc;
//	int sum = 0;
//	for (int i = 0; i < 9; i++) {
//		nr = yr + upr[i];
//		nc = yc + upc[i];
//		if (nr<1 || nr>N || nc<1 || nc>N) {		// 만약 인접노드가 맵 바깥에 위치한다면 해당 모래는 out에 따로 더해줌 (A[nr][nc]가 map밖이라면 밖으로 나간 모래 양에 더해줌)
//			out += (sand * percent[i]) / 100;
//		}
//		else {									//A[nr][nc]가 map내부이므로 퍼센트만큼 더해준다.
//			A[nr][nc] += (sand * percent[i]) / 100;
//			sum += (sand * percent[i]) / 100;
//		}
//	}
//	if (ar<1 || ar>N || ac<1 || ac>N) {
//		out += (A[yr][yc] - sum);
//	}
//	else {
//		A[ar][ac] += (A[yr][yc] - sum);			// 남은 모래를 계산해서 a에 저장함
//	}
//	A[yr][yc] = 0;
//}
// before 주석






//토네이도가 한 칸 이동한다.
//dir이 0이라면, 왼쪽으로 이동할 때 모래 움직임 계산 함수를 실행한다.
//그후, dir을 1 증가해서 계산된 next노드가 visited노드라면
//dir을 다시 0으로 바꾼 후 모래 움직임 계산 함수를 실행한다.
//만약 dir을 1 증가해서 계산된 next노드가 visited된 노드가 아니라면
// dir이 1일 때의 모래 움직임 계산 함수를 실행한다.

//토네이도가 한 칸 이동한다.
//그후,또 dir을 1 증가해서 계산된 next노드가 visited노드라면
//dir을 다시 원래대로 바꾼 후 모래 움직임 계산 함수를 실행한다.
//만약 dir을 1 증가해서 계산된 next노드가 visited된 노드가 아니라면
// dir이 2일 때의 모래 움직임 계산 함수를 실행한다.

//토네이도가 한 칸 이동한다.
//그후,또 dir을 1 증가해서 계산된 next노드가 visited노드라면
//dir을 다시 원래대로 바꾼 후 모래 움직임 계산 함수를 실행한다.
//만약 dir을 1 증가해서 계산된 next노드가 visited된 노드가 아니라면
// dir이 3일 때의 모래 움직임 계산 함수를 실행한다.


//토네이도가 한 칸 이동한다.
//그후,또 dir을 dir = (dir+1)%4 해서 계산된 next노드가 visited노드라면
//dir을 다시 원래대로 바꾼 후 모래 움직임 계산 함수를 실행한다.
//만약 dir을 dir = (dir+1)%4 증가해서 계산된 next노드가 visited된 노드가 아니라면
// dir이 (dir+1)%4 즉,0일 때의 모래 움직임 계산 함수를 실행한다.
