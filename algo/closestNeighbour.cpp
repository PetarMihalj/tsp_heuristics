#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
#include <chrono>

#include "../util/KDTree.h"
#include "../util/result.h"

using namespace std;

result closestNeighbour(vector<point> v){
    auto t1 = chrono::high_resolution_clock::now();
    int n=v.size();
    KDTree T{v};
    vector<int> tspSol{};

    int starter=T.closest(point{0,0});
    tspSol.push_back(starter);
    T.setActiveState(starter,false);

    double len=0;

    for (int i=0;i<n-1;i++){
        int clInd=T.closest(T.get(tspSol[tspSol.size()-1]));
        len+=sqrt(distSq(v[tspSol[tspSol.size()-1]],T.get(clInd)));
        T.setActiveState(clInd,false);
        tspSol.push_back(clInd);
    }
    len+=sqrt(distSq(v[tspSol[0]],v[tspSol[tspSol.size()-1]]));

    auto t2 = chrono::high_resolution_clock::now();
    long long timeMS = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();

    return result{"closestNeighbour", len, tspSol, {{"KDTreeSteps",T.getStepCount()},{"timeMS",timeMS}}};
}