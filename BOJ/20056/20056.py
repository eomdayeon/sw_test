from lib2to3.pgen2 import driver


N, M, K = map(int,input().split())

fireball = []  #파이어볼 M개
for i in range(M):
    fireball.append(list(map(int,input().split()))) # r,c,m,s,d (행,열,질량,속력,방향)-> 파이어볼의 정보

board = [[[] for _ in range(N)] for _ in range(N)]  #NxN 격자 -> 0번행은 N-1행과 연결, 0번열은 N-1열과 연결

result = 0

for fire in fireball:
    r,c,m,s,d  = fire[0], fire[1], fire[2], fire[3], fire[4]
    board[r-1][c-1].append([m,s,d]) #파이어볼 위치(r,c)에 질량,속력,방향 정보를 추가

def move():
    dr = [-1,-1,0,1,1,1,0,-1]
    dc = [0,1,1,1,0,-1,-1,-1]
    tempboard = [[[] for _ in range(N)] for _ in range(N)]
    # 모든 파이어볼이 자기 방향 d로 속력 s만큼 이동
    # 이동하는 중에 같은 칸에 여러개 파이어볼 있을 수도 있음
    for x in range(N):
        for y in range(N):
            if board[x][y]:
                for f in board[x][y]:
                    m, s, d = f
                    nx, ny = x + s*dr[d] , y + s*dc[d]
                    if nx < 0:
                        while nx < 0:
                            nx = nx + N
                    if nx >= N:
                        while nx>=N:
                            nx = nx - N
                    if ny < 0:
                        while ny < 0:
                            ny = ny + N
                    if ny >= N:
                        while ny>=N:
                            ny = ny - N
                    tempboard[nx][ny].append([m,s,d])

    return tempboard

def alleven(td):
    for i in td:
        if i % 2 != 0:
            return False
    return True

def allodd(td):
    for i in td:
        if i % 2 == 0:
            return False
    return True

def merge(board):
    for x in range(N):
        for y in range(N):
            if len(board[x][y]) >= 2:  #2개 이상의 파이어볼이 존재
                #1. 같은 칸에 있는 파이어볼이 하나로 합쳐진다.
                tm, ts, td = 0, 0, []
                for f in board[x][y]:
                    m, s, d = f
                    tm += m         #합쳐진 파이어볼 질량
                    ts += s         #합쳐진 파이어볼 속력
                    td.append(d)
                #2. 파이어볼은 4개의 파이어볼로 나뉜다.
                newm = tm//5        #3. 나누어진 파이어볼의 질량
                news = ts//len(board[x][y])     #3. 나누어진 파이어볼 속력
                if alleven(td) or allodd(td):       #3. 합쳐지는 파이어볼의 방향이 모두 홀수거나 짝수면
                    #방향이 0,2,4,6이 됨.
                    newd = [0,2,4,6]
                else:
                    #방향이 1,3,5,7이 됨.
                    newd = [1,3,5,7]

                board[x][y] = []
                for i in range(4):
                    if newm <= 0:
                        continue
                    board[x][y].append([newm,news,newd[i]])
    return board

for k in range(K):
    board = move()
    board = merge(board)

for i in range(N):
    for j in range(N):
        if board[i][j]:
            for f in board[i][j]:
                result += f[0]  #파이어볼의 질량 더함
print(result)
