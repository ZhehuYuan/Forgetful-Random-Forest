
with open("kExp.k", "w+") as f:
    f.write("\"alpha beta h L1 L2\"\nalpha:0.1\nbeta:0.5\nh:3\nalpha\nbeta\nh\n\n")
    for i in range(1,1001):
        f.write("L"+str(i)+":1000?20\n")
    f.write("\n.z.t\n\n")
    f.write("p:()\np:p,1.\n")
    f.write("p:p,(p[(#p)-1]*(1-alpha))\n"*999)
    f.write("p:|p\n")
    f.write("l:()\nm:0\nnewL:()\nh1:beta*(h-1)\na1:beta%alpha\nax:a1\nl:l,L1\nnewL:L1\nm:l[0] /only appears on first time\nan:(1-alpha)*p[0]\ntmp:0\n")
    f.write("ax:ax*an\nm:(alpha*(sum (p*newL)))+(an*m)\n")
    f.write("predict:((m + h1 + a1) - ax)\n\n")
    for i in range(2,1001):
        f.write("l:l,L"+str(i)+"\nnewL:L"+str(i)+"\nan:(1-alpha)*p[0]\ntmp:0\n")
        f.write("ax:ax*an\nm:(alpha*(sum (p*newL)))+(an*m)\n")
        f.write("predict:((m + h1 + a1) - ax)\n\n")
    f.write(".z.t\n\n")
    
    f.write("\"xxxxxxxxxxxxxxxxxxxxxxxxxx\"\n\n")
    
    f.write(".z.t\n\n")
    f.write("l:()\np:()\np:p,1.\n")
    f.write("p:p,(p[(#p)-1]*(1-alpha))\n"*999)
    f.write("p2:|p\n")
    f.write("l:l,L1\npredict:(alpha*(sum (p2*l))) + (((1-alpha)*p2[0])*(l[0])) + beta*(((h-1) + (1.%alpha)) - (((1-alpha)*p2[0])%alpha))\n\n")
    for i in range(2,1001):
        f.write("p:p,(p[(#p)-1]*(1-alpha))\n"*1000)
        f.write("p2:|p\n")
        f.write("l:l,L"+ str(i) + "\npredict:(alpha*(sum (p2*l))) + (((1-alpha)*p2[0])*(l[0])) + beta*(((h-1) + (1.%alpha)) - (((1-alpha)*p2[0])%alpha))\n\n")
    f.write(".z.t\n\n")
