#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <stack>

#include "../util/point.h"
#include "../util/UnionFind.h"
#include "../util/result.h"
#include "../util/KDTree.h"
#include "../util/BoruvkaEuclideanMST.h"

using namespace std;

result christofides(vector<point> v){
    auto t1 = chrono::high_resolution_clock::now();

    int n=v.size();
    vector<vector<int>> tree=boruvkaEuclideanMST(v);

    //Greedy matching
    KDTree T(v);
    for (int i=0;i<n;i++){
        if (tree[i].size()%2==0){
            T.setActiveState(i,false);
        }
    }

    for (int i=0;i<n;i++){
        if (tree[i].size()%2==1){
            T.setActiveState(i,false);
            /*for (int neigh:tree[i]){
                T.setActiveState(neigh,false);
            }*/
            int cl = T.closest(T.get(i));
            /*for (int neigh:tree[i]){
                if (tree[neigh].size()%2==1){
                    T.setActiveState(neigh,true);
                }
            }*/
            T.setActiveState(cl,false);
            tree[i].push_back(cl);
            tree[cl].push_back(i);
        }
    }

    //Eulerian circuit
    vector<vector<int>> tours(n,vector<int>{});
    map<pair<int,int>,int> alsoUsed{};
    queue<int> kandidati{};

    kandidati.push(0);

    while (!kandidati.empty()){
        int i = kandidati.front(); kandidati.pop();
        if (tree[i].empty()){
            if (tours[i].empty()){
                tours[i].push_back(i);
                tours[i].push_back(i);
            }
            continue;
        }

        tours[i].push_back(i);
        int curr=i;
        while (true){
            while (!tree[curr].empty() && alsoUsed[{curr,tree[curr].back()}]>0){
                pair<int,int> that = {curr,tree[curr].back()};
                tree[curr].pop_back();
                alsoUsed[that]--;
            }
            if (tree[curr].empty()) break;

            int newNode=tree[curr].back(); tree[curr].pop_back();
            alsoUsed[{newNode,curr}]++;

            tours[i].push_back(newNode);
            curr=newNode;

            kandidati.push(newNode);
        }
        if (tours[i].size()==1){
            tours[i].push_back(i);
        }
    }

    stack<pair<int,int>> st{};
    vector<bool> visitedTour(n);
    vector<int> tspSol{};

    st.push({0,1});
    visitedTour[0]=true;
    tspSol.push_back(0);

    while (!st.empty()){
        pair<int,int> e = st.top(); st.pop();
        int next=tours[e.first][e.second];
        if (e.second==tours[e.first].size()-1) continue;

        st.push({e.first,e.second+1});
        if (!visitedTour[next]){
            tspSol.push_back(next);
            st.push({next,1});
            visitedTour[next]=true;
        }
    }

    double len=0;

    for (int i=0;i<n-1;i++){
        len+=sqrt(distSq(v[tspSol[i]],v[tspSol[i+1]]));
    }
    len+=sqrt(distSq(v[tspSol[0]],v[tspSol[tspSol.size()-1]]));

    auto t2 = chrono::high_resolution_clock::now();
    long long timeMS = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();

    return result{"christofides", len, tspSol,{{"timeMS",timeMS}}};
}