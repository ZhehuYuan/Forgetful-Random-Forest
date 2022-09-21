import sklearn
import numpy as np
import random
from sklearn.tree import DecisionTreeClassifier as DTC
from sklearn import tree

import time

def train(data, result, m=8):
    dt = DTC(max_depth=m)
    dt.fit(data, result)
    return dt

def Phi():
    X = []
    y = []
    f = open("../phishing/phishing")
    for i in range(11055):
        l = f.readline()
        a = l.split(" ")
        a = [float(i) for i in a]
        X.append(a[:-1])
        y.append(int(a[-1]))
    before = time.time()
    dt = train(X[:1000], y[:1000])
    print(time.time()-before)
    
    TF = 0
    T = 0
    data = X[1000:]
    result = y[1000:]
    x = dt.predict(data)
    for j in range(len(x)):
        if x[j]==result[j]:
            T+=1
    TF+=len(x)
    print(T/TF)

def Elec():
    X = []
    y = []
    for i in range(1, 400):
        f = open("../electricity/electricity"+str(i)+".txt", "r")
        data = []
        result = []
        for line in f:
            if line=="\n":
                continue
            data.append([])
            line = line.replace("\n", "")
            line = line[:-1]
            line = line.split(" ")
            for i in range(len(line)-1):
                data[-1].append(float(line[i]))
            result.append(int(int(line[-1])==0))
        f.close()
        X.extend(data)
        y.extend(result)
    before = time.time()
    dt = train(X[:3469], y[:3469])
    print(str(time.time()-before))

    T = 0
    TF = 0
    data = X[3469:]
    result = y[3469:]
    x = dt.predict(data)
    for j in range(len(x)):
        if x[j]==result[j]:
            T+=1
    TF+=len(x)
    for i in range(400, 944):
        f = open("../electricity/electricity"+str(i)+".txt", "r")
        data = []
        result = []
        for line in f:
            if line=="\n":
                continue
            data.append([])
            line = line.replace("\n", "")
            if line[-1]==" ":
                line = line[:-1]
            line = line.split(" ")
            for i in range(len(line)-1):
                data[-1].append(float(line[i]))
            result.append(int(int(line[-1])==0))
        f.close()
        
        x = dt.predict(data)
        for j in range(len(x)):
            if x[j]==result[j]:
                T+=1
        TF+=len(x)
    print(str(T/TF))
 

def M5():
    X = []
    y = []
    for i in range(0, 98):
        f = open("../M5/day_"+str(i), "r")
        data = []
        result = []
        for line in f:
            if line=="\n":
                continue
            data.append([])
            line = line.replace("\n", "")
            line = line.split(" ")
            for i in range(len(line)-1):
                data[-1].append(float(line[i]))
            result.append(int(int(line[-1])==0))
        f.close()
        #before = time.time()
        X.extend(data)
        y.extend(result)
    before = time.time()
    dt = train(X[:146062], y[:146062])
    print(str(time.time()-before))

    T = 0
    TF = 0
    data = X[146062:]
    result = y[146062:]
    x = dt.predict(data)
    for j in range(len(x)):
        if x[j]==result[j]:
            T+=1
    TF+=len(x)
    for i in range(98, 133):
        f = open("../M5/day_"+str(i), "r")
        data = []
        result = []
        for line in f:
            if line=="\n":
                continue
            data.append([])
            line = line.replace("\n", "")
            #line = line[:-1]
            line = line.split(" ")
            for i in range(len(line)-1):
                data[-1].append(float(line[i]))
            result.append(int(int(line[-1])==0))
        f.close()
        
        x = dt.predict(data)
        for j in range(len(x)):
            if x[j]==result[j]:
                T+=1
        TF+=len(x)
    print(str(T/TF))
    
lastX = 0

def KDD():
    f = open("../KDD/KDDTrain+.txt", "r")
    X, y = [], []
    for i in range(int(125973/5)+10000):
        l = f.readline()[:-2]
        a = l.split(" ")
        a = [float(i) for i in a]
        X.append(a[:-1])
        y.append(int(a[-1]))
    
    data = []
    result = []
    aaa = int(125973/5)

    if(1):
        t = time.time()
        dt = train(X[:3999], y[:3999])
        print(time.time()-t)
    else:
        for i in range(int(aaa/400)):
            before = time.time()
            data.extend(X[i*400:min(i*400+400, aaa)])
            result.extend(y[i*400:min(i*400+400, aaa)])
            dt = train(np.array(data), np.array(result))
            after = time.time()
            print(after-before)

    #dt = train(np.array(data), np.array(result))
   
    xx = dt.predict(X[3999: aaa+10000])
    y = y[3999:aaa+10000]
    yy = 0
    for i in range(10000+aaa-3999):
        if xx[i] == y[i]:
            yy+=1
    print(yy/(10000+aaa-3999))

x = [3]
if 0 in x:
    print("KDD:")
    KDD()
    KDD()
    KDD()
    KDD()
    KDD()
    KDD()
if 1 in x:
    print("M5:")
    M5()
    M5()
    M5()
    M5()
    M5()
    M5()
if 2 in x:
    print("Elec:")
    Elec()
    Elec()
    Elec()
    Elec()
    Elec()
    Elec()
if 3 in x:
    print("phishing:")
    Phi()
    Phi()
    Phi()
    Phi()
    Phi()
    Phi()
