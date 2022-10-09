import heapq


M, S = map(int, input().split())  #물고리 M마리, 마법 연습 S회
fish = []  #각 물고기에 대한 정보가 들어간 리스트 [[fx,fy,d],[fx,fy,d],[fx,fy,d]...]

for i in range(M):
    fx, fy, d = map(int, input().split())
    fish.append([fx, fy, d])  #물고기 위치, 방향

sx, sy = map(int, input().split())  #상어의 위치

fishmap = [[[] for _ in range(5)] for _ in range(5)]  #격자맵 생성하는 2중 포문 주의
smell = [[0] * 5 for _ in range(5)]  #격자맵 생성하는 2중 포문 주의
result = 0

for f in fish:
    fx, fy, d = f
    fishmap[fx][fy].append(d)


shark_move = []  #상어 이동 리스트 (총 64가지)
for i in range(1,5):
    for j in range(1,5):
        for k in range(1,5):
            shark_move.append([i,j,k])


#---입력-끝----------------------------------------------

#1.상어가 모든 물고기에 복제 마법을 시전 -> 5번에서 물고기가 복제되어 칸에 반영될 것. (즉, 이때 물고기 위치를 저장하는 맵 필요)
def magic():
    fish_copy = [[[] for _ in range(5)] for _ in range(5)]
    for i in range(1, 5):
        for j in range(1, 5):
            for f in fishmap[i][j]:
                fish_copy[i][j].append(f)

    return fish_copy
  
#방향 전환 함수
def rotate(dir):
    if dir == 1:
        return 8
    else:
        dir = (dir -1)
    return dir

#2. 모든 물고기가 한칸 이동. (상어 있는 칸, 물고기 냄새가 있는 칸으로 이동 불가)
#   각 물고기는 이동할 수 있는 칸 향할 때까지, 방향 45도 반시계 회전하고 이동한다.
#   이때, 이동할 수 있는 칸 없으면 이동 안함.
def fish_move():
    dr = [0, 0, -1, -1, -1, 0, 1, 1, 1]  # 0,1,2,3,4,5,6,7 (상어이동)
    dc = [0, -1, -1, 0, 1, 1, 1, 0, -1]
    fishtempmap = [[[] for _ in range(5)] for _ in range(5)]

    for x in range(1,5):
        for y in range(1,5):
            for dir in fishmap[x][y]:
                flag = False            #flag 위치 주의하기. -> 이거 때문에 모든 이동 방향을 돌아도 못가는 경우 안이동하는 물고기 처리가 안되었음
                for k in range(8):
                    nx = x + dr[dir]
                    ny = y + dc[dir]
                    if nx<=0 or ny<=0 or nx>4 or ny>4:
                        dir = rotate(dir)
                        continue
                    elif nx == sx and ny == sy: #만약 상어가 있다면 이동 불가
                        dir = rotate(dir)
                        continue
                    elif smell[nx][ny] > 0: #만약 물고기 냄새가 있다면 이동불가
                        dir = rotate(dir)
                        continue
                    else:
                        fishtempmap[nx][ny].append(dir)
                        flag = True
                        break
                if flag == False:
                    fishtempmap[x][y].append(dir)               
    return fishtempmap

  
# 사전순으로 변환하는 함수
def c(command):
    num = str(command[0]) + str(command[1]) + str(command[2])
    return int(num)
  
#3. 상어가 연속해서 3칸 이동 (인접한 칸 상하좌우 이동가능)
#   연속해서 이동하는 중에 물고기가 있으면, 그 칸에 있는 물고기가 격자에서 제외됨. -> 상어가 이동하는 경우의 수 각각에 대해 제외되는 물고기 수 저장하는 리스트 필요
#   이때, 제외된 모든 물고기는 물고기 냄새를 남김
#   가능한 이동 방법 중 제외되는 물고기 수가 제일 많은 방법으로 이동함. (연속해서 3칸 이동하는 방법에 대해 모두 탐색 필요)
#   제외되는 물고기 수가 많은 방법이 여러개면, 사전 순으로 가장 앞서는 방법 사용
#   이때 사전 순으로 가장 앞서는 방법 : 방향을 정수로 변환함 -> [상:1, 좌:2, 하:3, 우:4] (즉, 우 -> 하 ->좌 ->상 순으로 앞서는 방법)
#   변환을 모두 마쳤으면 수를 이어 붙여 정수로 만들어서 정수가 크면 사전 순으로 앞선 것.(ex. [상,하,좌]-> [1,3,2] -> 132  
def move_shark():
    mr = [0,-1,0,1,0] # 1(상) 2(좌) 3(하) 4(우)
    mc = [0,0,-1,0,1]
    heap = []
    global sx, sy

    for command in shark_move:  #[상(1), 좌(2), 하(3)]   1(상) 2(좌) 3(하) 4(우)
        visited = [[False] * 5 for _ in range(5)]
        eat = 0
        flag = True
        cur_sx, cur_sy = sx, sy
        for index in command:
            next_sx = cur_sx + mr[index]
            next_sy = cur_sy + mc[index]
            if next_sx<=0 or next_sy<=0 or next_sx>4 or next_sy>4:
                flag = False
                break
            else:
                if not visited[next_sx][next_sy]:   #if fishmap[next_sx][next_sy] and not visited[next_sx][next_sy]: 라고 해서 틀림. -> 가는 경로에 물고기가 없다고 해당문을 실행하지 않게 되면 물고기가 이동 못해서 그다음 경로로 못가게 된다.
                    visited[next_sx][next_sy]=True
                    eat += len(fishmap[next_sx][next_sy]) #제외되는 물고기 수 저장
                    cur_sx, cur_sy = next_sx, next_sy
        if flag:
            heapq.heappush(heap, (-eat, c(command), command))

    eated, dictnum, moves = heapq.heappop(heap)
    for index in moves:
        sx += mr[index]
        sy += mc[index]
        if fishmap[sx][sy]: #물고기가 있는 경우
            smell[sx][sy] = 3 #냄새를 남긴다.
            fishmap[sx][sy].clear()  #fishmap에서 물고기 없앤다.

            
# 4.  두번째 전 연습때 생긴 물고기 냄새가 격자에서 사라짐 -> 몇번째 연습때 생긴 냄새인지 기록해야함
def remove_smell():
    
    for i in range(1,5):
        for j in range(1,5):
            if smell[i][j] > 0 :
                smell[i][j] -= 1

# 5. 1에서 사용한 복제 마법이 완료됨. 1에서의 위치와 방향을 그대로 갖는 물고기가 복제됨.
def fishcopy(fc):
    for i in range(1,5):
        for j in range(1,5):
            for f in fc[i][j]:
                fishmap[i][j].append(f)



for i in range(S):  #S번 반복


    #1. 상어가 모든 물고기에 복제 마법을 시전 -> 5번에서 물고기가 복제되어 칸에 반영될 것. (즉, 이때 물고기 위치를 저장하는 맵 필요)
    fc = magic()

    #2. 모든 물고기가 한칸 이동. (상어 있는 칸, 물고기 냄새가 있는 칸으로 이동 불가)
    #   각 물고기는 이동할 수 있는 칸 향할 때까지, 방향 45도 반시계 회전하고 이동한다.
    #   이때, 이동할 수 있는 칸 없으면 이동 안함.
    fishmap = fish_move()

    #3. 상어가 연속해서 3칸 이동 (인접한 칸 상하좌우 이동가능)
    #   연속해서 이동하는 중에 물고기가 있으면, 그 칸에 있는 물고기가 격자에서 제외됨. -> 상어가 이동하는 경우의 수 각각에 대해 제외되는 물고기 수 저장하는 리스트 필요
    #   이때, 제외된 모든 물고기는 물고기 냄새를 남김
    #   가능한 이동 방법 중 제외되는 물고기 수가 제일 많은 방법으로 이동함. (연속해서 3칸 이동하는 방법에 대해 모두 탐색 필요)
    #   제외되는 물고기 수가 많은 방법이 여러개면, 사전 순으로 가장 앞서는 방법 사용
    #   이때 사전 순으로 가장 앞서는 방법 : 방향을 정수로 변환함 -> [상:1, 좌:2, 하:3, 우:4] (즉, 우 -> 하 ->좌 ->상 순으로 앞서는 방법)
    #   변환을 모두 마쳤으면 수를 이어 붙여 정수로 만들어서 정수가 크면 사전 순으로 앞선 것.(ex. [상,하,좌]-> [1,3,2] -> 132
    move_shark()

    #4.  두번째 전 연습때 생긴 물고기 냄새가 격자에서 사라짐 -> 몇번째 연습때 생긴 냄새인지 기록해야함
    remove_smell()

    #5. 1에서 사용한 복제 마법이 완료됨. 1에서의 위치와 방향을 그대로 갖는 물고기가 복제됨.
    fishcopy(fc)

for i in range(1,5):
    for j in range(1,5):
        if fishmap[i][j]:
            result += len(fishmap[i][j])
print(result)
