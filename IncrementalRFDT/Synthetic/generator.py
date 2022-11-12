import random
import math
import sys

size = 100000
feature = 10
considered = 10
classes = 2
concept = int(sys.argv[1])
block_size = int(size/concept)
gradual_size = int(block_size/considered)

one = [0 for i in range(classes)]
data = []
resultAbrupt = []
resultGradual = []
posF = []
negF = []
newPosF = []
newNegF = []
    
tmp = [i for i in range(feature)]
random.shuffle(tmp)
oldPosF = tmp[:round(considered/2)]
oldNegF = tmp[round(considered/2):considered]

for i in range(size):
    if i%block_size==0:
        tmp = [i for i in range(feature)]
        random.shuffle(tmp)
        newPosF = tmp[:round(considered/2)]
        newNegF = tmp[round(considered/2):considered]
    if i%gradual_size == 0:
        index = round(i/gradual_size)
        if i%(2*gradual_size)==0:
            index = round(index/2)
            posF = newPosF[:index+1] + oldPosF[index+1:] 
        else:
            index = round((index-1)/2)
            negF = newNegF[:index+1] + oldNegF[index+1:] 
        
    singleData = []
    for j in range(feature):
        x = random.randint(0, 1)
        singleData.append(x)
    
    tAbrupt = 0
    for j in oldPosF:
        if singleData[j]:
            tAbrupt += 1
    for j in oldNegF:
        if not singleData[j]:
            tAbrupt += 1
    if tAbrupt*2 <= considered:
        resultAbrupt.append(0)
    else:
        resultAbrupt.append(1)

    tGradual = 0
    for j in posF:
        if singleData[j]:
            tGradual += 1
    for j in negF:
        if not singleData[j]:
            tGradual += 1
    if tGradual*2 <= considered:
        resultGradual.append(0)
    else:
        resultGradual.append(1)
    
    data.append(singleData)

name = "2synthetic_"+sys.argv[1]
with open(name+"_gradual","w") as f:
    for i in range(size):
        for j in range(feature):
            f.write(str(data[i][j]))
            f.write(" ")
        f.write(str(resultGradual[i]))
        f.write("\n")
with open(name+"_abrupt","w") as f:
    for i in range(size):
        for j in range(feature):
            f.write(str(data[i][j]))
            f.write(" ")
        f.write(str(resultAbrupt[i]))
        f.write("\n")
