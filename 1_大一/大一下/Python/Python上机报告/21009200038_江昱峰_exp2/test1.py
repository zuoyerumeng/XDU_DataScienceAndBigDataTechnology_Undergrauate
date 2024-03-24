string=input("请输入一个字符串:")
ans=[["大写字母",0],["小写字母",0],["数字",0],["其他字符",0]]
for i in string:
    if 'A'<=i<='Z':ans[0][1]+=1
    elif 'a'<=i<='z':ans[1][1]+=1
    elif '0'<=i<='9':ans[2][1]+=1
    else:ans[3][1]+=1
print(tuple(ans))