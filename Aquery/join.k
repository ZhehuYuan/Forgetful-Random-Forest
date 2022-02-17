A:(1 0;2 3)
B:(1 1;1 2;1 3;3 4)

"A"
A:+`a`b!+A
A
`
"B"
B:+`a`b!+B
B
`
"Join:"
findSingle:{[k;l]f:l[0];l:l[1];k:k[0];l:k,l;tmp1:@[l;!#l;f;(#l)?,k];tmp1:(tmp1*(!#l))-1;(,0-1)_tmp1}
findAll:{[p1;p2;f]p1:(f;p1);p2:+(p2;!#p2);tmp1:@[p2;!#p2;findSingle;(#p2)?(,p1)];tmp1}

"Inner Join: select A.a A.b B.b from A,B where B.a=A.a"
InnerJoin:{[row1;row2;cond;v1;v2]	row:(row1;row2);	rows:(#v2)?,row;	rows:+((,!#v2),+rows);	s:findAll[v1;v2;cond];	ret:@[s;!#v2;{[p1;p2]i1:p1;	i2:p2[0];	row1:p2[1];	row2:p2[2]; tmp1:(#i1)?,row2[i2];	tmp2:row1[i1];	+(+tmp1),+tmp2};rows];,/ret}

+`a`Ab`Bb!+InnerJoin[(+(,B[`b]));(+A[`a`b]);=;B[`a];A[`a]]

"Theta Inner Join: select A.a A.b B.b from A,B where B.a<=A.a"
le:{[a;b]~a>b}
+`a`Ab`Bb!+InnerJoin[(+(,B[`b]));(+A[`a`b]);le;B[`a];A[`a]]
