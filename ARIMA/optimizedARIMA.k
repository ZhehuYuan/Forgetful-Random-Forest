`
p:5
q:2
phi:p?1.
theta:q?1.
"p q phi theta"
p
q
phi
theta
l:()
e:()

`
L1:10?20
L2:10?20
"L1 L2"
L1
L2

`
"Optimized Moving"
phi1:()
phi1:phi1, (phi[1]+theta[0])
phi1:phi1, (phi[2]-(phi[1]*theta[0]))
phi1:phi1, (phi[3]-(phi[2]*theta[0]))
phi1:phi1, (phi[4]-(phi[3]*theta[0]))
phi1:phi1, (0.-phi[4]*theta[0])
a1:(1-theta[0])*phi[0]

phi2:()
phi2:phi2, phi[1]
phi2:phi2, (phi[2]+theta[1])
phi2:phi2, (phi[3]-theta[1]*phi[1])
phi2:phi2, (phi[4]-theta[1]*phi[2])
phi2:phi2, (0.-theta[1]*phi[3])
phi2:phi2, (0.-theta[1]*phi[4])
a2:(1-theta[1])*phi[0]

theta1:()
theta1:theta1, (theta[1]-(theta[0]*theta[0]))
theta1:theta1, (0.-(theta[1]*theta[0]))

theta2:()
theta2:theta2, theta[0]
theta2:theta2, 0
theta2:theta2, (0.-(theta[1]*theta[0]))
theta2:theta2, (0.-(theta[1]*theta[1]))


l:l,L1
e:e, (l[0] - phi[0])
e:e, (l[1] - (phi[0] + (phi[1]*l[0]) + (theta[0]*e[0])))
e:e, (l[2] - (phi[0] + (sum (phi[1,2]*l[1,0])) + (sum (theta[0,1]*e[1,0]))))
e:e, (l[3] - (phi[0] + (sum (phi[1,2,3]*l[2,1,0])) + (sum (theta[0,1]*e[2,1]))))
tmp:4
e:e, 0.
tmp:5
e:e, (l[tmp] - (a1 + (sum (phi1*l[tmp-(!p)+1])) + (sum (theta1*e[tmp-(!q)+2]))))
tmp:6
e:e, (l[tmp] - (a2 + (sum (phi2*l[tmp-(!(p+1))+1])) + (sum (theta2*e[tmp-(!(q+2))+1]))))
tmp:7
e:e, 0.
tmp:8
e:e, (l[tmp] - (a1 + (sum (phi1*l[tmp-(!p)+1])) + (sum (theta1*e[tmp-(!q)+2]))))
tmp:9
e:e, (l[tmp] - (a2 + (sum (phi2*l[tmp-(!(p+1))+1])) + (sum (theta2*e[tmp-(!(q+2))+1]))))

predict:(phi(0)) + (sum ({[x](phi(x+1)) * (l(((#l)-1)-x))}[!(p-1)])) + (sum ({[x](theta(x)) * (e(((#e)-1)-x))}[!q]))
predict

`
l:l[(9+3-p)+(!p-2)],L2
tmpL:L2
e:e[(9+3-p)+(!p-2)], (tmpL[0]-predict)
tmp:4
e:e,0.
tmp:5
e:e, (l[tmp] - (a1 + (sum (phi1*l[tmp-(!p)+1])) + (sum (theta1*e[tmp-(!q)+2]))))
tmp:6
e:e, (l[tmp] - (a2 + (sum (phi2*l[tmp-(!(p+1))+1])) + (sum (theta2*e[tmp-(!(q+2))+1]))))
tmp:7
e:e,0.
tmp:8
e:e, (l[tmp] - (a1 + (sum (phi1*l[tmp-(!p)+1])) + (sum (theta1*e[tmp-(!q)+2]))))
tmp:9
e:e, (l[tmp] - (a2 + (sum (phi2*l[tmp-(!(p+1))+1])) + (sum (theta2*e[tmp-(!(q+2))+1]))))
tmp:10
e:e,0.
tmp:11
e:e, (l[tmp] - (a1 + (sum (phi1*l[tmp-(!p)+1])) + (sum (theta1*e[tmp-(!q)+2]))))
tmp:12
e:e, (l[tmp] - (a2 + (sum (phi2*l[tmp-(!(p+1))+1])) + (sum (theta2*e[tmp-(!(q+2))+1]))))

e
predict:(phi(0)) + (sum ({[x](phi(x+1)) * (l(((#l)-1)-x))}[!(p-1)])) + (sum ({[x](theta(x)) * (e(((#e)-1)-x))}[!q]))
predict


