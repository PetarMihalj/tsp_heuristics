#include <iostream>
#include <random>

#include "util/point.h"
#include "algo/algorithms.h"

using namespace std;

std::default_random_engine rnd{151};
std::uniform_real_distribution<double> rd(0,100);

std::default_random_engine rndForUF{};
std::discrete_distribution<int> distForUF(0,1);

int main(){
    int n=20000;
    vector<point> v{};
    for (int i=0;i<n;i++){
        v.push_back({rd(rnd),rd(rnd)});
    }

    cout << multipleFragments(v).toString(false);
}