def generateBoard():
    board = []
    for i in range(n):
        row[queens[i]] = "Q"
        board.append("".join(row))
        row[queens[i]] = "."
    return board


def backtrack(row):
    if row == n:
        board = generateBoard()
        ans.append(board)
    else:
        for i in range(n):
            if i in columns or row - i in diagonal1 or row + i in diagonal2:
                continue
            queens[row] = i
            columns.add(i)
            diagonal1.add(row - i)
            diagonal2.add(row + i)
            backtrack(row + 1)
            columns.remove(i)
            diagonal1.remove(row - i)
            diagonal2.remove(row + i)


n = eval(input("请输入八皇后的方阵行数："))
ans = []
queens = [-1] * n
columns = set()
diagonal1 = set()
diagonal2 = set()
row = ["."] * n
backtrack(0)
print("所有可能的结果为：")
for i in ans:
    for j in i: print(j)
    print()