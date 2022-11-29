import random
import math
import sys

size = 50000
feature = 10
considered = 10
classes = 2
concept = int(sys.argv[1])
hard = int(sys.argv[2])
noise = int(sys.argv[3])
block_size = int(size/concept)

one = [0 for i in range(classes)]
data = []
result = []

F = [random.randint(0, 9) for i in range(11)]

for i in range(size):
    if i%block_size==0:
        for i in range(hard):
            x = random.randint(0, 10)
            y = random.randint(0, 9)
            F[x] = y
        
    singleData = []
    for j in range(feature):
        x = random.randint(0, 1)
        singleData.append(x)
    
    t = 0
    for j in range(6):
        if singleData[F[j]] == 0:
            t += 1
    for j in range(6, 11):
        if singleData[F[j]] == 0:
            t -= 1
    if t <= 0:
            if random.randint(0, 99)<noise:
                result.append(1)
            else:
                result.append(0)
    else:
            if random.randint(0, 99)<noise:
                result.append(0)
            else:
                result.append(1)

    
    data.append(singleData)

name = "synthetic_"+sys.argv[1]+"_"+sys.argv[2]

if noise!=0:
    name = str(noise)+"_"+name

with open(name,"w") as f:
    for i in range(size):
        for j in range(feature):
            f.write(str(data[i][j]))
            f.write(" ")
        f.write(str(result[i]))
        f.write("\n")
