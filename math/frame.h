#ifndef FRAME_H
#define FRAME_H

#include "geom/vec3.h"
#include "geom/transform.h"

namespace cg3
{

class Frame
{
public:
   Frame();
   Frame(cg3::Vec3d u,
         cg3::Vec3d v,
         cg3::Vec3d w,
         cg3::Vec3d o);

   void setFrame(cg3::Vec3d u,
                 cg3::Vec3d v,
                 cg3::Vec3d w,
                 cg3::Vec3d o);

   cg3::Vec3d LocalToGlobal(cg3::Vec3d vLocal);
   cg3::Vec3d GlobalToLocal(cg3::Vec3d vGlobal);

   cg3::Transform LocalToGlobal(cg3::Transform tLocal);
   cg3::Transform GlobalToLocal(cg3::Transform tGlobal);

   inline cg3::Vec3d u() const
   {
      return _u;
   }

   inline cg3::Vec3d v() const
   {
      return _v;
   }

   inline cg3::Vec3d w() const
   {
      return _w;
   }

   inline cg3::Vec3d o() const
   {
      return _o;
   }

private:
   cg3::Vec3d _u;
   cg3::Vec3d _v;
   cg3::Vec3d _w;
   cg3::Vec3d _o;

   cg3::Transform rotationMatrixGlobalToLocal;
   cg3::Transform rotationMatrixLocalToGlobal;

   void createRotationMatrixes();
};

}

#endif // FRAME_H
