import random

f1 = open("Retired", "r")
f2 = open("Unretired", "r")

f1 = f1.readlines()[:-1]
f2 = f2.readlines()[:-1]

x = []
y = []
length = len(f1)
grade = 0
for i in range(length):
    x.append(int(f1[i].split("\n")[0]))
    y.append(int(f2[i].split("\n")[0]))
    grade += x[-1]-y[-1]

print(grade)
mark = 0.0
for i in range(100000):
    grade2 = 0
    for j in range(length):
        if random.randint(0,1)<1:
            x[j], y[j] = y[j], x[j]
        grade2 += (x[j]-y[j])
    if grade2 > grade:
        mark+=1
    print(grade2)
print(mark/100000)
