def dijkstra(s):
    distance[s] = 0
    while True:
        v = -1
        for u in range(n):
            if not used[u] and (v == -1 or distance[u] < distance[v]):
                v = u
        if v == -1:break
        used[v] = True
        for u in range(n):
            distance[u] = min(distance[u], distance[v] + cost[v][u])

cost=[]
head=eval(input("请输入头结点："))
print("请输入二维边权矩阵：")
try:
    while True:
        cost.append(list(map(int,input().split())))
except EOFError:
    pass
n=len(cost)
distance=[10000 for i in range(n)]
used=[0 for i in range(n)]
dijkstra(head)
for i in range(n):
    if i != head:
        print("到结点{0}的最短路径为：{1}".format(i,distance[i]))