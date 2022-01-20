x:(10?100;10?10;10?10)
key:0
"x"
x
"key"
key

`
"Sort Start"
sortByKey:{[x;key]y:(+^+`b`a!(x[key];!#x[key]))[`a];+((+x)[y])}
sortByKey[x;key]
