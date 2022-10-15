from collections import deque
N, M, K, C = map(int,input().split())  #n:격자크기(최대20), m:박멸이 진행되는 년수, k: 제초제 확산범위, c: 제초제가 남아있는 년수
board = []
pestboard = [[0]* N for _ in range(N)]  #제초제 정보를 기록하는 보드

for i in range(N):
    board.append(list(map(int,input().split())))   #board[i][c] = 나무의 그루수(1이상 100이하) 빈칸->0 , 벽->-1

dr = [-1, 0,+1, 0]
dc = [ 0,-1, 0,+1]

def grow(board):
    #인접한 네개의 칸 중 나무가 있는 칸의 수만큼 나무가 성장
    #성장이 모든 나무에게서 동시에 일어남 -> 새로운 배열에 저장
    temp = [[0]* N for _ in range(N)]
    for r in range(N):
        for c in range(N):
            if board[r][c]>0: #나무가 있는 경우
                #인접한 네개의 칸 중 나무가 몇개 있는지 체크
                cnt = 0
                for k in range(4):
                    nr, nc = r + dr[k], c + dc[k]
                    if 0<=nr<N and 0<=nc<N:
                        if board[nr][nc] > 0: #나무 있다면
                            cnt += 1
                temp[r][c] = cnt

    for i in range(N):
        for j in range(N):
            if temp[i][j] > 0:
                board[i][j] += temp[i][j]
    return board

def thrive(board):
    #나무들이 인접한 4칸에 번식을 진행 -> 벽(-1), 다른나무(>0), 제초제가 있으면 번식 안함
    #이때, 각 칸의 나무그루수(board[i][j])// 총 번식이 가능한 칸의 개수(cnt) 만큼 번식됨.
    #번식은 동시에 진행되므로 새로운 배열에 저장필요

    q = deque()
    temp = [[0]* N for _ in range(N)]
    for r in range(N):
        for c in range(N):
            if board[r][c]>0: #나무가 있다면
                cnt = 0
                for k in range(4):
                    nr, nc = r + dr[k], c + dc[k]
                    if nr<0 or nc<0 or nr>=N or nc>=N:
                        continue
                    if board[nr][nc]==-1 or board[nr][nc]>0:
                        continue
                    if pestboard[nr][nc] > 0:
                        continue
                    q.append([nr,nc])
                    cnt += 1
                if cnt > 0 :
                    thrive_cnt = board[r][c]//cnt
                    while q:
                        x, y = q.popleft()
                        temp[x][y] += thrive_cnt
    for i in range(N):
        for j in range(N):
            if temp[i][j] > 0:
                board[i][j] += temp[i][j]
    return board


def pest(board):
    global pestboard, total
    #각 칸중, 제초체 뿌렸을 때 나무가 가장 많이 박멸되는 칸인 경우를 찾는다. => dfs로 각 칸에 대해 재초제 뿌린 경우 탐색후, max가 되는 경우를 찾음. (제초제 위치 정보도 함께 저장)
    #제초제 뿌릴 때 4개의 대각선 방향으로 K칸만큼 퍼짐. 
    #이때,전파되는 도중 벽이 있거나 (-1), 나무가 아예 없으면(0) 그 칸까지는 뿌려지고, 그 이후의 칸으로 제초제가 전파되지 않는다. 
    #제초제가 뿌려지면, c년만큼 남아있다가, c+1년이 되면 사라진다.(즉, c년동안 지속)
    #제초제가 이미 존재하는 곳에 다시 제초제 뿌려지면 새로 뿌려진 해로부터 c년 동안 유지 -> 즉, 새로 뿌려지면 덮인다.
    dr = [-1,1,1,-1]
    dc = [-1,-1,1,1]
    q = []
    for r in range(N):
        for c in range(N):
            if board[r][c] > 0: #나무가 있다면 
                cnt = board[r][c]
                for d in range(4):
                    for idx in range(1,K+1):
                        nr, nc = r + idx*dr[d], c + idx*dc[d]
                        if 0<=nr<N and 0<=nc<N:
                            if board[nr][nc] > 0:
                                cnt += board[nr][nc]
                            elif board[nr][nc] <= 0:
                                break
                q.append([cnt,r,c])

    q = sorted(q, key = lambda x: (-x[0],x[1],x[2]))      
    
    if not q:
        return
    total += q[0][0] 
    # print("박멸: ",q[0][0],q[0][1],q[0][2])
    pr, pc = q[0][1], q[0][2]  #제초제를 뿌릴 위치

    pestboard[pr][pc] = C+1
    board[pr][pc] = 0
    for d in range(4):
        for idx in range(1,K+1):
            nr, nc = pr + idx*dr[d], pc + idx*dc[d]
            if 0<=nr<N and 0<=nc<N:
                if board[nr][nc] > 0:
                    pestboard[nr][nc] = C+1
                    board[nr][nc] = 0
                elif board[nr][nc] <= 0:
                    pestboard[nr][nc] = C+1
                    break

               
total = 0
for m in range(1,M+1):
    # print(m,"년")
    board = grow(board)
    # print("성장")
    # print(board)

    board = thrive(board)
    # print("번식")
    # print(board)

    pest(board)
    for i in range(N):
        for j in range(N):
            if pestboard[i][j]>0:
                pestboard[i][j] -= 1
    # print("제초제보드갱신")
    # print(pestboard)



print(total)


# 5 1 2 1
# 0 0 0 0 0
# 0 30 23 0 0
# 0 0 -1 0 0
# 0 0 17 46 77
# 0 0 0 12 0
