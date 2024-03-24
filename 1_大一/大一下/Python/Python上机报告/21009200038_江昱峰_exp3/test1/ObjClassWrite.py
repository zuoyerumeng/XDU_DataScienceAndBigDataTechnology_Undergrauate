import pickle # 读出对象和类,并通过该类再创建对象
from Stack import stack
s = stack() # 创建一个对象,把对象及类写入
with open("Stack.py", "wb") as f: # 这步还是没查到问题在哪。。
    pickle.dump(s, f)