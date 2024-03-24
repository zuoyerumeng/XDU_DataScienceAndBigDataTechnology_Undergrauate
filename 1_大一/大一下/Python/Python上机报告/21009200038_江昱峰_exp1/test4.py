y,x=(0,0)
x = int(input("请输入你要计算的自变量"))
if x<0 :
    y =0
elif 0<=x<5:
    y = x
elif 5<=x<10:
    y = 3*x-5
elif 10 <= x <20:
    y = 0.5*x-2
else:
    y= 0
print("计算结果是%d"%y)