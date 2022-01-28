with open("constNoBatch.k", "w+") as f:
    for s in range(1,11):
        s*=1000
        Nbatch=100
        f.write("p:5\nq:2\nm:4\n\n")
        f.write("randomMatrix:{[x;y;z]$[y<2;();randomMatrix[x;y-1;z]],(,x?z)}\ncreateM:{[x;m]$[x<2;();createM[(x-1);m]],(,(randomMatrix[m;m;(1,0,-1)]))}\n\n")
        f.write("A:createM[p;m]\nB:createM[q;m]\nL1:10^(10*m)?20\nL2:10^(10*m)?20\n\n")
        for i in range(1, Nbatch+1):
            f.write("L"+str(i)+":"+str(s)+"?20\n")
        f.write("l:()\nle:()\nbatchMatrixDot:{[a;b]@[+(@[@[a;!#a;+]*b;!#a;+/]);!#a[0];+/]}\n\n")
        f.write("t1:.z.t\n\n")
        f.write("l:l,L1\ntmp:0\nle:le,0\ntmp:1\nle:le,(,l[tmp] - (+/((+A[0])*l[0])+le[0]*B[0]))\ntmp:2\nle:le,(,l[tmp] - batchMatrixDot[A[0,1];l[1,0]] + batchMatrixDot[B;le[1,0]])\ntmp:3\nle:le,(,l[tmp] - batchMatrixDot[A[0,1,2];l[2,1,0]] + batchMatrixDot[B;le[2,1]])\ntmp:4\nle:le,(,l[tmp] - batchMatrixDot[A[0,1,2,3];l[3,2,1,0]] + batchMatrixDot[B;le[3,2]])\n\n")
        for i in range(5,s+1):
            f.write("tmp:"+str(i)+"\nle:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])\n")
        f.write("predict:batchMatrixDot[A;l[(#l)-(!p)+1]]+batchMatrixDot[B;le[(#le)-(!q)+1]]\n\n")
        for i in range(2, Nbatch+1):
            f.write("l:l,L"+str(i)+"\nle:le[(#le)-(!(q-1))+1]\ntmp:"+str((i-1)*s+1)+"\nle:le,l[tmp]-predict\n\n")
            for j in range(2, s+1):
                f.write("tmp:"+str((i-1)*s+j)+"\nle:le,(,l[tmp] - batchMatrixDot[A;l[tmp-(!p)+1]] + batchMatrixDot[B;le[(#le)-(!q)+1]])\n")
            f.write("predict:batchMatrixDot[A;l[(#l)-(!p)+1]]+batchMatrixDot[B;le[(#le)-(!q)+1]]\n\n")
        f.write("t2:.z.t\nt2-t1\n")
