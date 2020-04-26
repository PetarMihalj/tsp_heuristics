//
// Created by Petar on 3/31/2019.
//

#ifndef HAMCYCLE_ALGORITHMS_H
#define HAMCYCLE_ALGORITHMS_H

#include "../util/result.h"
#include "../util/point.h"

result closestNeighbour(vector<point> v);
result closestNeighbourBF(vector<point> v);
result multipleFragments(vector<point> v);
result mst(vector<point> v);
result mstBF(vector<point> v);
result christofides(vector<point> v);

#endif //HAMCYCLE_ALGORITHMS_H
