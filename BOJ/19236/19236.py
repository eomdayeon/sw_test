import copy

#물고기의 정보는 두 정수 a,b로 이루어짐. (a,b) = (물고기번호, 방향)
dr = [0, -1, -1,  0, +1, +1, +1,  0, -1] #위, 왼위, 왼, 왼아래, 아래, 오른아래, 오른, 오른위
dc = [0,  0, -1, -1, -1,  0, +1, +1, +1] #1,2,3,4,5,6,7,8

board = [[0] * 4 for _ in range(4)]
fish  = [0 for _ in range(17)]  #물고기 정보를 담은 리스트
for i in range(4):  
    tmp = list(map(int,input().split()))
    for t in range(0,8,2):
        board[i][t//2] = [tmp[t],tmp[t+1]]

def rotate(dir): #물고기 방향 45도 회전
    if dir == 8:
        dir = 1
    else:
        dir = dir + 1
    return dir


def find_fish(board, index):
    for i in range(4):
        for j in range(4):
            if board[i][j][0] == index:
                return (i, j)
    return None

def move_fish(sx,sy,board):
    #물고기가 번호가 작은 물고기부터 이동
    for i in range(1,17):
        position = find_fish(board, i)
        if position != None:
            fx, fy = position
            fnum, fdir = board[fx][fy] #i번 물고기의 이동방향 
            
            for _ in range(8):
                #만약 맵 벗어나거나 상어가 있으면 방향을 바꾼다.
                nfx =  fx + dr[fdir]
                nfy =  fy + dc[fdir]
                if 0<=nfx<4 and 0<=nfy<4:
                    if not (nfx==sx and nfy==sy):
                        board[fx][fy] = board[nfx][nfy]          
                        board[nfx][nfy] = (fnum, fdir)
                        break
                fdir = rotate(fdir)


def possible(sx,sy,shark_dir,board):
    candi =[]
    for idx in range(1,4):
        nsx, nsy = sx + idx*dr[shark_dir], sy + idx*dc[shark_dir]
        if 0<=nsx<4 and 0<=nsy<4 and board[nsx][nsy] != (-1,-1):
            candi.append([nsx,nsy])
    return candi


def dfs(sx,sy,shark_eat,shark_dir,board):
    global max_eat
    #상어는 shark_dir 방향으로 이동 가능. 
    #상어가 한번에 여러 칸 이동가능 (맵이 4x4이므로 최소 1칸, 최대 3칸 이동가능하다)
    #이때, 이동가능한 칸이 없다면 종료 (이동성공하면 다시 move_fish 진행)
    tempboard = copy.deepcopy(board)
    
    fnum, fdir = tempboard[sx][sy] 
    shark_eat += fnum  #상어가 먹은 물고기번호 
    shark_dir = fdir  #상어 이동방향
    tempboard[sx][sy] = (-1,-1)    #상어가 먹은 곳은 (-1,-1)로 표시 -> (물고기번호,이동방향)


    move_fish(sx,sy,tempboard)

    candi = possible(sx,sy,shark_dir,tempboard)

    if not candi:
        max_eat = max(max_eat,shark_eat)
        return
    for nsx, nsy in candi:
        dfs(nsx,nsy,shark_eat,shark_dir,tempboard)





sx, sy = 0, 0  #상어 위치
max_eat = 0
shark_eat, shark_dir = 0,0 
dfs(sx,sy,shark_eat,shark_dir,board)

print(max_eat)
