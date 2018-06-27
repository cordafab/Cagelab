#include "transform.h"

namespace cg3 {

Transform::Transform()
{
   transformation.setIdentity();
}

Transform::Transform(double tx, double ty, double tz)
{
   Eigen::Translation3d translation(tx, ty, tz);

   transformation = translation;
}

Transform::Transform(dQuaternion r)
{
   Eigen::Quaterniond rotation(r.s(), r.x(), r.y(), r.z());

   transformation = rotation;
}

Transform::Transform(double mat[16])
{
   Eigen::Matrix4d m; //It is column major

   m.col(0) = Eigen::Vector4d(mat[0]  , mat[1]  , mat[2]  , mat[3] );
   m.col(1) = Eigen::Vector4d(mat[4]  , mat[5]  , mat[6]  , mat[7] );
   m.col(2) = Eigen::Vector4d(mat[8]  , mat[9]  , mat[10] , mat[11]);
   m.col(3) = Eigen::Vector4d(mat[12] , mat[13] , mat[14] , mat[15]);

   transformation = m;
}

Transform::Transform(Vec3d col1, Vec3d col2, Vec3d col3)
{
   Eigen::Matrix4d m; //It is column major

   m.col(0) = Eigen::Vector4d(col1.x(), col1.y(), col1.z(), 0 );
   m.col(1) = Eigen::Vector4d(col2.x(), col2.y(), col2.z(), 0 );
   m.col(2) = Eigen::Vector4d(col3.x(), col3.y(), col3.z(), 0 );
   m.col(3) = Eigen::Vector4d(0 , 0 , 0 , 1 );

   transformation = m;
}

Transform::Transform(cg3::eigenTransformation t)
{
   transformation = t;
}

cg3::Vec3d Transform::getTranslation() const
{
   Eigen::Vector3d vecT = transformation.translation();
   return cg3::Vec3d(vecT[0], vecT[1], vecT[2]);
}

dQuaternion Transform::getRotation() const
{
   //mi basta passargli la matrice intera e elimina la traslazione?
   Eigen::Quaterniond q(transformation.rotation());
   return cg3::dQuaternion (q.x(),q.y(),q.z(),q.w());
}

Transform Transform::cumulateWith(const Transform & t) const
{
   return Transform(transformation * t.transformation);
}

Transform Transform::inverse() const
{
   return Transform(transformation.inverse(Eigen::Affine));
}

Transform Transform::scale(double s) const
{
   return Transform(s * transformation);
}

cg3::Vec3d Transform::applyToPoint(cg3::Vec3d p) const
{
   Eigen::Vector3d _p(p.x(), p.y(), p.z());

   Eigen::Vector3d p1 = transformation * _p;
   return cg3::Vec3d(p1[0], p1[1], p1[2]);
}

Vec3d Transform::applyToPoint(double x, double y, double z) const
{
   Eigen::Vector3d _p(x, y, z);

   Eigen::Vector3d p1 = transformation * _p;
   return cg3::Vec3d(p1[0], p1[1], p1[2]);
}

Transform Transform::transformTowardsOrigin(Transform t)
{
   Transform thisTransform(transformation);
   Eigen::Vector3d vecT = transformation.translation();
   thisTransform.transformation(0,3) = 0;
   thisTransform.transformation(1,3) = 0;
   thisTransform.transformation(2,3) = 0;
   thisTransform.transformation = t.transformation * thisTransform.transformation;
   thisTransform.transformation(0,3) += vecT[0];
   thisTransform.transformation(1,3) += vecT[1];
   thisTransform.transformation(2,3) += vecT[2];
   return thisTransform;
}

Transform operator*(const double & s, const Transform & t)
{
   return t.scale(s);
}

Transform operator*(const Transform & t, const double & s)
{
   return t.scale(s);
}

/*void Transform::addTranslation(cg3::Transform t)
{
   //transformation.translate(t.transformation);

   transformation(0,3) += t.transformation(0,3);
   transformation(1,3) += t.transformation(1,3);
   transformation(2,3) += t.transformation(2,3);
}*/

}
