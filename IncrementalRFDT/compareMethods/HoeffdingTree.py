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
        ht = HoeffdingTreeClassifier(max_byte_size=200*1024*1024*1024, leaf_prediction="nba")
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(leaf_prediction="nb", split_confidence=0.0001, max_byte_size=200*1024*1024*1024)
    elif modelID==3:
        ht = iSOUPTreeRegressor(max_byte_size=200*1024*1024*1024, leaf_prediction="adaptive")
    elif modelID==4:
        ht = AdaptiveRandomForestClassifier(100, max_byte_size=200*1024*1024*1024)
    else:
        print("wrong model ID\n")
        exit(0)
    
    if dataId==0:
        f = open("../mixed/mixed_0101_gradual.csv", "r")
    elif dataId==1:
        f = open("../mixed/mixed_0101_abrupto.csv", "r")
    elif dataId==2:
        f = open("../Synthetic/synthetic_50_gradual", "r")
    elif dataId==3:
        f = open("../Synthetic/synthetic_25_gradual", "r")
    elif dataId==4:
        f = open("../Synthetic/synthetic_10_gradual", "r")
    elif dataId==5:
        f = open("../Synthetic/synthetic_50_abrupt", "r")
    elif dataId==6:
        f = open("../Synthetic/synthetic_25_abrupt", "r")
    elif dataId==7:
        f = open("../Synthetic/synthetic_10_abrupt", "r")


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
        if start!=0:
            localT = 0
            localTF = 0
            for i in range(start, end):
                if start >= 10*gap:
                    TF+=1
                localTF+=1
                x = ht.predict(np.array([data[i]]))[0]
                if modelID == 3:
                    x = x.tolist()
                    x=x.index(max(x))
                    if x == result[i].index(max(result[i])):
                        if start >= 10*gap:
                            T+=1
                        localT+=1
                else:
                    if x == result[i]:
                        if start >= 10*gap:
                            T+=1
            #f.write(str(localT/localTF))
            #f.write("\n")
        if(end!=length):
            t1 = time.time()
            if modelID==3:
                ht.partial_fit(np.array(X), np.array(y))
            else:
                ht.partial_fit(np.array(X), np.array(y))
            t+=time.time()-t1
        start = end
    print(("Mix"+str(modelID)+str(dataId), t, T/TF))

def CovType(modelID):
    if modelID==1:
        ht = HoeffdingTreeClassifier(leaf_prediction="nba", max_byte_size=200*1024*1024*1024)
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(leaf_prediction="nb", split_confidence=0.0001, max_byte_size=200*1024*1024*1024)
    elif modelID==3:
        ht = iSOUPTreeRegressor(max_byte_size=200*1024*1024*1024, leaf_prediction="adaptive")
    elif modelID==4:
        ht = AdaptiveRandomForestClassifier(100, max_byte_size=200*1024*1024*1024)
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
        if start!=0:
            localT = 0
            localTF = 0
            for i in range(start, end):
                if start >= 60*gap:
                    TF+=1
                localTF+=1
                x = ht.predict(np.array([data[i]]))[0]
                if modelID == 3:
                    x = x.tolist()
                    x=x.index(max(x))
                    if x == result[i].index(max(result[i])):
                        if start >= 60*gap:
                            T+=1
                        localT+=1
                else:
                    if x == result[i]:
                        if start >= 60*gap:
                            T+=1
                        localT+=1
            #f.write(str(localT/localTF))
            #f.write("\n")
        if(end!=length):
            t1 = time.time()
            if modelID==3:
                ht.partial_fit(np.array(X), np.array(y))
            else:
                ht.partial_fit(np.array(X), np.array(y))
            t+=time.time()-t1
        start = end
    print(("Cov"+str(modelID), t, T/TF))

def Elec(modelID):
    if modelID==1:
        ht = HoeffdingTreeClassifier(leaf_prediction="nb", max_byte_size=200*1024*1024*1024)
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(leaf_prediction="nb", grace_period=300, split_confidence=0.0001, max_byte_size=200*1024*1024*1024)
    elif modelID==3:
        ht = iSOUPTreeRegressor(max_byte_size=200*1024*1024*1024, leaf_prediction="adaptive")
    elif modelID==4:
        ht = AdaptiveRandomForestClassifier(100, max_byte_size=200*1024*1024*1024)
    else:
        print("wrong model ID\n")
        exit(0)
    
    t = 0
    alldata = []
    allresult = []
    sizeTrain = 0
    T = 0
    TF = 0
    for ii in range(1, 944):
        f = open("../electricity/electricity"+str(ii)+".txt", "r")
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
        if ii!=1:
            x = ht.predict(data)
            localT = 0
            localTF = 0
            for j in range(len(x)):
                localTF+=1
                if modelID == 3:
                    if x[j][0]>x[j][1]:
                            aaa = 0
                    else:
                            aaa = 1
                    if aaa == int(result[j][1]>=result[j][0]):
                        if ii>1:
                            T+=1
                        localT+=1
                else:
                    if x[j]==result[j]:
                        if ii>1:
                            T+=1
                        localT+=1
                if ii>1:
                    TF+=1
            #ff.wirte(str(localT/localTF))
            #ff.write("\n")
        if ii!=943:
            t1 = time.time()
            ht.partial_fit(data, result)
            t += time.time()-t1
    print(("Elec"+str(modelID), t, T/TF))

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
        ht = HoeffdingTreeClassifier(leaf_prediction="nba", max_byte_size=200*1024*1024*1024)
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(leaf_prediction="nb", grace_period=300, split_confidence=0.0001, max_byte_size=200*1024*1024*1024)
    elif modelID==3:
        ht = iSOUPTreeRegressor(max_byte_size=200*1024*1024*1024, leaf_prediction="adaptive")
    elif modelID==4:
        ht = AdaptiveRandomForestClassifier(100, max_byte_size=200*1024*1024*1024)
    else:
        print("wrong model ID\n")
        exit(0)


    t = 0.0
    length = 11055
    T = 0
    TF = 0
    start = 0
    gap = 100
    TPos = 0
    FNeg = 0
    FPos = 0
    while start<length:
        end = min(start+gap, length)
        X = data[start:end]
        y = result[start:end]
        if start!=0:
            localT=0
            localTF=0
            for i in range(start, end):
                if start >= 500:
                    TF+=1
                localTF+=1
                x = ht.predict([data[i]])[0]
                if modelID == 3:
                    if x[0]>x[1]:
                        x = 0
                    else:
                        x = 1
                    if result[i][x] > result[i][abs(1-x)]:
                        if start >= 500:
                            T+=1
                            if x==1:
                                TPos += 1
                        localT+=1
                    elif start>=500 and x==1:
                        FPos+=1
                    elif start>=500:
                        FNeg+=1
                else:
                    if x == result[i]:
                        if start >= 500:
                            T+=1
                            if x==1:
                                TPos += 1
                        localT+=1
                    elif start>=500 and x==1:
                        FPos+=1
                    elif start>=500:
                        FNeg+=1
            #f.write(str(localT/localTF))
            #f.write("\n")
        if(end!=length):
            t1 = time.time()
            ht.partial_fit(X, y)
            t+=time.time()-t1
        start = end
    print(("Phi"+str(modelID), t, T/TF, (2*TPos)/(2*TPos+FNeg+FPos), TPos/(TPos+FNeg), TPos/(TPos+FPos)))

if __name__=="__main__":
    dataset = sys.argv[1]
    modelID = int(sys.argv[2])
    if dataset=="Synth":
        Synth(modelID, int(sys.argv[3]))
    elif dataset=="covtype":
        CovType(modelID)
    elif dataset=="phi":
        Phishing(modelID)
    elif dataset=="Elec":
        Elec(modelID)
    else:
        print("wrong dataset\n")
