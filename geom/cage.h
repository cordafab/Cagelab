#ifndef CAGE_H
#define CAGE_H

#include "geom/trimesh.h"
#include "common/types.h"

class Cage
      : public Trimesh
{
public:
   Cage();
   Cage( const std::vector<double>      & vertices ,
         const std::vector<int>         & tris     );

   void init();
   void clear();


   inline cg3::Vec3<double> getActualPoseVertex(int vId) const
   {
      return getVertex(vId);
   }

   inline void setActualPoseVector(const std::vector<double> _vertices){setVerticesVector(_vertices);}

protected:

   //TODO: ELIMINA IMPLEMENTAZIONI DA FILE H E CREA UN CPP DEDICATO

};

#endif // CAGE_H



