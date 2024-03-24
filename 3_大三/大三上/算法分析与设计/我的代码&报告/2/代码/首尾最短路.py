graph=[]
print("请输入二维边权矩阵：")
try:
    while True:
        graph.append(list(map(int,input().split())))
except EOFError:
    pass
n=len(graph)

for k in range(n):
    for i in range(n):
        for j in range(n):
            graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j])
print("首尾节点间的最短路径为：{}".format(graph[0][n-1]))