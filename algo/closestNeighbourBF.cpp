#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
#include <chrono>

#include "../util/KDTree.h"
#include "../util/result.h"
#include "../util/point.h"

int compCount=0;

int closestBFvisited(vector<point>& data, vector<bool>& visited, point q){
    double minDistSq=10E50;
    point opt{};
    int optIndex=-1;
    for (int i=0;i<data.size();i++){
        compCount++;
        if (visited[i]) continue;
        double c=distSq(q,data[i]);
        if (c<minDistSq){
            minDistSq=c;
            opt=data[i];
            optIndex=i;
        }
    }
    return optIndex;
}

result closestNeighbourBF(vector<point> v){
    auto t1 = chrono::high_resolution_clock::now();
    int n=v.size();
    vector<bool> visited(n);
    vector<int> tspSol{};

    int starter = closestBFvisited(v,visited,point{0,0});
    tspSol.push_back(starter);
    visited[starter]=true;

    double len=0;

    for (int i=0;i<n-1;i++){
        point last=v[tspSol[tspSol.size()-1]];
        int clInd=closestBFvisited(v,visited,last);
        len+=sqrt(distSq(last,v[clInd]));
        tspSol.push_back(clInd);
        visited[clInd]=true;
    }

    len+=sqrt(distSq(v[tspSol[0]],v[tspSol[tspSol.size()-1]]));

    auto t2 = chrono::high_resolution_clock::now();
    long long timeMS = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();

    return result{"closestNeighbourBF", len, tspSol, {{"compCount",compCount},{"timeMS",timeMS}}};
}
