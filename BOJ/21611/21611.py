from collections import deque
N, M = map(int,input().split())

board = []
for i in range(N):
    board.append(list(map(int,input().split()))) 

magic = []
for i in range(M):
    magic.append(list(map(int,input().split())))  #상어가 d방향으로 거리s 이하인 모든칸에 구슬 파괴


sr, sc = N//2, N//2  #상어의 좌표
marble = [0] * (N*N) #일차원 배열로 회전하는 구슬의 좌표 나타냄 -> 0번째는 상어이므로 0으로 표시
dr = [0,-1,+1, 0, 0]
dc = [0, 0, 0,-1,+1]

bombcount = [0, 0, 0, 0]


def board_to_marble(board):
    global marble
    marble[1] = board[sr][sc-1]
    marble[2] = board[sr+1][sc-1]

    def change_dir(dir):
        if dir == 4:
            dir = 1
        elif dir == 1:
            dir = 3
        elif dir == 3:
            dir = 2
        elif dir == 2:
            dir = 4
        return dir 
        
    r, c, dir = sr+1, sc-1, 4  #현재 좌표, 방향

    idx = 3
    for C in range(2,N):
        for k in range(C):
            nr, nc = r + dr[dir], c + dc[dir]
            marble[idx] = (board[nr][nc]) 
            idx += 1
            r, c = nr, nc
        dir = change_dir(dir)

        for k in range(C):
            nr, nc = r + dr[dir], c + dc[dir]
            marble[idx] = (board[nr][nc])
            idx += 1
            r, c = nr, nc
        dir = change_dir(dir)

    for k in range(N-1):
        nr, nc = r + dr[dir], c + dc[dir]
        marble[idx] = (board[nr][nc])
        idx += 1
        r, c = nr, nc

def move(arr):
    new = []
    new.append(0)
    for idx in range(1,N*N):
        if arr[idx]!=0:
            new.append(arr[idx])
    
    for k in range(len(new), N*N):
        new.append(0)
    
    return new

def check_bomb(marble):
    global bombcount
    #4개 이상 연속하는 구슬이 있으면 폭발한다.
    temp = []  #연속하는 구슬 저장하면서 4 이상인지 체크하는 배열로, 이상이면 bomb에 저장해줌
    bomb = []  #폭발할 index 저장
    for i in range(1,N*N):
        if i in temp or marble[i]==0:
            continue
        if marble[i] == marble[i+1]:
            temp = []
            temp.append(i)
            for j in range(i+1,N*N):
                if marble[i] == marble[j]:
                    temp.append(j)
                if marble[i] != marble[j]:
                    break
            if len(temp) >= 4:
                bomb = bomb + temp    

    for bombidx in bomb:
        bombcount[marble[bombidx]] += 1

    return bomb

def change_marble(marble):
    # 연속하는 구슬 ->  하나의그룹
    # 하나의 그룹 -> 구슬 A : 그룹에 든 구슬의 개수, 구슬 B: 구슬 번호 
    # 구슬은 다시 1번칸부터 차례대로 A,B순서대로 삽입  => 새로운 1차원 마블 배열에 넣어주도록 하자
    # 만약, 구슬이 49개 보다 많으면 뒤에는 그냥 생략함 ->49개가 아니라 N*N개로 봐야함!!
    temp = []
    group = []
    group.append(0)
    for i in range(1,N*N):
        if i in temp or marble[i]==0 :
            continue
        if marble[i] == marble[i+1]:
            temp = []
            temp.append(i)
            for j in range(i+1,N*N):
                if marble[i] == marble[j]:
                    temp.append(j)
                if marble[i] != marble[j]:
                    break
            group.append(len(temp))
            group.append(marble[i])

        else:
            group.append(1)
            group.append(marble[i])

    if len(group)<N*N :
        for k in range(len(group), N*N):
            group.append(0)
    return group[0:N*N]   #여기서 구슬이 49개로 고정된다고 착각해서 [0:49]로 해서 인덱스 에러 떴었다.



def marble_to_board(marble):
    global board
    board[sr][sc-1] = marble[1]
    board[sr+1][sc-1] = marble[2]

    def change_dir(dir):
        if dir == 4:
            dir = 1
        elif dir == 1:
            dir = 3
        elif dir == 3:
            dir = 2
        elif dir == 2:
            dir = 4
        return dir 
        
    r, c, dir = sr+1, sc-1, 4  #현재 좌표, 방향

    idx = 3
    for C in range(2,N):
        for k in range(C):
            nr, nc = r + dr[dir], c + dc[dir]
            board[nr][nc] = marble[idx]
            idx += 1
            r, c = nr, nc
        dir = change_dir(dir)

        for k in range(C):
            nr, nc = r + dr[dir], c + dc[dir]
            board[nr][nc] = marble[idx]
            idx += 1
            r, c = nr, nc
        dir = change_dir(dir)

    for k in range(N-1):
        nr, nc = r + dr[dir], c + dc[dir]
        board[nr][nc] = marble[idx]
        idx += 1
        r, c = nr, nc
  

def destroy():
    global marble
    #블리자드 마법 시전
    for d, s in magic:

        #d방향으로 거리s이하인 모든 칸에 구슬을 파괴한다.
        for idx in range(1,s+1):
            targetx = sr + idx*dr[d]
            targety = sc + idx*dc[d]
            board[targetx][targety] = 0  #보드에 0으로 파괴된 것을 표기
            board_to_marble(board)          #파괴된 후에 마블 리스트 새로 만든다.


        #빈칸에 대해 회전하며 한칸씩 당겨짐.
        marble = move(marble)

        while True:
            #4개 이상 연속하는 구슬이 있으면 폭발한다.
            bomb = check_bomb(marble)
            
            if len(bomb) == 0:  #4개 이상 연속하는 구슬이 없으면 중단
                break

            #bomb에 저장된 인덱스에 대해 0으로 바꿔줌 -> 빈칸 발생
            for idx in bomb:
                marble[idx] = 0    
            marble = move(marble) #한칸씩 앞당겨줌


        marble = change_marble(marble)

        marble_to_board(marble)

destroy()
print(bombcount[1] + bombcount[2]*2 + bombcount[3]*3)



