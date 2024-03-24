import argparse
import os
import chardet
def main():
    parse = argparse.ArgumentParser()
    parse.add_argument('name',type=str,default='none',help='请输入你想要转换格式的文件名称')
    parse.add_argument('--encoding', type=str, default='none', help='（选择）请输入改文件的编码方式')
    args = parse.parse_args()
    encodeway = ''
    date = ''
    with open(args.name,'rb') as f:#检测原编码格式
        date = f.read()
        encodeway = chardet.detect(date)['encoding']
        print(encodeway)#得到原编码格式
    with open(args.name,'r',encoding=encodeway) as f:
        date = f.read()
        f.close()#获取文件内容
    with open(args.name,'w',encoding='utf-8') as f:
        f.write(date)#重写文件
        f.close()
    with open(args.name,'rb') as f:
        encodeway = chardet.detect(f.read())['encoding']
        print(encodeway)#在此检测文件内容
        f.close()

if __name__ == '__main__':
    main()