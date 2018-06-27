#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Eigen/Geometry"
#include "geom/vec3.h"
#include "math/quaternion.h"
#include "common/types.h"

namespace cg3 {

class Transform
{
private:
   //https://eigen.tuxfamily.org/dox/group__TutorialGeometry.html
   cg3::eigenTransformation transformation;
   //Sostituisci la trasformazione affine di eigen con una generica matrice4x4
   //Cosi' è possibile fare il blending delle matrici per lbs

public:
   Transform();

   Transform(double tx, double ty, double tz);
   Transform(cg3::dQuaternion r);
   Transform(double mat[16]);
   Transform(cg3::Vec3d col1, cg3::Vec3d col2, cg3::Vec3d col3);
   Transform(cg3::eigenTransformation t);

   cg3::Vec3d getTranslation() const;
   cg3::dQuaternion getRotation() const;

   Transform cumulateWith(const Transform & t) const;
   Transform inverse() const;

   Transform scale(double s) const;

   cg3::Vec3d applyToPoint(cg3::Vec3d p) const;
   cg3::Vec3d applyToPoint(double x, double y, double z) const;

   Transform transformTowardsOrigin(Transform t);

   inline double & operator() (int x, int y) { return transformation(x,y); }
   inline double operator () (int x, int y) const { return transformation(x,y); }

   /*inline Transform operator+(const Transform other) const
   {
      Eigen::Matrix4d a(transformation);
      Eigen::Matrix4d b(other.transformation);
      cg3::eigenTransformation res(a+b);
      return Transform ( res );
   }*/

   /*inline Transform operator+=(const Transform other) const
   {
      Eigen::Matrix4d a(transformation);
      Eigen::Matrix4d b(other.transformation);
      cg3::eigenTransformation res(a+b);
      transformation = res;
      return res;
   }*/


};

Transform operator*(const double & s, const Transform & t);

}

#endif // TRANSFORM_H
