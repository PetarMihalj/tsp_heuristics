from algoInterface import *
import matplotlib.pyplot as plt
import numpy as np
from dimacs import getProblemsFromFolder
from dimacs import impResults

D = impResults("../dimacs_res.txt")

algorithmList=[AlgorithmType.CLOSEST_NEIGHBOUR,AlgorithmType.MULTIPLE_FRAGMENTS,
                AlgorithmType.MST,AlgorithmType.CHRISTOFIDES]
attributeList=["timeMS","cycleCost"]

problems=getProblemsFromFolder("../dimacs_inst/")
testCaseNames = map(lambda x:x.problemName,problems)
testCases = map(lambda x:x.points,problems)

print("Started parsing {} problems.".format(len(problems)))

for i in range(len(problems)):
    resultList=[]
    for a in range(len(algorithmList)):
        resultList.append(callAlgorithm(algorithmList[a],problems[i].points))
        #print ("Called algorithm {} on test {}".format(algorithmList[a],problems[i].problemName))
    resultList.sort(key=lambda x:x.cycleCost)
    #testCaseName rezultatMog najboljiAlgoritamMog rezultatNjihov odstupanje
    print("{} & {} & {} & {} & {} \\\\\n\\hline".format(
        problems[i].problemName, resultList[0].cycleCost, resultList[0].algorithmName, 
        D[problems[i].problemName], round(resultList[0].cycleCost/float(D[problems[i].problemName])-1,2)
    ))

