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
    length = 11055

    total = 0.0
    t = time.time()

    T=0
    TF=0
    for i in range(length):
        if(i>=2000 and i%100==0):
            for j in range(i, i+100):
                if int(round(f.classify(data[i+length])))==result[i+length]:
                    T+=1
                TF+=1
        f.add(str(i), data[i], result[i])
        if i%100 == 99 or i==length-1:
            t = time.time()
            f.commit()
            total+=time.time()-t
    print total
    print float(T)/TF

if 1:
    f = open("../covtype/covtype", "r")
    data = []
    result = []
    length = 58101
    j=0
    for line in f:
        if line=="\n" or len(line)<20:
            continue
        j+=1
        line = line.replace("\n", "")
        line = line.split(" ")
        tmp = {}
        for i in range(len(line)-1):
            tmp[i+1]=float(line[i])
        data.append(tmp)
        result.append(int(line[-1]))
        if j==length-1:
            break
    f.close()

    f = irf.IRF(size)
    print length, size

    Tr=1
    TF=1
    total = 0.0
    t = time.time()
    for i in range(length):
        if i>=2000:
            Tr+=int(int(round(f.classify(data[i])))==result[i])
            TF+=1
        if length-size<=length%100:
            continue
        t = time.time()
        f.add(str(i), data[i], result[i])
        if i%100 == 99:
            f.commit()
            print i, total, float(Tr)/TF
        total+=time.time()-t
    print total
    print float(Tr)/TF

if 0:
    t = 0
    counter = 0
    ht = irf.IRF(size)
    Tr = 0
    TF = 0
    for i in range(1, 944):
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
        if i!=943:
            t1 = time.time()
            for j in range(len(data)):
                ht.add(str(counter), data[j], result[j])
                counter+=1
            ht.commit()
            t += time.time()-t1
        if i>20:
            for i in range(len(data)):
                if int(round(ht.classify(data[i])))==result[i]:
                    Tr+=1
                TF+=1
    print t
    print float(Tr)/TF

if 0:
    t = 0
    counter = 0
    ht = irf.IRF(size)
    Tr = 0
    TF = 0
    for i in range(133):
        f = open("../M5/day_"+str(i), "r")
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
        if i!=132:
            t1 = time.time()
            for j in range(len(data)):
                ht.add(str(counter), data[j], result[j])
                counter+=1
            ht.commit()
            t += time.time()-t1
        if i>=20:
            count = 0
            for i in range(len(data)):
                if int(round(ht.classify(data[i])))==result[i]:
                    Tr+=1
            TF+=1
    print t
    print float(Tr)/TF
