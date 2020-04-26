from __future__ import print_function
#vertices=[(-2,2), (0,3), (5,2.5), (2,-3.5), (-3, -3),  (-0.5,-2)]
vertices=[(-2,2), (5,2.5), (2,-3.5), (-3, -3),  (-0.5,-2)]
import math


print("{",end="")

for i in range(len(vertices)):
    if (i<len(vertices)-1):
        print("{}/{}/{}, ".format(vertices[i][0],vertices[i][1],i+1),end="")
    else:
        print("{}/{}/{}".format(vertices[i][0],vertices[i][1],i+1),end="")
print("}")

print("{",end="")
for i in range(len(vertices)):
    for j in range(i+1,len(vertices)):
        if (i<len(vertices)-2):
            print("{}/{}/{}, ".format(i+1,j+1,
                round(math.sqrt(math.pow(vertices[i][0]-vertices[j][0],2)+math.pow(vertices[i][1]-vertices[j][1],2)),2)
            ),end="")
        else:
            print("{}/{}/{}".format(i+1,j+1,
                round(math.sqrt(math.pow(vertices[i][0]-vertices[j][0],2)+math.pow(vertices[i][1]-vertices[j][1],2)),2)
            ),end="")
print("}")
