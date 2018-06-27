#ifndef CHARACTER_H
#define CHARACTER_H

#include "geom/trimesh.h"

class Character
      : public Trimesh
{
public:
   Character();
   Character(const std::vector<double>      & vertices ,
             const std::vector<int>         & tris     );

   void init();
   void clear();

   //REST POSE

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

   inline void setRestPoseVector(const std::vector<double> & _vertices){restPoseVertices = _vertices;}

   //ACTUAL POSE

   inline const std::vector<double> & getActualPoseVerticesVector() const
   {
      return getVerticesVector();
   }

   inline cg3::Vec3<double> getActualPoseVertex(int vId) const
   {
      return getVertex(vId);
   }

   inline void setActualPoseVector(const std::vector<double> & _vertices){setVerticesVector(_vertices);}

   //CAGE POSE

   inline const std::vector<double> & getCagePoseVerticesVector() const
   {
      return cagePoseVertices;
   }

   inline cg3::Vec3<double> getCagePoseVertex(int vId) const
   {
      int vIdPtr = vId * 3;
      //TODO: CHECK_BOUNDS(coords, vid_ptr+2);
      return cg3::Vec3<double>(
                  cagePoseVertices[vIdPtr + 0],
                  cagePoseVertices[vIdPtr + 1],
                  cagePoseVertices[vIdPtr + 2]
             );
   }

   inline void setCagePoseVertex(int vId, cg3::Vec3d newPosition)
   {
      int vIdPtr = vId * 3;
      //TODO: CHECK_BOUNDS(coords, vid_ptr+2);
      cagePoseVertices[vIdPtr + 0] = newPosition.x();
      cagePoseVertices[vIdPtr + 1] = newPosition.y();
      cagePoseVertices[vIdPtr + 2] = newPosition.z();
   }

   inline void setCagePoseVector(const std::vector<double> & _vertices){cagePoseVertices = _vertices;}

   //SKELETON POSE

   inline const std::vector<double> & getSkelPoseVerticesVector() const
   {
      return skelPoseVertices;
   }

   inline cg3::Vec3<double> getSkelPoseVertex(int vId) const
   {
      int vIdPtr = vId * 3;
      //TODO: CHECK_BOUNDS(coords, vid_ptr+2);
      return cg3::Vec3<double>(
                  skelPoseVertices[vIdPtr + 0],
                  skelPoseVertices[vIdPtr + 1],
                  skelPoseVertices[vIdPtr + 2]
             );
   }

   inline void setSkelPoseVertex(int vId, cg3::Vec3d newPosition)
   {
      int vIdPtr = vId * 3;
      //TODO: CHECK_BOUNDS(coords, vid_ptr+2);
      skelPoseVertices[vIdPtr + 0] = newPosition.x();
      skelPoseVertices[vIdPtr + 1] = newPosition.y();
      skelPoseVertices[vIdPtr + 2] = newPosition.z();
   }

   inline void setSkelPoseVector(const std::vector<double> & _vertices){skelPoseVertices = _vertices;}

   //POSE SWAPPING

   inline void setRestPoseAsActual() {setActualPoseVector(restPoseVertices);}
   inline void setCagePoseAsActual() {setActualPoseVector(cagePoseVertices);}
   inline void setSkelPoseAsActual() {setActualPoseVector(skelPoseVertices);}

   inline void setSkelCageBlendingValue(double value)
   {
      blendValue = value;
   }

   void updateSkelCageBlendVertices();


protected:

   //TODO: ELIMINA IMPLEMENTAZIONI DA FILE H
   std::vector<double> restPoseVertices;
   std::vector<double> cagePoseVertices;
   std::vector<double> skelPoseVertices;
   std::vector<double> skelCageBlendVertices;

   double blendValue;

};

#endif // CHARACTER_H
