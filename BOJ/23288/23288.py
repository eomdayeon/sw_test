from collections import deque

N, M, K = map(int,input().split())

board = []        #보드
for i in range(N):
    board.append(list(map(int,input().split())))

dice = [[0,2,0],  #주사위 전개도
        [4,1,3],    
        [0,5,0],
        [0,6,0]]

dir = 0              # 주사위 이동 방향(0:동,1:남,2:서,3:북)
x, y = 0, 0  # 보드에 놓인 주사위 좌표

dr = [0,1,0,-1]     #0: 동, 1: 남, 2: 서, 3: 북
dc = [1,0,-1,0]
score = 0           #최종 점수

def move():
    global x, y, dice, dir    
    #주사위가 이동방향으로 한칸 굴러간다. -> 주사위가 놓이는 좌표 구하기, 굴러간 주사위 전개도 반영
    nx, ny = x + dr[dir], y + dc[dir]        #주사위가 이동할 다음 좌표
    
    if nx<0 or ny<0 or nx>=N or ny>=M:      #만약 이동방향에 칸이 없으면
        dir = (dir+2) % 4                  #주사위 이동 방향 반대로 해서 그 좌표로 이동해줌.
        nx, ny = x + dr[dir], y + dc[dir] 
    x, y = nx, ny   #보드에 놓일 주사위 좌표 반영

    if dir == 0:    #이동방향 :동쪽
        tmp = dice[1][2]
        dice[1][2] = dice[1][1]
        dice[1][1] = dice[1][0]
        dice[1][0] = dice[3][1]
        dice[3][1] = tmp

    elif dir == 1:  #남쪽  
        tmp = dice[3][1]
        dice[3][1] = dice[2][1]
        dice[2][1] = dice[1][1]
        dice[1][1] = dice[0][1]
        dice[0][1] = tmp
    
    elif dir == 2:  #서쪽
        tmp = dice[1][0] 
        dice[1][0] = dice[1][1]
        dice[1][1] = dice[1][2]
        dice[1][2] = dice[3][1]
        dice[3][1] = tmp
   
    elif dir == 3:  #북쪽
        tmp = dice[0][1]
        dice[0][1] = dice[1][1]
        dice[1][1] = dice[2][1]
        dice[2][1] = dice[3][1]
        dice[3][1] = tmp

def get_score():
    global x,y,score
    # 주사위가 도착한 칸 (x,y)에 대한 점수를 계산함.
    # board[x][y]의 숫자가 B라고 했을 때,
    # board[x][y]에서 동서남북으로 연속해서 B와 같은 숫자가 나오는 칸의 수 C를 구한다.
    # 그후, B와 C를 곱한 것이 최종 그 칸에 대한 획득 점수이다. 
    # (이때, 현재 칸이 무조건 포함되므로 C는 1로 시작)
    B = board[x][y]
    C = 1

    queue = deque()
    queue.append([x,y])
    visited = [[False]*M for _ in range(N)]
    visited[x][y] = 1
    while queue:
        cx, cy = queue.popleft()
        for k in range(4):
            nx, ny = cx + dr[k], cy + dc[k]
            if nx<0 or ny<0 or nx>=N or ny>=M:
                continue
            if visited[nx][ny]:
                continue
            if board[nx][ny] == B:
                queue.append([nx,ny])
                visited[nx][ny] = True
                C += 1
    score += B*C

def decide_dir():
    global dice, x, y, dir
    # 다음 주사위 이동 방향을 정함.
    # 주사위 아랫면(dice[3][1] A)와 주사위가 있는 칸의 점수 (board[x][y] B)를 비교함
    A = dice[3][1] #주사위 아랫면
    B = board[x][y] #주사위가 놓인 칸의 점수

    
    if A>B: #이동방향 시계방향으로 회전 (0->1->2->3->0)
        dir = (dir+1) % 4
    elif A<B: #이동방향 반시계방향으로 회전 (3->2->1->0->3)
        dir = (dir+3) % 4

for i in range(K):
    move()
    get_score()
    decide_dir()
print(score)
    
