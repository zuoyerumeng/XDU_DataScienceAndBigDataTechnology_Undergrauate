array=list(map(int,input("请依次输入序列值：").split()))
dp = [i for i in array]
ans=array[0]
for i in range(1, len(array)):
    dp[i] = max(dp[i - 1] + array[i], array[i])
print("最大和为：{}".format(max(dp)))