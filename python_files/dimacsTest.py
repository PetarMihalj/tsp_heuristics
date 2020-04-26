from algoInterface import *
import matplotlib.pyplot as plt
import numpy as np
from dimacs import getProblemsFromFolder


algorithmList=[AlgorithmType.MST,AlgorithmType.CHRISTOFIDES,AlgorithmType.CLOSEST_NEIGHBOUR,AlgorithmType.MULTIPLE_FRAGMENTS]
attributeList=["timeMS","cycleCost"]

problems=getProblemsFromFolder("../dimacs_inst/")
testCaseNames = map(lambda x:x.problemName,problems)
testCases = map(lambda x:x.points,problems)

print("Started parsing {} problems.".format(len(problems)))

for i in range(len(problems)):
    fig, axs = plt.subplots(1, 2, figsize=(10, 5), sharey=False)
    fig.suptitle(testCaseNames[i])
    resultList=[]
    for a in range(len(algorithmList)):
        resultList.append(callAlgorithm(algorithmList[a],problems[i].points))
        print ("Called algorithm {} on test {}".format(algorithmList[a],problems[i].problemName))

    for atrI in range(len(attributeList)):
        for a in range(len(algorithmList)):
            axs[atrI].bar(algorithmList[a], getattr(resultList[a],attributeList[atrI]))
            axs[atrI].set_title(attributeList[atrI])
    fig.autofmt_xdate()
    fig.savefig("../dimacs_graphs/"+testCaseNames[i])
