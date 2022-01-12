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
p:()
p:p,1.
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p2:|p
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
an:(1-alpha)*p2[0]
ax:ax*an
m:(alpha*(sum (p2*newL)))+(an*m)
predict:((m + h1 + a1) - ax)
predict
`
"Add L2"
l:l,L2
newL:L2
p2:{[x]p[((#newL)-x)-1]}[!#newL]
an:(1-alpha)*p2[0]
ax:ax*an
m:(alpha*(sum (p2*newL)))+(an*m)
predict:(m + h1 + a1) - ax
predict

`
l:()
p:()
p:p,1.
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p2:|p
"Add L1, then forcast"
l:l,L1
predict:(alpha*(sum (p2*l))) + (((1-alpha)*p2[0])*(l[0])) + beta*(((h-1) + (1.%alpha)) - ((power[(1-alpha);#l])%alpha))
predict
`
"Add L2, then forcast"
l:l,L2
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p:p,(p[(#p)-1]*(1-alpha))
p2:|p
predict:(alpha*(sum (p2*l))) + (((1-alpha)*p2[0])*(l[0])) + beta*(((h-1) + (1.%alpha)) - ((power[(1-alpha);#l])%alpha))
predict
