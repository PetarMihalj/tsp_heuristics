def run(vertices):
    import itertools
    optPerm=None
    optSize=1000000000

    for perm in itertools.permutations(range(1,len(vertices)+1)):
        if (perm[0]!=1): continue
        c=dist(perm[len(vertices)-1],perm[0],vertices)
        tarStr=""

        for i in range(len(vertices)-1):
            c+=dist(perm[i],perm[i+1],vertices)
            tarStr+=str(round(dist(perm[i],perm[i+1],vertices),2))+" + "
        
        tarStr+=str(round(dist(perm[len(vertices)-1],perm[0],vertices),2))+" = "+str(round(c,2))

        if c<optSize:
            optSize=c
            optPerm=perm


        print("{} & {} \\\\".format(perm,tarStr)) 
    print(optPerm)
    print(optSize)
        
def dist(i,j,vertices):
    i-=1
    j-=1
    import math
    return math.sqrt(math.pow(vertices[i][0]-vertices[j][0],2)+math.pow(vertices[i][1]-vertices[j][1],2))