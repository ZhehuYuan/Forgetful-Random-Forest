with open("ConstBatchNumber.k", "w+") as f:
    f.write("\nalpha:0.1\nbeta:0.5\nh:3\n\n")
    for i in range(1,11):
        f.write("L"+str(i)+":"+str(i)+"000?20\n")
    for i in range(1, 11):
        f.write("`\n"+str(i*1000)+"\n\n")
        f.write("\nt1:.z.t\n\n")
        f.write("p:()\np:p,1.\n")
        f.write("p:p,(p[(#p)-1]*(1-alpha))\n"*(i*1000-1))
        f.write("p:|p\n")
        f.write("l:()\nm:0\nnewL:()\nh1:beta*(h-1)\na1:beta%alpha\nax:a1\nl:l,L"+str(i)+"\nnewL:L"+str(i)+"\nm:l[0] /only appears on first time\nan:(1-alpha)*p[0]\ntmp:0\n")
        f.write("ax:ax*an\nm:(alpha*(sum (p*newL)))+(an*m)\n")
        f.write("predict:((m + h1 + a1) - ax)\n\n")
        for j in range(2,1000):
            f.write("l:l,L"+str(i)+"\nnewL:L"+str(i)+"\nan:(1-alpha)*p[0]\ntmp:0\n")
            f.write("ax:ax*an\nm:(alpha*(sum (p*newL)))+(an*m)\n")
            f.write("predict:((m + h1 + a1) - ax)\n\n")
        f.write("t2:.z.t\n\n")
        f.write("t2-t1\n")
    
#    f.write("\"xxxxxxxxxxxxxxxxxxxxxxxxxx\"\n\n")
#    
#    f.write(".z.t\n\n")
#    f.write("l:()\np:()\np:p,1.\n")
#    f.write("p:p,(p[(#p)-1]*(1-alpha))\n"*999)
#    f.write("p2:|p\n")
#    f.write("l:l,L1\npredict:(alpha*(sum (p2*l))) + (((1-alpha)*p2[0])*(l[0])) + beta*(((h-1) + (1.%alpha)) - (((1-alpha)*p2[0])%alpha))\n\n")
#    for i in range(2,1001):
#        f.write("p:p,(p[(#p)-1]*(1-alpha))\n"*1000)
#        f.write("p2:|p\n")
#        f.write("l:l,L"+ str(i) + "\npredict:(alpha*(sum (p2*l))) + (((1-alpha)*p2[0])*(l[0])) + beta*(((h-1) + (1.%alpha)) - (((1-alpha)*p2[0])%alpha))\n\n")
#    f.write(".z.t\n\n")
