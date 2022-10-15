T = int(input())
for t in range(1,T+1):
    N, K = map(int,input().split())     #지도 한변의 길이: N, 최대 공사 가능 깊이: K
    board = []
    for i in range(N):
        board.append(list(map(int,input().split())))

    max_value= max([max(row) for row in board])
    visited = [[False] * N for _ in range(N)]
    max_length = 0
    start = []
    for r in range(N):
        for c in range(N):
            if board[r][c] == max_value:
                start.append([r,c])



    def dfs(r, c, h, cut, length):
        dr = [-1,0,1,0]
        dc = [0,-1,0,1]
        global max_length, visited

        if max_length< length:
            max_length = length

        for d in range(4):
            nr, nc = r + dr[d], c + dc[d]
            if 0<=nr<N and 0<=nc<N and not visited[nr][nc]:
                nh = board[nr][nc]
                if nh < h:
                    visited[nr][nc] = True
                    dfs(nr,nc,nh,cut,length+1)
                    visited[nr][nc] = False
                elif nh >= h:
                    if nh - K < h and not cut:
                        for k in range(1,K+1):
                            if board[nr][nc] - k >= 0:
                                if board[nr][nc] - k >= h:
                                    continue
                                nh = board[nr][nc] - k
                                cut = True
                                visited[nr][nc] = True
                                dfs(nr,nc,nh,cut,length+1)
                                cut = False
                                visited[nr][nc] = False


    for r,c in start:
        visited[r][c] = True
        dfs(r,c,board[r][c],False,1)
        visited[r][c] = False

    print('#{} {}'.format(t,max_length))
