l:()
s:()
c:()
av:()
len:0

"L1"
L1:1, 3, 5, 7
L1
"L2"
L2:2, 4, 6, 8
L2


"moving aggregates with period=4"

`
"add a new list L1"
L:L1
l:l,L
tmp1:(1+len+(!#L))
c:c,tmp1
L[0]:L[0]+$[len<1;0;s[len-1]]
tmp2:+\L
s:s,tmp2
av:av,tmp2%tmp1
len:len+#L
"list"
l
"count"
c
"sum"
s
"average"
av

`
"add a new list L2"
L:L2
l:l,L
tmp1:(1+len+(!#L))&({4}L)
c:c,tmp1
L[0]:L[0]+$[len<1;0;s[len-1]]
tmp2:+\L
s2:s,tmp2
tmp2:{[x](tmp2(x))-(s2(len+x-4))}[!#tmp2]
tmp2
s:s,tmp2
av:av,tmp2%tmp1
len:len+#L
"list"
l
"count"
c
"sum"
s
"average"
av
