class stack(object):
    def __init__(self,stack, maxsize):
        # 创建一个空的栈
        self.stack = []
        self.maxsize=maxsize # 栈的最大空间

    def push(self,val):
        # 入栈
        if self.size()==self.maxsize: # 检查栈是否已满
            print("栈已满！")
        self.stack.append(val)

    def pop(self):
        # 出栈
        if not self.size():
            print("栈为空！")
        return self.stack.pop()

    def peek(self):
        # 获取栈顶元素
        return self.stack[-1]

    def is_empty(self):
        # 检验是否为空
        return self.stack == []

    def size(self):
        # 返回栈元素个数
        return len(self.stack)

