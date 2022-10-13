from collections import deque

N, Q = map(int,input().split())   
M = 2**N        #전체 격자의 행, 열

board = []
for i in range(M):
    board.append(list(map(int,input().split())))   #전체 격자

L=[]        #단계 L -> Q의 개수만큼 있다.
L = list(map(int,input().split()))
Lsize =[]       #시계방향 회전할 배열의 사이즈 리스트 (2의L승)
for l in L:
    size = (int(2**l))     #size -> 회전해야 하는 배열의 크기
    Lsize.append(size)              #Lsize = [회전배열크기, 회전배열크기, ....] 총 Q개


dr = [-1,0,+1,0]
dc = [0,-1,0,+1]

def rotate(board,size):
    tmpboard = [[0]*M for _ in range(M)]
    for x in range(0,M,size):               # (x,y) => 회전을 시행하는 격자의 출발 지점(x,y) 좌표 ::::: 즉, 0부터 M(격자전체길이) 까지 회전행렬크기만큼 더해주면서 각 회전행렬 시작점 탐색
        for y in range(0,M,size):           #     만약, 회전 사이즈 (Lsize)가 4고 전체 격자 길이가 8이라면 ,행이 0: (0,0)~(0,3) -> (0,4)~(0,7) => 행이 4: (4,0)~(4,3) -> (4,4)~(4,7)
            for r in range(0,size,1):           #각 회전행렬에 대해 시계방향 rotate하는 코드 작성
                for c in range(0,size,1):
                    tmpboard[c+x][size-1-r+y] = board[r+x][c+y]

    return tmpboard

def icecheck(board):
    iceboard = [[0]*M for _ in range(M)] 
        
    for r in range(M):
        for c in range(M):
            cnt = 0
            for k in range(4): #board[r][c]에 대해 4방향 탐색
                nr, nc = r + dr[k], c + dc[k]
                if nr<0 or nc<0 or nr>=M or nc>=M:
                    continue
                if board[nr][nc] > 0: #얼음이 있는 칸 체크
                    cnt += 1
            if cnt < 3: #4방향 탐색 후 얼음있는 칸이 3개 미만이라면
                if board[r][c] == 0:  #얼음이 이미 없다면 그냥 0임
                    continue
                else:
                    iceboard[r][c] = board[r][c] - 1  #얼음 감소
            elif cnt >= 3: #4방향 탐색 후 얼음있는 칸이 3개 이상이라면
                iceboard[r][c] = board[r][c]

    return iceboard

for size in Lsize:  #Q번 진행하게 된다.
    board = rotate(board, size) #L에 대해 시계방향 회전
    board = icecheck(board)       #얼음 양 줄임


#남아있는 얼음 board[r][c]의 합을 구한다.   

def bfs(i,j):
    global visited
    count = 1
    queue = deque()
    queue.append([i,j])
    visited[i][j] = True
    while queue:
        r, c = queue.popleft()
        for k in range(4): #board[r][c]에 대해 4방향 탐색
            nr, nc = r + dr[k], c + dc[k]
            if nr<0 or nc<0 or nr>=M or nc>=M:
                continue    
            if board[nr][nc] > 0 and not visited[nr][nc]:  #얼음이 있다면
                queue.append([nr,nc])
                visited[nr][nc] = True
                count += 1 #얼음 개수 1 증가

    return count

#남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수를 구한다. (bfs)
total = 0  
maxcnt = 0
visited = [[False]*M for _ in range(M)]
for i in range(M):
    for j in range(M):
        if board[i][j] == 0:        #얼음 없으면 pass
            continue
        total += board[i][j]        #얼음 개수 count
        if board[i][j] > 0 and not visited[i][j]: #얼음이 있다면 bfs진행
            cnt = bfs(i,j)
            maxcnt = max(maxcnt, cnt)

print(total)
print(maxcnt)


