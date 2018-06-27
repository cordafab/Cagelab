#include "drawableObject.h"

DrawableObject::DrawableObject()
{
   type = ABSTRACT;
}

DrawableObject::~DrawableObject()
{

}

bool DrawableObject::sceneCenter(cg3::Vec3d & center) const
{
   return false;
}

bool DrawableObject::sceneRadius(double & radius) const
{
   return false;
}

