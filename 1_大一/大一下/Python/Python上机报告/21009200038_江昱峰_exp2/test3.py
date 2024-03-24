def sortedsimulation(array):#快速排序算法
    if len(array) < 2: return array
    t = array[0]
    l = [i for i in array[1:] if i <= t] #注意此处i即为array[…]!

    r = [i for i in array[1:] if i > t]
    return sortedsimulation(l) + [t] + sortedsimulation(r)
print(sortedsimulation(list(map(int,input("请输入任意多个数或字符串：").split()))))
