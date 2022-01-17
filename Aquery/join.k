x:(2,2,(8?10),2,2;12?20;12?20)
y:(2,2,8?100;10?20;10?20)
"The first row is the matching key"
`
"x"
x
`
"y"
y

`
"Join with at least 1 'key'"
join:{[x;y;xKey;ymatch]a:x[0];x[0]=x[xKey];x[xKey]=a;a:y[0];y[0]=y[ymatch];y[ymatch]=a;a:x[0]?(y[0]);b:!#y[0];y[!#y;b],x[(!(#x)-1)+1;a]}
+`a`b`c`d`e!join[x;y;0;0]
`
"Join with no 'key'"
findAll:{[a;b]noApp:(a_(!(1+#a)))[0];tmp:(b?a);tmp1:(,#b)_tmp;$[(#tmp1)=0;();tmp,findAll[a;@[b;tmp1;noApp]]]}
joinNoKey:{[x;y;xmatch;ymatch]a:x[0];x[0]=x[xmatch];x[xmatch]=a;a:y[0];y[0]=y[ymatch];y[ymatch]=a;a:findAll[x[0];y[0]];b:(!((_(#a)%(#x[0])),#x[0]))[1];c:+(+((#y[0])+(!#x[0])*0;!#x[0]))_(+(a;b));x[!(#x);c[1]],y[(!(#y)-1)+1;c[0]]}
a:joinNoKey[x;y;0;0]
+`a`b`c`d`e!a

