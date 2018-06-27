#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "geom/vec3.h"

typedef enum
{
   ABSTRACT,
   TRIMESH,
   QUADMESH,
   CAGE,
   SKELETON
}
DrawableType;

class DrawableObject
{
public:

   DrawableObject();
   virtual ~DrawableObject();

   DrawableType type;

   virtual void draw()                             const = 0;

   //sceneCenter and sceneRadius must return true if
   //center and radius are valid, false otherwise.
   virtual bool sceneCenter( cg3::Vec3d & center ) const;
   virtual bool sceneRadius( double & radius )     const;
};

#endif // DRAWABLEOBJECT_H
