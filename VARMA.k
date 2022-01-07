`
"Creating A, B, L1, L2, Le1, Le2"
p:5
q:2
m:4

randomMatrix:{[x;y;z](x?z),$[y<2;();randomMatrix[x;y-1;z]]}

createA:{[x](m^randomMatrix[m;m;2]),$[x<2;();createA[x-1]]}
createB:{[x](m^randomMatrix[m;m;2]),$[x<2;();createB[x-1]]}
`
A:createA[p]
A
#A
`
B:createB[q]
B

y:(1,3,5,7)
`
L1:10^((10*m)?20)
L1
`
L2:3^((3*m)?20)
L2
`
Le1:10^((10*m)?((!5)-2))
Le1
`
Le2:3^((3*m)?((!5)-2))
Le2

`
l:()
le:()
`
"Add L1 and Le1 then predict"
l:l,L1
le:le,Le1

mySum:{[x](x[0])+$[(#x)<2;0;mySum[x[(1+!((#x)-1))]]]}

f1:{[x;y](mySum[((l[(#l)-(x+1)])*(A[(x*m)+y]))]),$[x<2;();f1[x-1;y]]}
g1:{[x](mySum[(f1[p;(x-1)])]), $[x<2;();g1[x-1]]}

f2:{[x;y](mySum[((le[(#le)-(x+1)])*(B[(x*m)+y]))]),$[x<2;();f2[x-1;y]]}
g2:{[x](mySum[(f2[q;(x-1)])]), $[x<2;();g2[x-1]]}

predict:g2[m]+g1[m]
predict
`
"Add L2 and Le2 then predict"
l:l,L2
le:le,Le2

mySum:{[x](x[0])+$[(#x)<2;0;mySum[x[(1+!((#x)-1))]]]}

f1:{[x;y](mySum[((l[(#l)-(x+1)])*(A[(x*m)+y]))]),$[x<2;();f1[x-1;y]]}
g1:{[x](mySum[(f1[p;(x-1)])]), $[x<2;();g1[x-1]]}

f2:{[x;y](mySum[((le[(#le)-(x+1)])*(B[(x*m)+y]))]),$[x<2;();f2[x-1;y]]}
g2:{[x](mySum[(f2[q;(x-1)])]), $[x<2;();g2[x-1]]}

predict:g2[m]+g1[m]
predict
