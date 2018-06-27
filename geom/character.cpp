#include "character.h"

Character::Character()
   : Trimesh()
{

}

Character::Character( const std::vector<double>   & vertices ,
                      const std::vector<int>      & tris     )
   : Trimesh(vertices, tris),
     restPoseVertices(vertices),
     cagePoseVertices(vertices),
     skelPoseVertices(vertices),
     skelCageBlendVertices(vertices)
{
   init();
}

void Character::init()
{
   blendValue = 0.0;
}

void Character::clear()
{
   restPoseVertices.clear();
   Trimesh::clear();
}

void Character::updateSkelCageBlendVertices()
{
   for(int i=0; i<skelCageBlendVertices.size(); ++i)
   {
      skelCageBlendVertices[i] = (blendValue * cagePoseVertices[i]) + ((1.0-blendValue) * skelPoseVertices[i]);
   }
}
