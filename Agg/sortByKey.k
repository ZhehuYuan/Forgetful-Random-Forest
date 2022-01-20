x:((10?100),101,101;(10?10),9,7;(10?10),0,0)
key:0
key2:1
"x"
x
"key"
key
"key2"
key2

`
"Sort With 1 key"
sortByKey:{[x;key]y:(+^+`b`a!(x[key];!#x[key]))[`a];+((+x)[y])}
sortByKey[x;key]
`
"Sort With 2 key"
sortBy2Key:{[x;key;key2]y:(+^+`c`b`a!(x[key];x[key2];!#x[key]))[`a];+((+x)[y])}
sortBy2Key[x;key;key2]

