#include "geom/cage.h"
#include "geom/plane.h"
#include "iostream"

Cage::Cage()
   : Trimesh()
{

}


Cage::Cage( const std::vector<double>   & vertices ,
            const std::vector<int>      & tris     )
   : Trimesh(vertices, tris)
{
   init();
}

void Cage::init()
{

}

void Cage::clear()
{
   Trimesh::clear();
}
