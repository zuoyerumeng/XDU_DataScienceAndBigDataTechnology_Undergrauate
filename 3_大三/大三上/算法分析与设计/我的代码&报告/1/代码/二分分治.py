def find_kth(llst, llen, rlst, rlen, k):
    if llen > rlen:
        return find_kth(rlst, rlen, llst, llen, k)
    # 长度小的数组已经没有值了,从rlst找到第k大的数
    if not llen:
        return rlst[k-1]
    # 找到第1 大的数,比较两个列表的第一个元素,返回最小的那个
    if k == 1:
        return min(llst[0], rlst[0])
    middle = min(k >> 1, llen)
    middle_ex = k - middle
    # 舍弃llst的一部分
    if llst[middle-1] < rlst[middle_ex-1]:
        return find_kth(llst[middle:], llen-middle, rlst, rlen, k-middle)
    # 舍弃rlst 的一部分
    elif llst[middle-1] > rlst[middle_ex-1]:
        return find_kth(llst, llen, rlst[middle_ex:], rlen-middle_ex, k-middle_ex)
    else:
        return llst[middle-1]

llst=list(map(int,input("请输入第一个有序序列：").split()))
rlst=list(map(int,input("请输入第二个有序序列：").split()))
k=eval(input("请输入要查找第几大的数："))
if len(llst)>len(rlst):llst,rlst=rlst,llst
print("是{}".format(find_kth(len(llst), rlst, len(rlst), k)))
