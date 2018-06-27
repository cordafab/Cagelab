#ifndef RAY_H
#define RAY_H

#include "geom/vec3.h"

namespace cg3 {

template<class T> class Ray
{
private:

      Vec3<T> _origin;
      Vec3<T> _direction;

public:
   Ray()
   {
      setOrigin(Vec3<T>());
      setDirection(Vec3<T>());
   }

   Ray(Vec3<T> origin, Vec3<T> direction)
   {
      setOrigin(origin);
      setDirection(direction);
   }

   inline void set(Vec3<T> origin, Vec3<T> direction)
   {
      setOrigin(origin);
      setDirection(direction);
   }

   inline void setOrigin(Vec3<T> origin)
   {
      _origin = origin;
   }

   inline void setDirection(Vec3<T> direction)
   {
      _direction = direction;
   }

   inline Vec3<T> origin() const
   {
      return _origin;
   }

   inline Vec3<T> direction() const
   {
      return _direction;
   }

   inline Vec3<T> getPointOnRay(const double & t)
   {
      return _origin + (_direction * t);
   }

};

typedef Ray<double> dRay;

}

#endif // RAY_H
