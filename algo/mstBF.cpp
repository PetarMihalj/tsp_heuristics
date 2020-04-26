#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <stack>

#include "../util/point.h"
#include "../util/UnionFind.h"
#include "../util/result.h"
#include "../util/BoruvkaEuclideanMST.h"

using namespace std;

result mstBF(vector<point> v){
    auto t1 = chrono::high_resolution_clock::now();

    int n=v.size();


    vector<vector<int>> tree(v.size(),vector<int>{});

    vector<pair<double, pair<int,int>>> edges{};
    for (int i=0;i<n;i++){
        for (int j=i+1;j<n;j++){
            edges.push_back({distSq(v[i],v[j]),pair<int,int>{i,j}});
        }
    }

    UnionFind UF(n);
    sort(edges.begin(),edges.end());

    for (auto edge:edges){
        if (UF.parent(edge.second.first)!=UF.parent(edge.second.second)){
            UF.join(edge.second.first,edge.second.second);
            tree[edge.second.first].push_back(edge.second.second);
            tree[edge.second.second].push_back(edge.second.first);
        }
    }

    //so that both algorithms give same results
    for (int i=0;i<n;i++){
        sort(tree[i].begin(),tree[i].end());
    }

    int lastPointIndex=0;
    stack<int> st{};
    vector<int> visited(n);
    visited[0]=1;
    st.push(0);

    vector<int> tspSol{};

    while (!st.empty()){
        int curr = st.top(); st.pop();
        tspSol.push_back(curr);
        for (int neigh: tree[curr]){
            if (!visited[neigh]){
                visited[neigh]=1;
                st.push(neigh);
            }
        }
    }

    double len=0;

    for (int i=0;i<n-1;i++){
        len+=sqrt(distSq(v[tspSol[i]],v[tspSol[i+1]]));
    }
    len+=sqrt(distSq(v[tspSol[0]],v[tspSol[tspSol.size()-1]]));

    auto t2 = chrono::high_resolution_clock::now();
    long long timeMS = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();

    return result{"mst", len, tspSol,{{"timeMS",timeMS}}};
}