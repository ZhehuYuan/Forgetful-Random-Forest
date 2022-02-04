aaa: ((1 2 3 1 2 3);(4 5 6 6 6 6))

groupBy:{[x]groupBySingle:{[a;x]findAll:{[c;xx]f:{[i;c]$[(c[0])[i]~c[1];i+1;0]};@[!#xx;!#xx;f;(#xx)#,(xx;c)]};z:findAll[a;x];b:(findAll[0;z]_(!(1+#z)))-1;(a;b)};x:+x;y:?x;@[y;!#y;groupBySingle;(#y)#,x]}
groupBy[aaa]
