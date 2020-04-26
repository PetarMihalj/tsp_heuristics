from algoInterface import Problem

def getProblemsFromFolder(folderPath):
    from os import listdir
    files = listdir(folderPath)
    problems = [impFromFilePath(folderPath+file) for file in files]
    return problems

def impFromFilePath(filePath):
    f=open(filePath,'r')
    lines = f.readlines()
    points = [tuple(line.split()[1:3]) for line in lines if line.split()[0].isdigit()]
    return Problem(lines[0].split()[-1],list(map(lambda x: (float(x[0]),float(x[1])),points)))

def impResults(filePath):
    f=open(filePath,'r')
    lines = f.readlines()
    d = dict([tuple(line.split()[0:2]) for line in lines])
    return d

probs = getProblemsFromFolder("../dimacs_inst/")
