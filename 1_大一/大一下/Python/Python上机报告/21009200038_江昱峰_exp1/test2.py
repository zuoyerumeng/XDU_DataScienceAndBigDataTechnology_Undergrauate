import random
a,b=input("请输入两个小数，代表生成随机数的区间:").split()
a,b=eval(a),eval(b)
book=[]
for i in range(10):book.append(random.uniform(a,b))
print(sorted(book))
book=[]
for i in range(10):book.append(random.uniform(a,b))
print(sorted(book,reverse=True))