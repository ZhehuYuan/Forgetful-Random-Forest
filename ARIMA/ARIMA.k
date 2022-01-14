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
L2:3?20
"L1 L2"
L1
L2

`
"Add L1, then predict"
l:l,L1
e:e, (l[0] - phi[0])
e:e, (l[1] - (phi[0] + (phi[1]*l[0]) + (theta[0]*e[0])))
e:e, (l[2] - (phi[0] + (sum (phi[1,2]*l[1,0])) + (sum (theta[0,1]*e[1,0]))))
e:e, (l[3] - (phi[0] + (sum (phi[1,2,3]*l[2,1,0])) + (sum (theta[0,1]*e[2,1]))))
tmp:4
e:e, (l[tmp] - (phi[0] + (sum (phi[(!(p-1))+1]*l[tmp-(!(p-1))+1])) + (sum (theta[!q]*e[tmp-(!q)+1]))))
tmp:5
e:e, (l[tmp] - (phi[0] + (sum (phi[(!(p-1))+1]*l[tmp-(!(p-1))+1])) + (sum (theta[!q]*e[tmp-(!q)+1]))))
tmp:6
e:e, (l[tmp] - (phi[0] + (sum (phi[(!(p-1))+1]*l[tmp-(!(p-1))+1])) + (sum (theta[!q]*e[tmp-(!q)+1]))))
tmp:7
e:e, (l[tmp] - (phi[0] + (sum (phi[(!(p-1))+1]*l[tmp-(!(p-1))+1])) + (sum (theta[!q]*e[tmp-(!q)+1]))))
tmp:8
e:e, (l[tmp] - (phi[0] + (sum (phi[(!(p-1))+1]*l[tmp-(!(p-1))+1])) + (sum (theta[!q]*e[tmp-(!q)+1]))))
tmp:9
e:e, (l[tmp] - (phi[0] + (sum (phi[(!(p-1))+1]*l[tmp-(!(p-1))+1])) + (sum (theta[!q]*e[tmp-(!q)+1]))))

predict:(phi(0)) + (sum ({[x](phi(x+1)) * (l(((#l)-1)-x))}[!(p-1)])) + (sum ({[x](theta(x)) * (e(((#e)-1)-x))}[!q]))
predict

`
"Add L2, then predict"
l:l,L2
tmp:10
e:e, l[tmp]-predict
tmp:11
e:e, (l[tmp] - (phi[0] + (sum (phi[(!(p-1))+1]*l[tmp-(!(p-1))+1])) + (sum (theta[!q]*e[tmp-(!q)+1]))))
tmp:12
e:e, (l[tmp] - (phi[0] + (sum (phi[(!(p-1))+1]*l[tmp-(!(p-1))+1])) + (sum (theta[!q]*e[tmp-(!q)+1]))))

predict:(phi(0)) + (sum ({[x](phi(x+1)) * (l(((#l)-1)-x))}[!(p-1)])) + (sum ({[x](theta(x)) * (e(((#e)-1)-x))}[!q]))
predict

