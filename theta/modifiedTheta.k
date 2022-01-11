`
"alpha beta h L1 L2"
alpha:0.1
beta:0.5
h:3
alpha
beta
h

L1:10?20
L2:3?20
L1
L2

`
l:()
m:0
newL:()
h1:beta*(h-1)
a1:beta%alpha
ax:a1
power:{[x;y]$[y<1;1;$[((_(y%2))*2)=y;(sqr (power[x;y%2]));x*(sqr (power[x;(y-1)%2]))]]}
SES2:{[i]$[i<0;0;((power[(1-alpha);i])*(newL[(((#newL)-i)-1)]))+SES2[i-1]]}
"Add L1"
l:l,L1
newL:L1
m:l[0] /only appears on first time
an:(power[(1-alpha); (#newL)])
ax:ax*an
m:(alpha*(SES2[(#newL)-1]))+(an*m)
predict:((m + h1 + a1) - ax)
predict
`
"Add L2"
l:l,L2
newL:L2
an:(power[(1-alpha); (#newL)])
ax:ax*an
m:(alpha*(SES2[(#newL)-1]))+(an*m)
predict:(m + h1 + a1) - ax
predict

`
l:()
SES:{[i]$[i<0;0;((power[(1-alpha);i])*(l[(((#l)-i)-1)]))+SES[i-1]]}
"Add L1, then forcast"
l:l,L1
predict:(alpha*(SES[(#l)-1])) + ((power[(1-alpha); (#l)])*(l[0])) + beta*(((h-1) + (1.%alpha)) - ((power[(1-alpha);#l])%alpha))
predict

`
"Add L2, then forcast"
l:l,L2
predict:(alpha*(SES[(#l)-1])) + ((power[(1-alpha); (#l)])*(l[0])) + beta*(((h-1) + (1.%alpha)) - ((power[(1-alpha);#l])%alpha))
predict
