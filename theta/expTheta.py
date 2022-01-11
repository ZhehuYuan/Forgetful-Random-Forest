def loop(s1, up, lower, s2):
    x = ""
    for i in range(lower, up+1):
        x+=s1+str(i)+s2
    return x


with open("kExp.k", "w") as f:
    f.write("\"alpha beta h L1 L2\"\nalpha:0.1\nbeta:0.5\nh:3\nalpha\nbeta\nh\n\n")
    for i in range(1,1001):
        f.write("L"+str(i)+":1000?20\n")
    f.write("\n.z.t\n\n")
    f.write("l:()\nm:0\nnewL:()\nh1:beta*(h-1)\na1:beta%alpha\nax:a1\npower:{[x;y]$[y<1;1;$[((_(y%2))*2)=y;(sqr (power[x;y%2]));x*(sqr (power[x;(y-1)%2]))]]}\nSES2:{[i](power[(1-alpha);i])*(newL[(((#newL)-i)-1)])}\nl:l,L1\nnewL:L1\nm:l[0] /only appears on first time\nan:(power[(1-alpha); (#newL)])\ntmp:0\n")
    for i in range(10):
        j = i*100+99
        f.write("tmp:tmp+"+loop("SES2[", j-1, i*100, "]+") + "SES2[" + str(j) + "]\n")
    f.write("ax:ax*an\nm:(alpha*(tmp))+(an*m)\n")
    f.write("predict:((m + h1 + a1) - ax)\n\n")
    
    for i in range(2,1001):
        f.write("l:l,L"+str(i)+"\nnewL:L"+str(i)+"\nan:(power[(1-alpha); (#newL)])\ntmp:0\n")
        for i in range(10):
            j = i*100+99
            f.write("tmp:tmp+"+loop("SES2[", j-1, i*100, "]+") + "SES2[" + str(j) + "]\n")
        f.write("ax:ax*an\nm:(alpha*(tmp))+(an*m)\n")
        f.write("predict:((m + h1 + a1) - ax)\n\n")
    f.write(".z.t\n\n")
