#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
#include <chrono>

#include "../util/KDTree.h"
#include "../util/result.h"
#include "../util/UnionFind.h"

using namespace std;

KDTree T;
int searchesDone=0;
vector<int> tail;

priority_queue<pair<double,pair<int,int>>,
        std::vector<pair<double,pair<int,int>>>,
        std::greater<pair<double,pair<int,int>>>> pq{};

int closestWithoutMeAndMyTail(int x){
    //hide tail and myself
    T.setActiveState(tail[x],false);
    T.setActiveState(x,false);

    //find fixed and push it back
    int cl = T.closest(T.get(x));
    searchesDone++;

    //unhide tail and myself
    T.setActiveState(tail[x],true);
    T.setActiveState(x,true);

    return cl;
}

result multipleFragments(vector<point> v){
    auto t1 = chrono::high_resolution_clock::now();
    int n=v.size();
    T=KDTree{v};
    vector<int> degree(n);
    vector<vector<int>> neighbours(n,vector<int>{});
    tail=vector<int>(n);

    for (int i=0;i<n;i++){
        tail[i]=i;
        degree[i]=0;
        int cl = closestWithoutMeAndMyTail(i);
        pq.push({distSq(v[i],v[cl]),{i,cl}});
    }

    for (int i=0;i<n-1 ;i++){
        pair<double,pair<int,int>> t;
        while (true){
            t = pq.top(); pq.pop();
            int x=t.second.first; int y=t.second.second;

            if (degree[x]==2) continue;
            if (degree[y]<2 && y!=tail[x]) break;

            int cl = closestWithoutMeAndMyTail(x);
            pq.push({distSq(v[x],v[cl]),{x,cl}});
        }

        //sad je sve ok
        int x=t.second.first; int y=t.second.second;
        neighbours[x].push_back(y);
        neighbours[y].push_back(x);
        degree[x]++;
        degree[y]++;
        int tx=tail[x];
        int ty=tail[y];
        tail[x]=tail[tx]=ty;
        tail[y]=tail[ty]=tx;

        if (degree[x]==2){
            T.setActiveState(x,false);
        }
        else{
            int cl = closestWithoutMeAndMyTail(x);
            pq.push({distSq(v[x],v[cl]),{x,cl}});
        }

        if (degree[y]==2){
            T.setActiveState(y,false);
        }
        else{
            int cl = closestWithoutMeAndMyTail(y);
            pq.push({distSq(v[y],v[cl]),{y,cl}});
        }
    }

    vector<int> tspSol{};
    vector<bool> visited(n);

    int curr=0;
    for (int i=0;i<n;i++){
        if (degree[i]==1){
            curr=i;
            break;
        }
    }

    for (int i=0;i<n;i++){
        tspSol.push_back(curr);
        visited[curr]=true;
        if (!visited[neighbours[curr][0]]){
            curr=neighbours[curr][0];
        }
        else{
            curr=neighbours[curr][1];
        }
    }

    double len=0;

    for (int i=0;i<n-1;i++){
        len+=sqrt(distSq(v[tspSol[i]],v[tspSol[i+1]]));
    }
    len+=sqrt(distSq(v[tspSol[0]],v[tspSol[tspSol.size()-1]]));

    auto t2 = chrono::high_resolution_clock::now();
    long long timeMS = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();

    return result{"multipleFragments", len, tspSol,
                  {{"KDTreeSteps",T.getStepCount()},{"KDSearchesDone",searchesDone},{"timeMS",timeMS}}};
}