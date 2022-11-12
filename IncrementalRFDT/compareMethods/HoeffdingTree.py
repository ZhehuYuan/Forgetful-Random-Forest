import time
import numpy as np
from skmultiflow.trees import ExtremelyFastDecisionTreeClassifier
from skmultiflow.trees import HoeffdingTreeClassifier
from skmultiflow.trees import HoeffdingAdaptiveTreeClassifier
from skmultiflow.trees import LabelCombinationHoeffdingTreeClassifier
from skmultiflow.trees import iSOUPTreeRegressor
from skmultiflow.trees import StackedSingleTargetHoeffdingTreeRegressor
from skmultiflow.meta import AdaptiveRandomForestClassifier
from skmultiflow.data import RegressionGenerator
import joblib
import sys
from sklearn import svm
from sklearn.linear_model import SGDClassifier as SGDC

def Synth(modelID, dataId):
    if modelID==1:
        ht = HoeffdingTreeClassifier()
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(grace_period=300, split_confidence=0.0001)
    elif modelID==3:
        ht = iSOUPTreeRegressor(tie_threshold=0.5)
    elif modelID==4:
        ht = AdaptiveRandomForestClassifier(20, 3)
    else:
        print("wrong model ID\n")
        exit(0)
    
    if dataId==0:
        f = open("../mixed/mixed_0101_gradual.csv", "r")
    elif dataId==1:
        f = open("../mixed/mixed_0101_abrupto.csv", "r")
    elif dataId==2:
        f = open("../Synthetic/2synthetic_100_gradual", "r")


    data = []
    result = []
    for line in f:
        if line=="\n" or len(line)<20:
            continue
        data.append([])
        line = line.replace("\n", "")
        line = line.split(" ")
        for i in range(len(line)-1):
            data[-1].append(float(line[i]))
        if modelID==3:
            result.append([1.0 if int(float(line[-1]))==i else 0.0 for i in range(2)])
        else:
            result.append(int(float(line[-1])))
    f.close()

    t = 0.0
    length = len(data)
    T = 0
    TF = 0
    start = 0
    gap = 100
    while start<length:
        end = min(start+gap, length)
        X = data[start:end]
        y = result[start:end]
        if start >= 20*gap:
            for i in range(start, end):
                TF+=1
                x = ht.predict(np.array([data[i]]))[0]
                if modelID == 3:
                    x = x.tolist()
                    x=x.index(max(x))
                    if x == result[i].index(max(result[i])):
                        T+=1
                else:
                    if x == result[i]:
                        T+=1
        if(end!=length):
            t1 = time.time()
            if modelID==3:
                ht.partial_fit(np.array(X), np.array(y))
            else:
                ht.partial_fit(np.array(X), np.array(y))
            t+=time.time()-t1
        start = end
    print(t)
    print(T/TF)

def CovType(modelID):
    if modelID==1:
        ht = HoeffdingTreeClassifier()
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(grace_period=300, split_confidence=0.0001)
    elif modelID==3:
        ht = iSOUPTreeRegressor(tie_threshold=0.5)
    elif modelID==4:
        ht = AdaptiveRandomForestClassifier(20, 8)
    else:
        print("wrong model ID\n")
        exit(0)
    
    f = open("../covtype/covtype", "r")
    data = []
    result = []
    for line in f:
        if line=="\n" or len(line)<20:
            continue
        data.append([])
        line = line.replace("\n", "")
        line = line.split(" ")
        for i in range(len(line)-1):
            data[-1].append(float(line[i]))
        if modelID==3:
            result.append([1.0 if int(float(line[-1]))==i else 0.0 for i in range(7)])
        else:
            result.append(int(float(line[-1])))
    f.close()

    t = 0.0
    length = 581012
    T = 0
    TF = 0
    start = 0
    gap = 400
    while start<length:
        end = min(start+gap, length)
        X = data[start:end]
        y = result[start:end]
        if start >= 20*gap:
            for i in range(start, end):
                TF+=1
                x = ht.predict(np.array([data[i]]))[0]
                if modelID == 3:
                    x = x.tolist()
                    x=x.index(max(x))
                    if x == result[i].index(max(result[i])):
                        T+=1
                else:
                    if x == result[i]:
                        T+=1
        if(end!=length):
            t1 = time.time()
            if modelID==3:
                ht.partial_fit(np.array(X), np.array(y))
            else:
                ht.partial_fit(np.array(X), np.array(y))
            t+=time.time()-t1
        start = end
    print(t)
    print(T/TF)

def Elec(modelID):
    if modelID==1:
        ht = HoeffdingTreeClassifier()
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(grace_period=300, split_confidence=0.0001)
    elif modelID==3:
        ht = iSOUPTreeRegressor(tie_threshold=0.5)
    elif modelID==4:
        ht = AdaptiveRandomForestClassifier(20, 3)
    else:
        print("wrong model ID\n")
        exit(0)
    
    t = 0
    alldata = []
    allresult = []
    sizeTrain = 0
    T = 0
    TF = 0
    for j in range(1, 944):
        f = open("../electricity/electricity"+str(j)+".txt", "r")
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
            if modelID==3:
                result.append([0.0 if int(int(line[-1])==0)==i else 1.0 for i in range(2)])
            else:
                result.append(int(int(line[-1])>0))
        f.close()
        if modelID==3:
            data = np.array(data)
            result = np.array(result)
        if j>20:
            x = ht.predict(data)
            for j in range(len(x)):
                if modelID == 3:
                    if x[j][0]>x[j][1]:
                        aaa = 0
                    else:
                        aaa = 1
                    if aaa == int(result[j][1]>=result[j][0]):
                        T+=1
                else:
                    if x[j]==result[j]:
                        T+=1
                TF+=1
        if i!=943:
            t1 = time.time()
            ht.partial_fit(data, result)
            t += time.time()-t1
    print(t)
    print(str(T/TF))


def Phishing(modelID):
    f = open("../phishing/phishing", "r")
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
        if modelID==3:
            result.append([1.0 if int(line[-1])==i else 0.0 for i in range(2)])
        else:
            result.append(int(line[-1]))
    f.close()

    data = np.array(data)
    result = np.array(result)
    record = [[] for x in data[0]]

    if modelID==1:
        ht = HoeffdingTreeClassifier()
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(grace_period=300, split_confidence=0.0001)
    elif modelID==3:
        ht = iSOUPTreeRegressor(tie_threshold=0.5)
    elif modelID==4:
        ht = AdaptiveRandomForestClassifier(20, 7)
    else:
        print("wrong model ID\n")
        exit(0)

    t = 0.0
    length = 11055
    T = 0
    TF = 0
    start = 0
    gap = 100
    while start<length:
        end = min(start+gap, length)
        X = data[start:end]
        y = result[start:end]
        if start >= 2000:
            for i in range(start, end):
                TF+=1
                x = ht.predict([data[i]])[0]
                if modelID == 3:
                    if x[0]>x[1]:
                        x = 0
                    else:
                        x = 1
                    if result[i][x] > result[i][abs(1-x)]:
                        T+=1
                else:
                    if x == result[i]:
                        T+=1
        if(end!=length):
            t1 = time.time()
            ht.partial_fit(X, y)
            t+=time.time()-t1
        start = end
    print(t)
    print(T/TF)

if __name__=="__main__":
    dataset = sys.argv[1]
    modelID = int(sys.argv[2])
    if dataset=="Synth":
        Synth(modelID, int(sys.argv[3]))
    elif dataset=="covtype":
        CovType(modelID)
    elif dataset=="phi":
        Phishing(modelID)
    elif dataset=="M5":
        M5(modelID)
    elif dataset=="Elec":
        Elec(modelID)
    else:
        print("wrong dataset\n")
