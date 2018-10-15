#include "geom/cage.h"
#include "geom/plane.h"
#include "iostream"

Cage::Cage()
   : Trimesh()
{

}


Cage::Cage( const std::vector<double>   & vertices ,
            const std::vector<int>      & tris     )
   : Trimesh(vertices, tris),
   restPoseVertices(vertices)
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

void Cage::interpolateKeyframes(const std::vector<double> & keyframeLow,
                                const std::vector<double> & keyframeTop,
                                double a)
{
   std::cout << "Anim " << a << std::endl;
   for(unsigned long i=0; i<vertices.size(); ++i)
   {
      vertices[i] = restPoseVertices[i] + ((keyframeLow[i] * (1.0-a)) + (keyframeTop[i] * a));
   }
}
