"L1:"
L1:(1;2;3;5;6;8;9;1;7;3;5;6)
L1
"L2:"
L2:(8;36;9;2;61;85)
L2

`
"moving min:"
movingMin:{[L]L[0],mM[L;1;L[0]]}
mM:{[L;i;x]$[(#L)<(i+2);$[x<L[i];x;L[i]];$[x<L[i];x,mM[L;i+1;x];L[i],mM[L;i+1;L[i]]]]}
minimum:movingMin[L1]
minimum
minimum:movingMin[L2]
minimum

`
"moving max:"
movingMax:{[L]L[0],mMax[L;1;L[0]]}
mMax:{[L;i;x]$[(#L)<(i+2);$[x>L[i];x;L[i]];$[x>L[i];x,mMax[L;i+1;x];L[i],mMax[L;i+1;L[i]]]]}
maximum:movingMax[L1]
maximum
maximum:movingMax[L2]
maximum

`
"moving average"
/comment movingAvg:{[newL]x:(avg newL);(average+(x-average)*(count newL)%(c+count newL); c+count newL)}
movingAvg:{[L](+\L)%(1+!#L)}
movingAvg[L1]
movingAvg[L2]

`
"moving sum"
movingSum:{[L](+\L)}
movingSum[L1]
movingSum[L2]

`
"moving count"
movingCount:{[L]1+!#L}
movingCount[L1]
movingCount[L2]
