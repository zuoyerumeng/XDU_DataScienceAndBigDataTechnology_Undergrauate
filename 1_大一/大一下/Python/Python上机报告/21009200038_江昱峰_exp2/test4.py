def add():  # 添加信息
    info = input("请依次输入添加人的名字、电话、email、工作单位").split()
    book[info[0]] = info[1:]
    print("添加成功！")


def dele():  # 删除信息
    key = input("请输入要删除人的名字：")
    if key not in book: print("抱歉，您要删除的人不存在！")
    else:
        book.pop(key)
        print("删除成功！")


def query():  # 查询信息
    key = input("请输入要查询人的名字：")
    if key not in book:
        print("抱歉，您要查询的人不存在!")
    else:
        print("此人的电话为：{}".format(book[key][0]))
        print("此人的email为：{}".format(book[key][1]))
        print("此人的工作单位为：{}".format(book[key][2]))

def alloutput():  # 输出所有人的信息
    for key in book:
        print("名字：{}".format(key))
        print("电话：{}".format(book[key][0]))
        print("email：{}".format(book[key][1]))
        print("工作单位：{}".format(book[key][2]))
        print()


book = {}
try:
    while True:
        kind = eval(input("请输入要对通讯录执行的操作：（输入1添加，输入2删除，输入3查询，输入4输出所有人信息)"))
        if kind == 1:add()
        elif kind == 2:
            dele()
        elif kind == 3:
            query()
        elif kind == 4:
            alloutput()
        else:
            print("抱歉，您输入的值不对！")
except EOFError:
    pass
