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

   inline const std::vector<double> & getRestPoseVerticesVector() const
   {
      return restPoseVertices;
   }

   inline cg3::Vec3<double> getRestPoseVertex(int vId) const
   {
      int vIdPtr = vId * 3;
      //TODO: CHECK_BOUNDS(coords, vid_ptr+2);
      return cg3::Vec3<double>(
                  restPoseVertices[vIdPtr + 0],
                  restPoseVertices[vIdPtr + 1],
                  restPoseVertices[vIdPtr + 2]
             );
   }

   inline void setRestPoseVertex(int vId, cg3::Vec3d newPosition)
   {
      int vIdPtr = vId * 3;
      //TODO: CHECK_BOUNDS(coords, vid_ptr+2);
      restPoseVertices[vIdPtr + 0] = newPosition.x();
      restPoseVertices[vIdPtr + 1] = newPosition.y();
      restPoseVertices[vIdPtr + 2] = newPosition.z();
   }

   inline void setRestPoseVector(const std::vector<double> _vertices){restPoseVertices = _vertices;}


   inline cg3::Vec3<double> getActualPoseVertex(int vId) const
   {
      return getVertex(vId);
   }

   inline void setActualPoseVector(const std::vector<double> _vertices){setVerticesVector(_vertices);}

protected:

   std::vector<double> restPoseVertices;

   //TODO: ELIMINA IMPLEMENTAZIONI DA FILE H E CREA UN CPP DEDICATO

};

#endif // CAGE_H



