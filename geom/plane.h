#ifndef PLANE_H
#define PLANE_H

#include "geom/vec3.h"

#include "Eigen/Geometry"
#include "Eigen/Core"
#include <vector>

namespace cg3 {

template<class T> class Plane
{

private:

   T _d;
   Vec3<T> _normal;
   Vec3<T> _point;

public:

   Plane()
   {
      set(Vec3<T>(), Vec3<T>());
   }

   Plane(Vec3<T> point, Vec3<T> normal)
   {
      set(point, normal);
   }

   Plane(const std::vector<double> & vertices,
         const std::vector<int>    & chosenVerticesIndexes)
   {
      // http://www.ilikebigbits.com/blog/2015/3/2/plane-from-points
      // centroid
      cg3::Vec3d c(0,0,0);
      for(auto p : chosenVerticesIndexes)
      {
         c[0] += vertices[p*3+0];
         c[1] += vertices[p*3+1];
         c[2] += vertices[p*3+2];
      }
      c /= static_cast<double>(chosenVerticesIndexes.size());

      // 3x3 covariance matrix
      double xx = 0.0; double yy = 0.0;
      double xy = 0.0; double yz = 0.0;
      double xz = 0.0; double zz = 0.0;
      //
      for(auto p : chosenVerticesIndexes)
      {
        cg3::Vec3d pc(0,0,0); //p-c

        pc[0] += vertices[p*3+0] - c[0];
        pc[1] += vertices[p*3+1] - c[1];
        pc[2] += vertices[p*3+2] - c[2];

        xx += pc.x() * pc.x();
        xy += pc.x() * pc.y();
        xz += pc.x() * pc.z();
        yy += pc.y() * pc.y();
        yz += pc.y() * pc.z();
        zz += pc.z() * pc.z();
      }

      double det_x   = yy*zz - yz*yz;
      double det_y   = xx*zz - xz*xz;
      double det_z   = xx*yy - xy*xy;
      double det_max = std::max(det_x, std::max(det_y, det_z));

      if (fabs(det_max) == 1e-5) std::cerr
            << "WARNING : the samples don't span a plane!" << std::endl;

      cg3::Vec3d n;
      if (det_max == det_x) n = cg3::Vec3d(1.0, (xz*yz - xy*zz) / det_x, (xy*yz - xz*yy)/det_x);else
      if (det_max == det_y) n = cg3::Vec3d((yz*xz - xy*zz) / det_y, 1.0, (xy*xz - yz*xx)/det_y);else
      if (det_max == det_z) n = cg3::Vec3d((yz*xy - xz*yy) / det_z, (xz*xy - yz*xx)/det_z, 1.0);
      else assert(false);

      set(c,n);
   }

   Plane(const std::vector<cg3::Vec3d> & samples)
   {
      // http://www.ilikebigbits.com/blog/2015/3/2/plane-from-points
      // centroid
      cg3::Vec3d c(0,0,0);
      for(auto p : samples) c += p;

      c /= static_cast<double>(samples.size());

      // 3x3 covariance matrix
      double xx = 0.0; double yy = 0.0;
      double xy = 0.0; double yz = 0.0;
      double xz = 0.0; double zz = 0.0;
      //
      for(auto p : samples)
      {
        cg3::Vec3d pc = p-c;

        xx += pc.x() * pc.x();
        xy += pc.x() * pc.y();
        xz += pc.x() * pc.z();
        yy += pc.y() * pc.y();
        yz += pc.y() * pc.z();
        zz += pc.z() * pc.z();
      }

      double det_x   = yy*zz - yz*yz;
      double det_y   = xx*zz - xz*xz;
      double det_z   = xx*yy - xy*xy;
      double det_max = std::max(det_x, std::max(det_y, det_z));

      if (fabs(det_max) == 1e-5) std::cerr
            << "WARNING : the samples don't span a plane!" << std::endl;

      cg3::Vec3d n;
      if (det_max == det_x) n = cg3::Vec3d(1.0, (xz*yz - xy*zz)/det_x, (xy*yz - xz*yy)/det_x);else
      if (det_max == det_y) n = cg3::Vec3d((yz*xz - xy*zz)/det_y, 1.0, (xy*xz - yz*xx)/det_y);else
      if (det_max == det_z) n = cg3::Vec3d((yz*xy - xz*yy)/det_z, (xz*xy - yz*xx)/det_z, 1.0);
      else assert(false);

      set(c,n);
   }

   inline void set(Vec3<T> point, Vec3<T> normal)
   {
      _normal = normal;
      _normal.normalize();
      _d = point.dot(normal);
      _point = point;
   }

   inline T & d() { return _d; }
   inline Vec3<T> & normal() { return _normal; }

   inline const T & d() const { return _d; }
   inline const Vec3<T> & normal() const { return _normal; }

   inline T distanceFromPlane (const Vec3<T> & point)
   {
      return point.dot(_normal)-_d;
   }

   bool doIntersectWithLine(const Vec3<T> & v1,
                               const Vec3<T> & v2)
   {
       double v1Side = getPointPosition(v1);
       double v2Side = getPointPosition(v2);

       //if the two end-vertices are located on different side of the main plane
       if(v1Side*v2Side<0)
       {
           return true;
       }
       return false;
   }

   bool computeIntersectionWithLine(const Vec3<T> & v1,
                                       const Vec3<T> & v2,
                                             Vec3<T> & intersection)
   {
       Vec3<T> dir = v2-v1;
       T u = dir[0];
       T v = dir[1];
       T w = dir[2];

       Eigen::Matrix<T, 3, 3> A;
       A(0,0) = _normal[0];   A(0,1) = _normal[1];   A(0,2) = _normal[2];
       A(1,0) = w;            A(1,1) = 0;            A(1,2) = -u;
       A(2,0) = v;            A(2,1) = -u;           A(2,2) = 0;

       Eigen::Matrix<T, 3, 1> b;
       b(0) = _d;
       b(1) = (w*v1[0])-(u*v1[2]);
       b(2) = (v*v1[0])-(u*v1[1]);

       Eigen::Matrix<T, 3, 1> x = A.colPivHouseholderQr().solve(b);

       intersection = cg3::Vec3<T>(x[0], x[1], x[2]);

       return true;
   }

   inline const cg3::Vec3<T> projectPointOnPlane(const cg3::Vec3<T> & point)
   {
      //https://stackoverflow.com/questions/9605556/how-to-project-a-point-onto-a-plane-in-3d

      T dist = distanceFromPlane(point);
      return point-(dist*_normal);
   }
};

typedef Plane<double> dPlane;

}
#endif // PLANE_H
