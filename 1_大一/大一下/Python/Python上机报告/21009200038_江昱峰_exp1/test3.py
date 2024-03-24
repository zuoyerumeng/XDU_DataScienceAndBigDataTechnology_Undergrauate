n=int(input("请输入4位整数："))
if not n%400 or not n%4 and n%100:print("闰年")
else:print("平年")