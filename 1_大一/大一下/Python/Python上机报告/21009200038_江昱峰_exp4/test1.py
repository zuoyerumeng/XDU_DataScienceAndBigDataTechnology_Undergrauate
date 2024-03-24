import math
class Cylinder():  # 定义类
    def __init__(self, r, h):  # 包含两个属性
        self.r = r
        self.h = h

    def volume(self):  # 定义求体积方法
        V = self.h * math.pi * self.r ** 2
        print("体积为：",V)

    def size(self): # 定义求面积方法
        S= 2*math.pi*(self.r**2+self.r*self.h)
        print("面积为：",S)

test=Cylinder(2,3)
test.size()
test.volume()