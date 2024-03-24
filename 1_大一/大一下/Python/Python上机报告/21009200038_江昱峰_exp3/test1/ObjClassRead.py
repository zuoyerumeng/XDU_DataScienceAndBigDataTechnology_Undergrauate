import pickle # 读出对象和类,并通过该类再创建对象
from Stack import stack
with open("Stack.py", "rb") as f:
    s = pickle.load(f)
    s2 = pickle.load(f)
print(s)
print(s.stack)
print(s.maxsize)
stack2 = s2(66) # 这步还是没查到问题在哪。。
