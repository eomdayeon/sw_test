#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define MAX 51

using namespace std;

int A[MAX][MAX] = { 0 };  //바구니에 저장된 물 양을 기록하는 map
int C[MAX][MAX] = { 0 };  //구름 유무를 나타내는 map
queue < pair<int,int> >  command;  //방향과 거리(d,s) 로 구성된 명령어 큐 -> 하나씩 pop하면서 이동 명령을 수행한다.

int dr[8] = { 0, -1,-1,-1, 0, 1, 1, 1 };
int dc[8] = { -1,-1, 0, 1, 1, 1, 0,-1 };
int sum = 0;

int main() {

	int N, M;
	scanf("%d", &N);
	scanf("%d", &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	int d, s;
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &d, &s);
		command.push(make_pair(d, s));
	}

	//비바라기 시전
	C[N][1] = 1; 
	C[N][2] = 1; 
	C[N-1][1] = 1; 
	C[N-1][2] = 1; 

	//이동 명령을 M번 시행
	while (!command.empty()) {

		int d = command.front().first;		//이동할 방향
		int s = command.front().second;		//이동할 거리
		command.pop();

		//1 모든 구름을 d방향으로 s칸 이동시킨다.
		int MOVEC[MAX][MAX] = { 0 };					//이동한 구름을 나타내는 임시 이동구름 맵
		int nr, nc;
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				if (C[r][c] == 1) {	//만약 구름이 있다면
					//해당 구름을 d방향으로 s만큼 이동시켜준다.
					//이동된 구름을 반영하는 새로운 구름 배열이 필요하다.
					nr = r + (dr[d-1] * s);
					nc = c + (dc[d-1] * s);

					while (nr > N || nr < 1 || nc > N || nc < 1) {
						if (nr > N) nr = nr - N;
						if (nr < 1) nr = nr + N;
						if (nc > N) nc = nc - N;
						if (nc < 1) nc = nc + N;
					}
					MOVEC[nr][nc] = 1; //임시 이동구름 맵에 구름 이동 기록
				}
			}
		}

		//2 각 구름에서 비를 내려준다 -> 각 구름이 있는 행,열에 대해 물 양을 증가
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				if (MOVEC[r][c] == 1) {
					A[r][c]++;
					//printf("행: %d 열: %d 물 양: %d\n",r,c,A[r][c]);
				}
			}
		}

		//3 구름이 모두 사라진다 (기존에 구름위치를 나타내는 맵 C를 초기화, MOVEC는 일단 그대로 둠)
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				C[r][c] = 0;
			}
		}

		//4 2번 단계에서 물 양을 증가시킨 r,c칸에 대해 물복사버그를 시행 -> 해당 (r,c)칸의 대각선 인접노드 중 물이 있는 바구니의 수만큼 (r,c)의 물 양 증가시켜줌
		int cross_r;
		int cross_c;
		int cabinet;	//r,c노드의 대각선 노드중 물이 있는 바구니 수를 체크함
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				cabinet = 0;
				if (MOVEC[r][c] == 1) {   //구름 이동을 해서 비를 내림으로써 물이 증가한 칸 (r,c)를 체크해줌
					//해당 r,c의 대각선 인접노드 중 물이 있는지 count해줌
					for (int k = 2; k <= 8; k=k+2) {
						cross_r = r + dr[k-1];
						cross_c = c + dc[k-1];
						if (1 <= cross_r && cross_r <= N && 1 <= cross_c && cross_c <= N) { //대각선 노드의 행,열이 맵 내부에 존재하는지 체크
							if (A[cross_r][cross_c] > 0) {	//대각선 노드에 물이 존재한다면
								cabinet++;
							}
						}
					}
				}
				A[r][c] += cabinet;  // (r,c) 대각선 노드 중 물이 있는 바구니 수만큼 (r,c)에 있는 바구니 물 양을 증가시켜줌
			}
		}



		//5 바구니에 저장된 물의 양이 2 이상인 모든 칸에 구름을 생성하고, 물의 양을 2 줄임. (이때 단계3에서 구름이 사라진 칸은 생성불가)
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				//이전에 생성했던 구름 위치일 경우에 생략
				if (MOVEC[r][c] == 1) {
					continue;
				}
				//바구니에 저장된 물의양이 2이상이면, 구름을 생성하고 물의 양을 2 줄임.
				if (A[r][c] >= 2) {
					C[r][c] = 1;
					A[r][c] -= 2;
				}
			}
		}

		//모든 과정이 끝났으므로 MOVEC 임시이동구름 배열을 초기화해준다.
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				MOVEC[r][c] = 0;
			}
		}
	}

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			sum += A[r][c];
		}
	}
	printf("%d", sum);

}
