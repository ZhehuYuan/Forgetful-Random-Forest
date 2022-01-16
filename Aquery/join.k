x:(100?10;100?20;100?20)
y:(10?100;10?20;10?20)
"The first row is the matching key"
`
"x"
x
`
"y"
y
`
"x join y, 0 means this column not appears in x"
{[a;b]y[!#y;b],x[(!(#x)-1)+1;a]}[{[a]a?(y[0])}[x[0]];!#y[0]]
