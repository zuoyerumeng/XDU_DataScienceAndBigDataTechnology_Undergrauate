class PriorityQueue():
    def init(self):
        self.heap = []

    def add(self, value):
        self.heap.append(value)
        self._siftup(len(self.heap)-1)

    def _siftup(self, index):
        if index > 0:
            parent = int((index - 1) / 2)
            if self.heap[parent] > self.heap[index]:
                self.heap[parent], self.heap[index] = self.heap[index], self.heap[parent]
                self._siftup(parent)

    def extract(self):  # 删除堆顶元素并返回此元素值

        if not self.heap:print('队列已空！')
        value = self.heap[0]
        self.heap[0] = self.heap[len(self.heap)-1]
        self._siftdown(0)
        return value

    def _siftdown(self, index):
        if index < len(self.heap):
            left = 2 * index + 1
            right = 2 * index + 2
            if left < len(self.heap) and right < len(self.heap) \
                    and self.heap[left] <= self.heap[right] \
                    and self.heap[left] <= self.heap[index]:
                self.heap[left], self.heap[index] = self.heap[index], self.heap[left]
                self._siftdown(left)
            elif left < len(self.heap) and right < len(self.heap) \
                    and self.heap[left] >= self.heap[right] \
                    and self.heap[right] <= self.heap[index]:
                self.heap[right], self.heap[index] = self.heap[index], self.heap[right]
                self._siftdown(left)
            if left < len(self.heap) and right > len(self.heap) \
                    and self.heap[left] <= self.heap[index]:
                self.heap[left], self.heap[index] = self.heap[index], self.heap[left]
                self._siftdown(left)
p=PriorityQueue()
p.heap = list(map(int, input("请依次输入元素值以初始化优先队列：").split()))
p.heap.sort()
try:
    while True:
        kind = eval(input("请输入对优先队列执行的操作：(输入1插入元素，输入2删除队首并返回首元素，输入3查询队列首元素）"))
        if kind == 1:
            n = eval(input("请输入要插入的元素："))
            p.add(n)
        elif kind == 2:
            print("队列的首元素为：{0},删除成功！".format(p.extract()))
        elif kind == 3:
            print("队列的首元素为：{0}".format(p.heap[0]))
        else:print("您输入的值非法！")
except EOFError:
    pass