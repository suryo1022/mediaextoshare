from tkinter import E
import numpy as np
import scipy as sp


filename = 'recogcount-dash2.txt'

# 認識回数のテキストファイルを読み込む
f = open(filename, 'r')
# 行単位でリストに保存
datalist = f.readlines()

nums = np.zeros(len(datalist))

print(len(datalist))

# 数値を配列に格納
i = 0
for sen in datalist:
    #print(sen[0:2])
    if sen[0:2] == "n1":
        nums[i] = sen.split(' ')[1]
        i = i + 1
    elif sen[0:2] == "n2":
        nums[i] = sen.split(' ')[1]
        i = i + 1

results = np.empty(int(i))

print(i)
j = 0
k = 0
a1 = a2 = 0
while j+1 <= 40-1:
    if j % 4 == 0:
        a1 = float(nums[j])
        #print(a1)
    elif j % 4 == 2:
        a2 = float(nums[j+1])
        #print(a2)
        k = k + 1
        results[k] = (a1 + a2) / 2
        #print("a = ")
        print(+results[k])

    j = j + 2

#print(nums)

#print(results)
#np.savetxt("ninshikiritsu.txt", results)


f.close()
