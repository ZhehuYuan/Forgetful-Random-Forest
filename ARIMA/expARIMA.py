with open("Batch.k", "w+") as f:
    f.write("\np:5\nq:2\nphi:p?1.\ntheta:q?1.\n\n")
    for i in range(1, 11):
        f.write("L"+str(i)+":"+str(i)+"000?20\n")
    for i2 in range(1, 11):
        f.write(str(i2)+"\n")
        k=i2*1000
        f.write("t1:.z.t\n\n")
        f.write("l:()\ne:()\n\n")
        f.write("phi1:()\nphi1:phi1, (phi[1]+theta[0])\nphi1:phi1, (phi[2]-(phi[1]*theta[0]))\nphi1:phi1, (phi[3]-(phi[2]*theta[0]))\nphi1:phi1, (phi[4]-(phi[3]*theta[0]))\nphi1:phi1, (0.-phi[4]*theta[0])\na1:(1-theta[0])*phi[0]\n\n")
        f.write("phi2:()\nphi2:phi2, phi[1]\nphi2:phi2, (phi[2]+theta[1])\nphi2:phi2, (phi[3]-theta[1]*phi[1])\nphi2:phi2, (phi[4]-theta[1]*phi[2])\nphi2:phi2, (0.-theta[1]*phi[3])\nphi2:phi2, (0.-theta[1]*phi[4])\na2:(1-theta[1])*phi[0]\n\n")
        f.write("theta1:()\ntheta1:theta1, (theta[1]-(theta[0]*theta[0]))\ntheta1:theta1, (0.-(theta[1]*theta[0]))\ntheta2:()\ntheta2:theta2, theta[0]\ntheta2:theta2, 0\ntheta2:theta2, (0.-(theta[1]*theta[0]))\ntheta2:theta2, (0.-(theta[1]*theta[1]))\n\n")
        f.write("l:l,L"+str(i2)+"\ne:e, (l[0] - phi[0])\ne:e, (l[1] - (phi[0] + (phi[1]*l[0]) + (theta[0]*e[0])))\ne:e, (l[2] - (phi[0] + (sum (phi[1,2]*l[1,0])) + (sum (theta[0,1]*e[1,0]))))\ne:e, (l[3] - (phi[0] + (sum (phi[1,2,3]*l[2,1,0])) + (sum (theta[0,1]*e[2,1]))))\n\n")
        for j in range(4, k-3, 3):
            f.write("e:e,0.\ntmp:"+str(j+1)+"\ne:e, (l[tmp] - (a1 + (sum (phi1*l[tmp-(!p)+1])) + (sum (theta1*e[tmp-(!q)+2]))))\ntmp:"+str(j+2)+"\ne:e, (l[tmp] - (a2 + (sum (phi2*l[tmp-(!(p+1))+1])) + (sum (theta2*e[tmp-(!(q+2))+1]))))\n")
        j+=3
        while(j<k):
            f.write("tmp:"+str(j)+"\ne:e, (l[tmp] - (phi[0] + (sum (phi[(!(p-1))+1]*l[tmp-(!(p-1))+1])) + (sum (theta[!q]*e[tmp-(!q)+1]))))\n")
            j+=1
        f.write("predict:(phi(0)) + (sum ({[x](phi(x+1)) * (l(((#l)-1)-x))}[!(p-1)])) + (sum ({[x](theta(x)) * (e(((#e)-1)-x))}[!q]))\n\n") 

        for i in range(2,101):
            f.write("l:l[(1000+2-p)+(!p-2)],L"+str(i2)+"\ne:e[("+str(k)+"+2-p)+(!p-2)], (l[p-2]-predict)\n")
            for j in range(4, k, 3):
                f.write("e:e,0.\ntmp:"+str(j+1)+"\ne:e, (l[tmp] - (a1 + (sum (phi1*l[tmp-(!p)+1])) + (sum (theta1*e[tmp-(!q)+2]))))\ntmp:"+str(j+2)+"\ne:e, (l[tmp] - (a2 + (sum (phi2*l[tmp-(!(p+1))+1])) + (sum (theta2*e[tmp-(!(q+2))+1]))))\n")
            j+=3
            while(j<k+3):
                f.write("tmp:"+str(j)+"\ne:e, (l[tmp] - (phi[0] + (sum (phi[(!(p-1))+1]*l[tmp-(!(p-1))+1])) + (sum (theta[!q]*e[tmp-(!q)+1]))))\n")
                j+=1 
            f.write("predict:(phi(0)) + (sum ({[x](phi(x+1)) * (l(((#l)-1)-x))}[!(p-1)])) + (sum ({[x](theta(x)) * (e(((#e)-1)-x))}[!q]))\n\n")
        f.write("t2:.z.t\n\n")
        f.write("t2-t1\n\n")
