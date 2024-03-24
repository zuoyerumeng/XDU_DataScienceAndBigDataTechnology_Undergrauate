import math

def isPrime(n):
    if n==1:return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if not n % i: return False
    return True


l, r = list(map(int, input("请输入生成器的起止范围：").split()))
print("质数的和为：",sum(i for i in range(l, r + 1) if isPrime(i)))