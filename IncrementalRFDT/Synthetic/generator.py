import random
import math
import sys

size = int(sys.argv[1])
feature = int(sys.argv[2])
classes = int(sys.argv[3])
concept = int(sys.argv[4])
block_size = int(size/concept)

one = [0 for i in range(classes)]
data = []
result = []
coefficient = random.uniform(-1, 1)
for i in range(size):
    if i%block_size==0:
        nValid = random.randint(1, feature)
        valid1 = [random.randint(0, feature-1) for j in range(nValid)]
        valid2 = [random.randint(0, feature-1) for j in range(nValid)]

    singleData = []
    for j in range(feature):
        x = random.uniform(0, 1)
        singleData.append(x)
    
    r = 0
    for j in range(nValid):
        r+=singleData[valid1[j]]*singleData[valid2[j]]
    if classes==2:
        r = int((r/nValid)*4<1)
    elif classes==5:
        r = r/nValid
        if(r*10<1):
            r=4
        elif(r*5<1):
            r=3
        elif(r*3<1):
            r=2
        elif(r*2<1):
            r=1 
        else:
            r=0
        pass
    if r == classes:
        r-=1

    result.append(r)
    
    one[r]+=1
    data.append(singleData)
    if(len(singleData)!=feature):
        print("error 1")
print(one)

name = "synthetic"
for i in range(1, 5):
    name+="_"+sys.argv[i]
with open(name,"w") as f:
    for i in range(size):
        for j in range(feature):
            f.write(str(data[i][j]))
            f.write(" ")
        f.write(str(result[i]))
        f.write("\n")
