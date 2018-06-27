#include "pickableObject.h"

PickableObject::PickableObject()
{
   activateTransformation = true;
}

PickableObject::~PickableObject()
{

}

bool PickableObject::getSelectedObjectsBarycenter(cg3::Point3d &barycenter) const
{
   return false;
}

void PickableObject::translate(const cg3::Vec3d &translation)
{

}

void PickableObject::rotate(const cg3::dQuaternion &rotation, const cg3::Point3d &rotationCenter)
{

}

void PickableObject::rotate(const cg3::dQuaternion &rotation)
{

}

void PickableObject::rotate(const cg3::Transform &rotation, const cg3::Point3d &rotationCenter)
{

}

void PickableObject::rotate(const cg3::Transform &rotation)
{

}

void PickableObject::scale(const cg3::Point3d & centerOfScaling,
                           const int delta)
{

}
