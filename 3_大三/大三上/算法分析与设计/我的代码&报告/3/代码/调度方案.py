time=list(map(int,input("请输入每个工作分别需要的时间：").split()))
print("最优的调度方案为：{}".format(sorted(time)))