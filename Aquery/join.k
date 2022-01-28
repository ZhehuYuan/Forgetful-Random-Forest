w:(!10;10?20;10?20)
x:(2,2,(8?10),2,2;12?20;12?20)
y:(2,2,8?100;10?20;10?20)
z:(2,2,8?100;10?20;10?20)

"The first row is the matching row"
`
"w: a is key"
+`a`b`c!w
`
"x: a is not key"
+`a`b`c!x
`
"y: a is not key"
+`a`d`e!y
`
"z: a is not key"
+`a`c`d!z
`
"Join x y"
findAll:{[a;b]noApp:(a_(!(1+#a)))[0];tmp:(b?a);tmp1:(,#b)_tmp;$[(#tmp1)=0;();tmp,findAll[a;@[b;tmp1;noApp]]]}
Join:{[x;y;xmatch;ymatch]a:x[0];x[0]=x[xmatch];x[xmatch]=a;a:y[0];y[0]=y[ymatch];y[ymatch]=a;a:findAll[x[0];y[0]];b:(!((_(#a)%(#x[0])),#x[0]))[1];c:+(+((#y[0])+(!#x[0])*0;!#x[0]))_(+(a;b));x[!(#x);c[1]],y[(!(#y)-1)+1;c[0]]}
a:Join[x;y;0;0]
+`a`b`c`d`e!a
`
"Join x z"
a:Join[x;z;0;0]
+`a`b`c`c2`d!a
`
"Join x w"
a:Join[x;w;0;0]
+`a`b`c`b2`c2!a
