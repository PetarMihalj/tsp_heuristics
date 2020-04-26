from algoInterface import *
import matplotlib.pyplot as plt
import numpy as np

SAMPLE_SIZE=10
x = np.linspace(10, 10000, 10)

algorithmList=[AlgorithmType.MST,AlgorithmType.CHRISTOFIDES,AlgorithmType.CLOSEST_NEIGHBOUR,AlgorithmType.MULTIPLE_FRAGMENTS]
attributeList=["timeMS","cycleCost"]

testCases = [[np.random.uniform(low=0,high=100,size=(int(s),2)) for t in range(SAMPLE_SIZE)] for s in x]

resultList = [[[callAlgorithm(algorithm,sample) for sample in s] for s in testCases] for algorithm in algorithmList]

for atribute in attributeList:
    fig, ax = plt.subplots()
    for i in range(len(algorithmList)):
        avg = [np.average([getattr(inst,atribute) for inst in result]) for result in resultList[i]]
        ax.plot(x, avg, label=atribute+"_"+algorithmList[i])
        ax.legend()

plt.show()