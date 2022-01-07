`
"L n1 m1 n2 m2 n3 m3"
L:20?20
n1:2
m1:12
n2:3
m2:3
n3:2
m3:12

L
n1
m1

`
"One round of X-11, this can be done over and over again. Usually 3 round is done."
mySum:{[x]$[(#x)<1;0;x[(#x)-1]+(mySum[x[!((#x)-1)]])]}
MA:{[a;x;y;l]$[x<0;();(mySum l[(a-x)+!y]), MA[a;x-1;y;l]]}
"SI"
L1:MA[(#L)-m1;(#L)-m1;m1;L]
L2:(MA[(#L1)-n1;(#L1)-n1;n1;L1])%(n1*m1)
x:m1+n1-2
C:((_(x%2))?1), L2, ((_((x+1)%2))?1)
SI:L-C
SI
"S"
L1:MA[(#SI)-m2;(#SI)-m2;m2;SI]
L2:MA[(#L1)-n2;(#L1)-n2;n2;L1]%(m2*n2)
x:m2+n2-2
S:((_(x%2))?1), L2, ((_((x+1)%2))?1)
S
"Se"
L1:MA[(#S)-m3;(#S)-m3;m3;S]
L2:MA[(#L1)-n3;(#L1)-n3;n3;L1]%(m3*n3)
x:m3+n3-2
S2:((_(x%2))?1), L2, ((_((x+1)%2))?1)
Se:S-S2
Se
"SA"
SA:L-Se
SA
