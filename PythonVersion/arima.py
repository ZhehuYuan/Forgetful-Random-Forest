import statsmodels.api as sm
import random as random
import pandas as pd
import time
'''
# ARIMA
print("ARIMA")
data = [x+random.random() for x in range(20*1000)]
dta = []
for i in range(1,21):
    dta.append(pd.Series(data[:i*1000]))
t1=time.time()
print(t1)
for i in range(20):
    arima = sm.tsa.ARIMA(dta[i],order=(4,0,2)).fit()
    while True:
        try:
            predict_dta = arima.predict(start=1000+i*1000, end=1000+i*1000, dynamic=True)
            break
        except:
            pass
    print(predict_dta)
t2=time.time()
print(t2)
print(t2-t1)

exit()
'''
# Failed ARIMA
data = [x+random.random() for x in range(1000*1000)]
dta = pd.Series(data[:10])
arima = sm.tsa.ARIMA(dta,order=(4,0,2)).fit()
x=arima.params
t1=time.time()
print(t1)
for i in range(10):
    dta=pd.Series(data[:1000+i*1000])
    arima = sm.tsa.ARIMA(dta,order=(4,0,2))
    predict_dta = arima.predict(x)
    print(predict_dta)
t2=time.time()
print(t2)
print(t2-t1)
