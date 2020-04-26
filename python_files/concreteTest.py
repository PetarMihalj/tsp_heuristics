import algoInterface
import bruteforceAlgo
vertices=[(-2,2), (5,2.5), (2,-3.5), (-3, -3),  (-0.5,-2)]

for algoType in [algoInterface.AlgorithmType.CLOSEST_NEIGHBOUR,
                algoInterface.AlgorithmType.MULTIPLE_FRAGMENTS,
                algoInterface.AlgorithmType.MST,
                algoInterface.AlgorithmType.CHRISTOFIDES]:
    res=algoInterface.callAlgorithm(algoType,vertices)
    print(res.__dict__)

print("BF:")
bruteforceAlgo.run(vertices)