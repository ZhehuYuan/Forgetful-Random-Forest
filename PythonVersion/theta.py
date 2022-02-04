import statsmodels.api as sm
import random as random
import pandas as pd
import time
from statsmodels.tsa.forecasting.theta import ThetaModel
# Theta
print("Theta")
data = [x+random.random() for x in range(200*1000)]
dta = []
for i in range(1,201):
    dta.append(pd.Series(data[:i*1000]))
t1=time.time()
print(t1)
for i in range(200):
    theta = ThetaModel(dta[i],period=1).fit()
    predict_dta = theta.forecast(steps=1)
    print(predict_dta)
t2=time.time()
print(t2)
print(t2-t1)

exit()

# Failed Theta
data = [x+random.random() for x in range(1000*1000)]
data = pd.Series(data[:10])
arima = ThetaModel(data,period=1).fit()
x=arima.params
t1=time.time()
print(t1)
for i in range(10):
    dta=pd.Series(data[:1000+i*1000])
    theta = ThetaModel(dta,period=1)
    predict_dta = theta.forecast(steps=1)
    print(predict_dta)
t2=time.time()
print(t2)
print(t2-t1)

