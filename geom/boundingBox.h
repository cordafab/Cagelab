#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "geom/vec3.h"

//CODE FROM CAGELAB

class BoundingBox
{
public:

   BoundingBox();

   cg3::Vec3d     min, max;

   void           reset();
   cg3::Vec3d     center() const;
   double         diagonal()   const;

};

#endif // BOUNDINGBOX_H
