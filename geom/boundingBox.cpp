#include "boundingBox.h"

#include <float.h>

//CODE FROM CAGELAB

BoundingBox::BoundingBox()
{
   reset();
}

void BoundingBox::reset()
{
   min = cg3::Vec3d( FLT_MAX,   FLT_MAX,   FLT_MAX);
   max = cg3::Vec3d(-FLT_MAX,  -FLT_MAX,  -FLT_MAX);
}

cg3::Vec3d BoundingBox::center() const
{
   return (min+max)*0.5;
}

double BoundingBox::diagonal() const
{
   return (min-max).length();
}
