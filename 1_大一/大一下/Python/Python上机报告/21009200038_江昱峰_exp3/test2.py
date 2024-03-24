class queue(object):
    def __init__(self):
        self.queue = []

    def enqueue(self,item):
        # 入队
        self.queue.append(item)

    def outqueue(self):
        # 出队
        if not self.queue == []:
            self.queue.pop(0)
        else :
            return None

    def head(self):
        if not self.queue == [] :
            print(self.queue[0])
        else :
            return None

    def tail(self):
        if not self.queue == []:
            print(self.queue[-1])
        else :
            return None

    def is_Empty(self):
        return self.queue == []

    def length(self):
        print(len(self.queue))
