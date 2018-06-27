#ifndef EDGE_H
#define EDGE_H

#include <algorithm>

//CODE FROM CAGELAB

typedef std::pair<int,int> edge;

inline edge uniqueEdge(int v0, int v1)
{
    edge e;
    e.first  = std::min(v0,v1);
    e.second = std::max(v0,v1);
    return e;
}

#endif // EDGE_H
