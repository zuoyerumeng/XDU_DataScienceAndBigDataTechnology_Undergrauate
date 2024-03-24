# -*- coding: utf-8 -*-
import os
file=open("partition.txt","r",encoding="GB2312")
file_big=open("part-r-00001.txt","w",encoding="utf-8")
file_small=open("part-r-00000.txt","w",encoding="utf-8")
lines=file.readlines()
for i in lines:
    line=i.split("\t")
    # print(line)
    if int(line[5])>15: file_big.write(i)
    elif int(line[5])<15: file_small.write(i)

file.close()
file_big.close()
file_small.close()    
    