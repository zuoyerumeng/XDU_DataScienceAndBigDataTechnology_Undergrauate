val=[20,30,65,40,60]
wei=[10,20,30,40,50]
dp=[[-1 for i in range(6)]for i in range(101)]
def rec(con,t):
    if dp[con][t]!=-1:return dp[con][t]
    if t==5:return 0
    if con<wei[t]:dp[con][t]=rec(con,t+1)
    else:dp[con][t]=max(val[t]+rec(con-wei[t],t+1),rec(con,t+1))
    return dp[con][t]
print(rec(100,0))