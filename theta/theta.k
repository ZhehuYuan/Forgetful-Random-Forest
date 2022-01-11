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
power:{[x;y]$[y<1;1;$[((_(y%2))*2)=y;(sqr (power[x;y%2]));x*(sqr (power[x;(y-1)%2]))]]}
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

