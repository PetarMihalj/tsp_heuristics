class AlgorithmType:
    CHRISTOFIDES = "christofides"
    MST = "mst"
    MST_BF = "mstBF"
    CLOSEST_NEIGHBOUR = "closestNeighbour"
    CLOSEST_NEIGHBOUR_BF = "closestNeighbourBF"
    MULTIPLE_FRAGMENTS = "multipleFragments"

class Result:
    def __init__(self, json):
        self.algorithmName=json["algorithmName"]
        self.cycleCost=json["cycleCost"]
        self.cycle=json["cycle"]
        self.counters=json["counters"]
        self.timeMS=json["counters"]["timeMS"]

class Problem:
    def __init__(self, problemName, points):
        self.problemName=problemName
        self.points=points

def callAlgorithm(algorithmType, points):
    import os
    IN_FILE = open("inputFile.txt", "w")
    IN_FILE.write(algorithmType+"\n")
    IN_FILE.write(str(len(points))+"\n")
    for point in points:
        IN_FILE.write(str(point[0])+" "+str(point[1])+"\n")
    IN_FILE.close()
    os.system(r".\\HamCycleCallable.exe")
    
    import json
    OUT_FILE = open("outputFile.txt","r")
    jsonText=OUT_FILE.readline()
    json=json.loads(jsonText)
    return Result(json)
    
