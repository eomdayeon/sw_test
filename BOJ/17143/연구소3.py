# 연구소는 0 -> 빈칸, 1 -> 벽, 2 -> 바이러스를 놓을 수 있는 위치로 구성됨
# 2는 바이러스 놓을 수 있는 위치이기 때문에, 그중에 M개를 골라서 바이러스를 놓을 수 있다.
# 즉, 2의 개수가 K개라고 가정하면, K개 중에 M개를 뽑는 조합의 경우를 탐색한다.(dfs)
# K개 중에 M개 뽑는 모든 경우의 수에 대해, 바이러스가 빈칸에 바이러스를 확산시킨다.(bfs) -> 언제까지? 모든 0이었던 칸이 활성화될 때 까지.
# 모든 0이 탐색되었을 때 최종 결과를 return 해준다.

# 실수한 부분!!!!! 시간을 기록하며 더해나가는 temp배열을 board배열로 복사해서 썼는데, 그러면 벽(1)과 바이러스(2)까지 모두 저장되어있어서 temp에 시간을 갱신해주면서 값이 꼬일 가능성이 있다.
# 따라서, 앞으로는 bfs를 통해 기록을 할 때 새로운 배열로 기록을 해주는 것이 좋을 것이다. 

from collections import deque

N, M = map(int, input().split())
board = []
result = 99999

for i in range(N):
    board.append(list(map(int, input().split())))

virus = []
sel_virus_idx = []
count = 0  # 빈칸의 개수 (즉, 바이러스가 퍼뜨려야 하는 개수)
for i in range(N):
    for j in range(N):
        if board[i][j] == 2:
            virus.append((i, j))
        elif board[i][j] == 1:  # 벽이면, 안헷갈리기 위해 -1로 바꿔줌
            board[i][j] = -1
        elif board[i][j] == 0:  # 빈칸 개수 저장
            count += 1


def dfs(idx, cnt):
    global result

    if cnt == M:
        # 만약, M개 다 뽑았다면 그 M개 바이러스에 대해 bfs를 진행한다.
        res = bfs(sel_virus_idx)
        if res < result:
            result = res
        return

    for i in range(idx, len(virus)):
        sel_virus_idx.append(i)
        dfs(i + 1, cnt + 1)
        sel_virus_idx.pop()


def bfs(sel_virus_idx):
    queue = deque()
    visited = [[False] * N for _ in range(N)]
    dx = [-1, 0, +1, 0]
    dy = [0, -1, 0, +1]
    t = [[0]*N for _ in range(N)]   #처음에 board 배열을 temp배열에 모두 복제하고 썼는데, 그럴 필요가 없었다. 괜히 틀리기만 함. -> 시간을 저장하는 t 배열만 쓰면 되고, board배열에서 빈칸인지 비활성화된 바이러스인지 체크한다.
    time = 0
    blank = 0

    for v in sel_virus_idx:  # 선택된 바이러스에 대해 큐에 삽입하고, count저장을 위해 0으로 바꿔줌
        vx, vy = virus[v]
        queue.append((vx, vy))
        visited[vx][vy] = True
        t[vx][vy] = 0

    while queue:

        cx, cy = queue.popleft()

        for k in range(4):
            nx, ny = cx + dx[k], cy + dy[k]
            if nx < 0 or ny < 0 or nx >= N or ny >= N:
                continue

            if board[nx][ny] == 0 and visited[nx][ny] == False:  # 0이고, 방문안한 경우에 큐에 삽입(즉, 바이러스를 퍼뜨림) -> 1초의 시간 소요
                visited[nx][ny] = True
                t[nx][ny] = t[cx][cy] + 1
                queue.append((nx, ny))
                blank += 1
                time = t[nx][ny]

            elif board[nx][ny] == 2 and visited[nx][ny] == False:  # 비활성화 바이러스이고, 방문안한 경우에 활성화
                visited[nx][ny] = True
                t[nx][ny] = t[cx][cy] + 1
                queue.append((nx, ny))


    if blank < count:
        time = 99999

    return time


dfs(0, 0)  # selectvirus 바이러스 후보 K개 중, M개를 뽑는 조합

if result == 99999:
    result = -1
print(result)

