lst=list(map(int,input("请依次输入数组元素：").split()))
t=eval(input("请输入求和的目标值："))
lst.sort()
i,j=0,len(lst)-1
f=0
while i<j:
    if lst[i]+lst[j]==t:
        if not f:print("满足要求的元素组为：")
        f=1
        print(lst[i],lst[j])
        i+=1
        j-=1
    elif lst[i]+lst[j]<t:i+=1
    else:j-=1
if not f:print("不存在满足要求的元素组")