#include <iostream>
#include <random>

#include "util/point.h"
#include "algo/algorithms.h"

using namespace std;

void readAndExecute(){
    ifstream IS;
    IS.open("inputFile.txt");
    ofstream OS;
    OS.open("outputFile.txt");

    string algoName;
    IS>>algoName;
    int n; IS>>n;
    vector<point> v(n);
    for (int i=0;i<n;i++){
        double x,y; IS>>x>>y;
        v[i]={x,y};
    }

    if (algoName=="christofides"){
        OS << christofides(v).json();
    }
    else if (algoName=="closestNeighbour"){
        OS << closestNeighbour(v).json();
    }
    else if (algoName=="closestNeighbourBF"){
        OS << closestNeighbourBF(v).json();
    }
    else if (algoName=="mst"){
        OS << mst(v).json();
    }
    else if (algoName=="mstBF"){
        OS << mstBF(v).json();
    }
    else if (algoName=="multipleFragments"){
        OS << multipleFragments(v).json();
    }
    else{
        OS << "Wrong algorithm name";
    }

    IS.close();
    OS.close();
}

int main(){
    readAndExecute();
}