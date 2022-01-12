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
