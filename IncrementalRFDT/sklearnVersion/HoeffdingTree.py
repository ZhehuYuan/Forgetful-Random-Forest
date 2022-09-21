import time
import numpy as np
from skmultiflow.trees import ExtremelyFastDecisionTreeClassifier
from skmultiflow.trees import HoeffdingTreeClassifier
from skmultiflow.trees import HoeffdingAdaptiveTreeClassifier
from skmultiflow.trees import LabelCombinationHoeffdingTreeClassifier
from skmultiflow.trees import iSOUPTreeRegressor
from skmultiflow.trees import StackedSingleTargetHoeffdingTreeRegressor
from skmultiflow.data import RegressionGenerator
import joblib
import sys
from sklearn import svm
from sklearn.linear_model import SGDClassifier as SGDC

def AWS(modelID):
    if modelID==1:
        ht = HoeffdingTreeClassifier()
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(grace_period=300, split_confidence=0.0001)
    elif modelID==3:
        ht = iSOUPTreeRegressor(tie_threshold=0.5)
    elif modelID==4:
        ht = SGDC(loss='hinge', warm_start=True)
    elif modelID == 5:
        ht = SGDC(loss='hinge', warm_start=False)
    else:
        print("wrong model ID\n")
        exit(0)
    
    t = 0
    alldata = []
    allresult = []
    sizeTrain = 0
    for i in range(950, 470, -1):
        f = open("../AWS/"+str(i), "r")
        if((951-i)%12==1):
            data = []
            result = []
        for line in f:
            if line=="\n":
                continue
            data.append([])
            line = line.replace("\n", "")
            line = line[:-1]
            line = line.split(" ")
            for ii in range(len(line)-1):
                data[-1].append(float(line[ii]))
            if modelID==3:
                result.append([0.0 if int(int(line[-1])==0)==i else 1.0 for i in range(2)])
            else:
                result.append(int(int(line[-1])>0))
        f.close()
        if((951-i)%12 != 0):
            continue
        if modelID==3:
            data = np.array(data)
            result = np.array(result)
        if modelID==5:
            if sizeTrain>0:
                tmp = np.arange(sizeTrain)
                np.random.shuffle(tmp)
                tmp = tmp.tolist()
                tmp = tmp[:int(sizeTrain*0.9)]
                newdata = []
                newresult = []
                for i in tmp:
                    newdata.append(alldata[i])
                    newresult.append(allresult[i])
                alldata = newdata
                allresult = newresult
                sizeTrain = int(sizeTrain*0.9)
            alldata.extend(data)
            allresult.extend(result)
            sizeTrain+=len(data)
        if modelID in [3, 2, 1]:
            t1 = time.time()
            ht.partial_fit(data, result)
            t+=time.time()-t1
        elif modelID == 4:
            X = np.array(data)
            y = np.array(result)
            t1 = time.time()
            if i == 939:
                ht.partial_fit(X, y, classes=[0, 1])
            else:
                ht.partial_fit(X, y)
            t+=time.time()-t1
        elif modelID == 5:
            X = np.array(alldata)
            y = np.array(allresult)
            t1 = time.time()
            ht.fit(X, y)
            t+=time.time()-t1
    print(str(t))

    T = 0
    TF = 0
    for i in range(470, -1, -1):
        f = open("../AWS/"+str(i), "r")
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
            result.append(int(int(line[-1])>0))
        f.close()
        
        if modelID==3:
            data = np.array(data)
        x = ht.predict(data)
        for j in range(len(x)):
            if modelID == 3:
                if x[j][0]>x[j][1]:
                    aaa = 0
                else:
                    aaa = 1
                if aaa==result[j]:
                    T+=1
            else:
                if x[j]==result[j]:
                    T+=1
            TF+=1
    print(str(T/TF)+", "+str(T)+", "+str(TF))

def Elec(modelID):
    if modelID==1:
        ht = HoeffdingTreeClassifier()
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(grace_period=300, split_confidence=0.0001)
    elif modelID==3:
        ht = iSOUPTreeRegressor(tie_threshold=0.5)
    elif modelID==4 or modelID==5:
        ht = svm.SVC()
    else:
        print("wrong model ID\n")
        exit(0)
    
    t = 0
    alldata = []
    allresult = []
    sizeTrain = 0
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
            if modelID==3:
                result.append([0.0 if int(int(line[-1])==0)==i else 1.0 for i in range(2)])
            else:
                result.append(int(int(line[-1])>0))
        f.close()
        if modelID==3:
            data = np.array(data)
            result = np.array(result)
        if modelID==4:
            alldata.extend(data)
            allresult.extend(result)
            sizeTrain+=len(data)
            continue
        if modelID==5:
            if sizeTrain>0:
                tmp = np.arange(sizeTrain)
                np.random.shuffle(tmp)
                tmp = tmp.tolist()
                tmp = tmp[:int(sizeTrain*0.9)]
                newdata = []
                newresult = []
                for i in tmp:
                    newdata.append(alldata[i])
                    newresult.append(allresult[i])
                alldata = newdata
                allresult = newresult
                sizeTrain = int(sizeTrain*0.9)
            alldata.extend(data)
            allresult.extend(result)
            sizeTrain+=len(data)
            continue
        if modelID in [1, 2, 3]:
            t1 = time.time()
            ht.partial_fit(data, result)
            t += time.time()-t1
    if modelID in [4, 5]:
        t1 = time.time()
        ht.fit(alldata, allresult)
        t+=time.time()-t1
    print(t)
    
    T = 0
    TF = 0
    for i in range(400, 944):
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
            result.append(int(int(line[-1])>0))
        f.close()
        
        if modelID==3:
            data = np.array(data)
        x = ht.predict(data)
        for j in range(len(x)):
            if modelID == 3:
                if x[j][0]>x[j][1]:
                    aaa = 0
                else:
                    aaa = 1
                if aaa==result[j]:
                    T+=1
            else:
                if x[j]==result[j]:
                    T+=1
            TF+=1
    print(str(T/TF))

def M5(modelID):
    if modelID==1:
        ht = HoeffdingTreeClassifier()
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(grace_period=300, split_confidence=0.0001)
    elif modelID==3:
        ht = iSOUPTreeRegressor(tie_threshold=0.5)
    elif modelID==4 or modelID==5:
        ht = svm.SVC()
    else:
        print("wrong model ID\n")
        exit(0)
    
    t = 0
    alldata = []
    allresult = []
    sizeTrain = 0
    for i in range(98):
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
            if modelID==3:
                result.append([0.0 if int(int(line[-1])==0)==i else 1.0 for i in range(2)])
            else:
                result.append(int(int(line[-1])>0))
        f.close()
        if modelID==3:
            data = np.array(data)
            result = np.array(result)
        if modelID==4:
            alldata.extend(data)
            allresult.extend(result)
            sizeTrain+=len(data)
            continue
        if modelID==5:
            if sizeTrain>0:
                tmp = np.arange(sizeTrain)
                np.random.shuffle(tmp)
                tmp = tmp.tolist()
                tmp = tmp[:int(sizeTrain*0.9)]
                newdata = []
                newresult = []
                for i in tmp:
                    newdata.append(alldata[i])
                    newresult.append(allresult[i])
                alldata = newdata
                allresult = newresult
                sizeTrain = int(sizeTrain*0.9)
            alldata.extend(data)
            allresult.extend(result)
            sizeTrain+=len(data)
            continue
        if modelID in [1, 2, 3]:
            t1 = time.time()
            ht.partial_fit(data, result)
            t += time.time()-t1
    if modelID in [4,5]:
        t1 = time.time()
        ht.fit(alldata, allresult)
        t += time.time()-t1
    print(t)
    #joblib.dump(ht, 'HoeffdingTree20.pkl')

    #ht = joblib.load('HoeffdingTree60.pkl')
    #print(ht.measure_tree_depth())
    T = 0
    TF = 0
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
            result.append(int(int(line[-1])>0))
        f.close()
        
        if modelID==3:
            data = np.array(data)
        x = ht.predict(data)
        for j in range(len(x)):
            if modelID == 3:
                if x[j][0]>x[j][1]:
                    aaa = 0
                else:
                    aaa = 1
                if aaa==result[j]:
                    T+=1
            else:
                if x[j]==result[j]:
                    T+=1
            TF+=1
    print(str(T/TF)+", "+str(T)+", "+str(TF))
    exit(0)

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
    #for tmp in data:
    #    for i in range(len(record)):
    #        if tmp[i] not in record[i]:
    #            record[i].append(tmp[i])

    length = 8000

    #ht = ExtremelyFastDecisionTreeClassifier()
    #ht = StackedSingleTargetHoeffdingTreeRegressor()
    if modelID==1:
        ht = HoeffdingTreeClassifier()
        #ht = HoeffdingTreeClassifier(grace_period=400)
        #ht = HoeffdingTreeClassifier(tie_threshold=0.1)
        #ht = HoeffdingTreeClassifier(leaf_prediction="mc")
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(grace_period=300, split_confidence=0.0001)
        #ht = HoeffdingAdaptiveTreeClassifier(grace_period=400)
        #ht = HoeffdingAdaptiveTreeClassifier(tie_threshold=0.1)
        #ht = HoeffdingAdaptiveTreeClassifier(leaf_prediction="mc")
    elif modelID==3:
        #ht = iSOUPTreeRegressor()
        #ht = iSOUPTreeRegressor(grace_period=400)
        ht = iSOUPTreeRegressor(tie_threshold=0.5)
    else:
        print("wrong model ID\n")
        exit(0)

    for gap in [100]:
        start = 0
        t1 = time.time()
        while start<length:
            end = min(start+gap, length)
            X = data[start:end]
            y = result[start:end]
            #print(data[start:end])
            #print(result[start:end])
            ht.partial_fit(X, y)
            start = end
    print(str(time.time()-t1))
    #t1=time.time()

    y = 0
    for i in range(3055):
        x = ht.predict([data[end+i]])[0]
        if modelID == 3:
            if x[0]>x[1]:
                x = 0
            else:
                x = 1
            if result[end+i][x] > result[end+i][abs(1-x)]:
                y+=1
        else:
            if x == result[end+i]:
                y+=1
    print(y/3055)

def KDD(modelID):

    f = open("../KDD/KDDTrain+.txt", "r")
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
            result.append([1.0 if int(line[-1])==i else 0.0 for i in range(2)])
        else:
            result.append(int(line[-1]))
    
    f.close()

    data = np.array(data)
    result = np.array(result)
    record = [[] for x in data[0]]
    #for tmp in data:
    #    for i in range(len(record)):
    #        if tmp[i] not in record[i]:
    #            record[i].append(tmp[i])

    length = int(len(data)/5)

    #ht = ExtremelyFastDecisionTreeClassifier()
    #ht = StackedSingleTargetHoeffdingTreeRegressor()
    if modelID==1:
        ht = HoeffdingTreeClassifier()
        #ht = HoeffdingTreeClassifier(grace_period=400)
        #ht = HoeffdingTreeClassifier(tie_threshold=0.1)
        #ht = HoeffdingTreeClassifier(leaf_prediction="mc")
    elif modelID==2:
        ht = HoeffdingAdaptiveTreeClassifier(grace_period=300, split_confidence=0.0001)
        #ht = HoeffdingAdaptiveTreeClassifier(grace_period=400)
        #ht = HoeffdingAdaptiveTreeClassifier(tie_threshold=0.1)
        #ht = HoeffdingAdaptiveTreeClassifier(leaf_prediction="mc")
    elif modelID==3:
        #ht = iSOUPTreeRegressor()
        #ht = iSOUPTreeRegressor(grace_period=400)
        ht = iSOUPTreeRegressor(tie_threshold=0.5)
    else:
        print("wrong model ID\n")
        exit(0)

    for gap in [400]:
        start = 0
        t1 = time.time()
        while start<length:
            end = min(start+gap, length)
            X = data[start:end]
            y = result[start:end]
            #print(data[start:end])
            #print(result[start:end])
            ht.partial_fit(X, y)
            start = end
    print(str(time.time()-t1))
    #t1=time.time()

    y = 0
    for i in range(10000):
        x = ht.predict([data[end+i]])[0]
        if modelID == 3:
            if x[0]>x[1]:
                x = 0
            else:
                x = 1
            if result[end+i][x] > result[end+i][abs(1-x)]:
                y+=1
        else:
            if x == result[end+i]:
                y+=1
    print(y/10000)

if __name__=="__main__":
    dataset = sys.argv[1]
    modelID = int(sys.argv[2])
    if dataset=="KDD":
        KDD(modelID)
    elif dataset=="phi":
        Phishing(modelID)
    elif dataset=="M5":
        M5(modelID)
    elif dataset=="Elec":
        Elec(modelID)
    elif dataset=="AWS":
        AWS(modelID)
    else:
        print("wrong dataset\n")
