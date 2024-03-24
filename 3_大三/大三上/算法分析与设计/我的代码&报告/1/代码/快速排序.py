def qs(array):
    if len(array) < 2: return array
    t = array[0]
    l = [i for i in array[1:] if i <= t]
    r = [i for i in array[1:] if i > t]
    return qs(l) + [t] + qs(r)
lst=list(map(int,input("请输入待排序的数组：").split()))
print("排序后的数组为：{0}".format(qs(lst)))
'''
最大次数：O(N^2)
实例：逆序排列的数列

最小次数：0
实例：已经正序排好的数列
'''