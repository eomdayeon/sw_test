N = int(input())

classroom = [[0] * N for _ in range(N)]

students = []
for i in range(N**2):
    students.append(list(map(int,input().split())))


dr = [-1,0,+1,0]
dc = [0,-1,0,+1]

for info in students:
    student = info[0]
    temp = []
    for r in range(N):
        for c in range(N):
            if classroom[r][c] == 0:
                blank = 0
                like = 0
                for d in range(4):
                    nr, nc = r + dr[d], c+ dc[d]
                    if 0<=nr<N and 0<=nc<N:
                        if classroom[nr][nc] == 0:
                            blank+=1
                        if classroom[nr][nc] in info[1:]:
                            like+=1
                temp.append([like,blank,r,c])

    temp = sorted(temp,key = lambda x: (-x[0],-x[1],x[2],x[3]))
    classroom[temp[0][2]][temp[0][3]] = student


students.sort()
result = 0
for r in range(N):
    for c in range(N):
        number = classroom[r][c]
        cnt = 0
        for d in range(4):
            nr, nc = r + dr[d], c+ dc[d]
            if 0<=nr<N and 0<=nc<N:
                if classroom[nr][nc] in students[number-1][1:]:
                    cnt+=1
        if cnt == 1:
            result += 1
        elif cnt == 2:
            result += 10
        elif cnt == 3:
            result += 100
        elif cnt == 4:
            result += 1000

print(result)
