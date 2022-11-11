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
    dt = train(X[:251], y[:251])
    print(time.time()-before)
    
    TF = 0
    T = 0
    data = X[2000:]
    result = y[2000:]
    x = dt.predict(data)
    for j in range(len(x)):
        if x[j]==result[j]:
            T+=1
    TF+=len(x)
    print(T/TF)

def Elec():
    X = []
    y = []
    for i in range(1, 21):
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
    dt = train(X[:280], y[:280])
    print(str(time.time()-before))

    T = 0
    TF = 0
    for i in range(21, 944):
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
 

def Cov():
    f = open("../covtype/covtype", "r")
    X, y = [], []
    for i in range(581012):
        l = f.readline()[:-1]
        a = l.split(" ")
        a = [float(i) for i in a]
        X.append(a[:-1])
        y.append(int(a[-1]))
    
    data = []
    result = []
    aaa = 581012

    t = time.time()
    dt = train(X[:1715], y[:1715])
    print(time.time()-t)

    #dt = train(np.array(data), np.array(result))
   
    xx = dt.predict(X[2000:])
    y = y[2000:]
    yy = 0
    for i in range(561011):
        if xx[i] == y[i]:
            yy+=1
    print(yy/(561012))

def Gradual():
    f = open("../mixed/mixed_0101_gradual.csv", "r")
    X, y = [], []
    for i in range(41000):
        l = f.readline()[:-1]
        a = l.split(" ")
        a = [float(i) for i in a]
        X.append(a[:-1])
        y.append(int(a[-1]))
    
    data = []
    result = []

    t = time.time()
    dt = train(X[:762], y[:762])
    print(time.time()-t)

    #dt = train(np.array(data), np.array(result))
   
    xx = dt.predict(X[2000:])
    y = y[2000:]
    yy = 0
    for i in range(39000):
        if xx[i] == y[i]:
            yy+=1
    print(yy/(39000))

def Abrupto():
    f = open("../mixed/mixed_0101_abrupto.csv", "r")
    X, y = [], []
    for i in range(40000):
        l = f.readline()[:-1]
        a = l.split(" ")
        a = [float(i) for i in a]
        X.append(a[:-1])
        y.append(int(a[-1]))
    
    data = []
    result = []

    t = time.time()
    dt = train(X[:267], y[:267])
    print(time.time()-t)

    #dt = train(np.array(data), np.array(result))
   
    xx = dt.predict(X[2000:])
    y = y[2000:]
    yy = 0
    for i in range(38000):
        if xx[i] == y[i]:
            yy+=1
    print(yy/(38000))

x = [0, 1, 2, 3, 4]
if 0 in x:
    print("covtype:")
    Cov()
    Cov()
    Cov()
    Cov()
    Cov()
    Cov()
if 1 in x:
    print("Elec:")
    Elec()
    Elec()
    Elec()
    Elec()
    Elec()
    Elec()
if 2 in x:
    print("phishing:")
    Phi()
    Phi()
    Phi()
    Phi()
    Phi()
    Phi()
if 3 in x:
    print("gradual:")
    Gradual()
    Gradual()
    Gradual()
    Gradual()
    Gradual()
    Gradual()
if 4 in x:
    print("abrupto:")
    Abrupto()
    Abrupto()
    Abrupto()
    Abrupto()
    Abrupto()
    Abrupto()
