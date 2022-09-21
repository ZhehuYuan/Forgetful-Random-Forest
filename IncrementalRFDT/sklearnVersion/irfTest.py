import irf
import time
import sys

size = int(sys.argv[1])

if 0:
    f = open("../phishing/phishing", "r")
    data = []
    result = []
    for line in f:
        if line=="\n":
            continue
        line = line.replace("\n", "")
        line = line[:-1]
        line = line.split(" ")
        tmp = {}
        for i in range(len(line)-2):
            tmp[i+1]=float(line[i])
        data.append(tmp)
        result.append(int(line[-2]))
    f.close()

    f = irf.IRF(size)
    length = 8000

    total = 0.0
    t = time.time()
    for i in range(length):
        f.add(str(i), data[i], result[i])
        if i%100 == 99 or i==length-1:
            f.commit()
            total+=time.time()-t
            t = time.time()
    print(total)
    count = 0
    for i in range(3055):
        if int(round(f.classify(data[i+length])))==result[i+length]:
            count+=1
    print float(count)/3055

if 0:
    f = open("../KDD/KDDTrain+.txt", "r")
    data = []
    result = []
    for line in f:
        if line=="\n":
            continue
        line = line.replace("\n", "")
        line = line[:-1]
        line = line.split(" ")
        tmp = {}
        for i in range(len(line)-2):
            tmp[i+1]=float(line[i])
        data.append(tmp)
        result.append(int(line[-2]))
    f.close()

    f = irf.IRF(size)
    length = len(data)/5

    total = 0.0
    t = time.time()
    for i in range(length):
        f.add(str(i), data[i], result[i])
        if i%400 == 399 or i==length-1:
            f.commit()
            total+=time.time()-t
            t = time.time()
    print(total)
    count = 0
    for i in range(10000):
        if int(round(f.classify(data[i+length])))==result[i+length]:
            count+=1
    print float(count)/10000

if 1:
    t = 0
    counter = 0
    ht = irf.IRF(size)
    for i in range(1, 400):
        f = open("../electricity/electricity"+str(i)+".txt", "r")
        data = []
        result = []
        for line in f:
            if line=="\n":
                continue
            tmp = {}
            line = line[:-2] 
            while line[-1]==" ":
                line = line[:-1]
            line = line.split(" ")
            for j in range(len(line)-1):
                tmp[j+1] = float(line[j])
            data.append(tmp)
            result.append(int(int(line[-1])>0))
        f.close()
        t1 = time.time()
        for j in range(len(data)):
            ht.add(str(counter), data[j], result[j])
            counter+=1
        ht.commit()
        t += time.time()-t1
    print t
    
    data = []
    result = []
    for i in range(400, 944):
        f = open("../electricity/electricity"+str(i)+".txt", "r")
        for line in f:
            if line=="\n":
                continue
            tmp = {}
            line = line[:-2]
            while line[-1]==" ":
                line = line[:-1]
            line = line.split(" ")
            for j in range(len(line)-1):
                tmp[j+1] = float(line[j])
            data.append(tmp)
            result.append(int(int(line[-1])>0))
    count = 0
    for i in range(len(data)):
        if int(round(ht.classify(data[i])))==result[i]:
            count+=1
    print float(count)/len(data)

