import random
from collections import Counter
n=int(input("请输入生成的随机整数的个数："))
base=[i for i in range(101)]
book=[]
for i in range(n):
    book.append(random.choice(base))
print(Counter(book))