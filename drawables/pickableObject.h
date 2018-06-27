#ifndef PICKABLEOBJECT_H
#define PICKABLEOBJECT_H

#include "geom/vec3.h"
#include "math/quaternion.h"
#include "geom/transform.h"

class PickableObject
{
public:
   PickableObject();
   virtual ~PickableObject();

   virtual void drawWithNames () = 0;

   //returns true if the barycenter is a valid value,
   //false otherwise (or if none objects are selected)
   //barycenter contains the center of mass of the selected objects
   virtual bool getSelectedObjectsBarycenter(cg3::Point3d & barycenter) const;

   virtual void selectObject (const int index) = 0;
   virtual void deselectObject (const int index) = 0;

   //Deformation
   virtual void translate (const cg3::Vec3d & translation);

   virtual void rotate (const cg3::dQuaternion & rotation,
                        const cg3::Point3d & rotationCenter);

   virtual void rotate (const cg3::dQuaternion & rotation);

   virtual void rotate (const cg3::Transform & rotation,
                        const cg3::Point3d & rotationCenter);

   virtual void rotate (const cg3::Transform & rotation);

   virtual void scale (const cg3::Point3d & centerOfScaling,
                       const int delta);

   //Flags
   bool activateTransformation;
};

#endif // PICKABLEOBJECT_H
