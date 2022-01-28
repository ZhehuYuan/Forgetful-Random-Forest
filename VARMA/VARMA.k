`
"Creating A, B, L1, L2, Le1, Le2"
p:5
q:2
m:4
`
"p q m"
p
q
m

randomMatrix:{[x;y;z]$[y<2;();randomMatrix[x;y-1;z]],(,x?z)}
createM:{[x;m]$[x<2;();createM[(x-1);m]],(,(randomMatrix[m;m;(1,0,-1)]))}
"A"
A:createM[p;m]
A
#A
"B"
B:createM[q;m]
B
#B
"L1"
L1:10^(10*m)?20
L1
#L1
"L2"
L2:10^(10*m)?20
L2
#L2

`
l:()
le:()
`
"Algorithm Start"
batchMatrixDot:{[a;b]@[+(@[@[a;!#a;+]*b;!#a;+/]);!#a[0];+/]}
`
"Add L1 and Le1 then predict"
l:l,L1
tmp:0
le:le,0
tmp:1
le:le,(,l[tmp] - (+/((+A[0])*l[0])+le[0]*B[0]))
tmp:2
le:le,(,l[tmp] - batchMatrixDot[A[0,1];l[1,0]] + batchMatrixDot[B;le[1,0]])
tmp:3
le:le,(,l[tmp] - batchMatrixDot[A[0,1,2];l[2,1,0]] + batchMatrixDot[B;le[2,1]])
tmp:4
le:le,(,l[tmp] - batchMatrixDot[A[0,1,2,3];l[3,2,1,0]] + batchMatrixDot[B;le[3,2]])
tmp:5
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:6
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:7
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:8
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:9
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
`
predict:batchMatrixDot[A;l[(#l)-(!p)+1]]+batchMatrixDot[B;le[(#le)-(!q)+1]]
predict
`
"Add L2 and Le2 then predict"
l:l,L2
le:le[(#le)-(!(q-1))+1]
tmp:10
le:le,l[tmp]-predict
tmp:11
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:12
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:13
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:14
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:15
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:16
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:17
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:18
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
tmp:19
le:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])
`
predict:batchMatrixDot[A;l[(#l)-(!p)+1]]+batchMatrixDot[B;le[(#le)-(!q)+1]]
predict
