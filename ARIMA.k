`
p:5
q:2
phi:(p+1)?1.
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
Le1:10?2.
L2:3?20
Le2:3?2.
"L1 Le1 L2 Le2"
L1
Le1
L2
Le2

`
"Add L1, then predict"
l:l,L1
e:e,Le1
predict:(phi(0)) + (sum ({[x](phi(x+1)) * (l(((#l)-1)-x))}[!p])) - (sum ({[x](theta(x)) * (e(((#e)-1)-x))}[!q]))
predict

`
"Add L2, then predict"
l:l,L2
e:e,Le2
predict:(phi(0)) + (sum ({[x](phi(x+1)) * (l(((#l)-1)-x))}[!p])) - (sum ({[x](theta(x)) * (e(((#e)-1)-x))}[!q]))
predict

