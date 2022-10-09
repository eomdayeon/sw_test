# 0 -> 빈칸, 1-> 집, 2-> 치킨집
# 즉, 2인 것들 중에서 M개를 골라서 도시의 치킨 거리를 계산함.
# => 2(치킨집)의 개수가 K개라 했을 때, K개 중에 M개를 고르는 조합. (이 때, 순서는 고려하지 않는다.)
# 도시의 치킨 거리가 가장 작을 때를 출력함.


result = 9999
chicken_idx=[]


def distance(chicken_idx):
    sum = 0 
    for hx, hy in house:
        temp = []
        for k in chicken_idx:  #이 부분을 실수했다. chicken_idx는 선택된 chicken에 대한 index를 저장하는 배열이므로, 해당 index를 탐색해야 하기 때문에 for k in range(0,len(chicken_idx)): 라고 하면 틀렸다. for문 범위 실수에 주의하자.
            cx,cy = chicken[k]
            temp.append(abs(cx - hx) + abs(cy - hy))
        sum += min(temp)
    return sum


#city를 탐색하면서 치킨집(2)을 M개 선택함
def comb(idx, cnt, M):
    global result, select

    if len(chicken_idx) == M:   #만약 M개의 치킨집이 다 선택되었다면
        sum = distance(chicken_idx)   # 치킨 거리 계산해서 작은지 확인한다.
        result = min(result, sum)
        return

    for i in range(idx, len(chicken)):
        chicken_idx.append(i)       # 치킨집 5개 (0,1,2,3,4) 중 선택되는 index를 저장한다. -> 나중에 해당 치킨집의 위치는 chicken[인덱스][0],chicken[인덱스][1]로 구할 수 있음.
        comb(i + 1, cnt + 1, M)
        chicken_idx.pop()


N, M = map(int, input().split())
city = []

for i in range(N):
    city.append(list(map(int, input().split())))

chicken = []
house  = []
sum = 0

#city 맵을 탐색하며 치킨집(2)에 해당하는 위치(i,j)를 chicken 리스트에 저장한다.
for i in range(N):
    for j in range(N):
        if city[i][j] == 1:
            house.append((i,j))
        elif city[i][j] == 2:
            chicken.append((i, j))



#치킨집 K개 중에 최대 M개를 선택하는 경우의 수를 탐색한다. (M이 3이라면, 치킨집 K개 중에 1개 선택, 2개 선택 , 3개 선택하는 경우의 수를 다 탐색해야 한다.)
for m in range(1, M + 1):
    comb(0, 0, m)

print(result)




