from algoInterface import *
import matplotlib.pyplot as plt
import numpy as np

n=100
size=100

algorithmList=[AlgorithmType.MST,AlgorithmType.CHRISTOFIDES,AlgorithmType.CLOSEST_NEIGHBOUR,AlgorithmType.MULTIPLE_FRAGMENTS]
attributeList=["timeMS","cycleCost"]

testCases = [np.random.uniform(low=0,high=100,size=(int(size),2)) for i in range(n)]

resultList = [[callAlgorithm(algorithm,t) for t in testCases] for algorithm in algorithmList]

perf=[0,0,0,0]

for i in range(len(testCases)):
    mini=-1
    minVal=100000000000000000
    for a in range(len(algorithmList)):
        if (resultList[a][i].cycleCost<minVal):
            minVal=resultList[a][i].cycleCost
            mini=a
    perf[mini]+=1


y_pos = np.arange(len(algorithmList))
plt.bar(y_pos, perf, align='center', alpha=0.5)
plt.xticks(y_pos, algorithmList)
plt.ylabel('Broj pobjeda')
plt.title('Algoritam')

plt.show()