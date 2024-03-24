graph=[]
print("请输入二维边权矩阵：")
f,cnt=0,0
while True:
    graph.append(list(map(int,input().split())))
    cnt+=1
    if not f:n=len(graph[0])
    if cnt==n:break

for k in range(n):
    for i in range(n):
        for j in range(n):
            graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j])

book=[]
print("请依次输入首尾节点的值：")
try:
    while True:
        book.append(list(map(int,input().split())))
except EOFError:
    pass
print("两节点间的最短路径依次是：")
for i in book:print(graph[i[0]][i[1]])
