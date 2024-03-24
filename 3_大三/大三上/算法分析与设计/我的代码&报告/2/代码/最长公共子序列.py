s1=input()
s2=input()
l1, l2 = len(s1), len(s2)
dp = [[-1 for i in range(l2 + 1)] for i in range(l1 + 1)]

def best(x, y):
    if dp[x][y] != -1: return dp[x][y]
    if x == l1 or y == l2:
        return 0
    if s1[x] == s2[y]:
        dp[x][y] = 1 + best(x + 1, y + 1)
    else:
        dp[x][y] = max(best(x + 1, y), best(x, y + 1))
    return dp[x][y]

print(best(0, 0))