#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <cfloat>
#include <algorithm>
#include <iostream>
#include <common/types.h>

//for cinolib conversion
#include <cinolib/geometry/vec3.h>

namespace cg3 {

template<class T> class Vec3
{
private:

   union {

      struct {
         T _x;
         T _y;
         T _z;
      };

      T _v[3];

   };

public:

   Vec3()
   {
      set(0, 0, 0);
   }

   Vec3(const T x, const T y, const T z)
   {
      set(x, y, z);
   }

   inline const T *ptr() const
   {
       return _v;
   }

   inline T & x() { return _x; }
   inline T & y() { return _y; }
   inline T & z() { return _z; }

   inline const T & x() const { return _x; }
   inline const T & y() const { return _y; }
   inline const T & z() const { return _z; }

   inline T & operator[](const int i)
   {
       return _v[i];
   }

   inline const T & operator[](const int i) const
   {
       return _v[i];
   }

   inline void set(const T x, const T y, const T z)
   {
      _x = x;
      _y = y;
      _z = z;
   }

   inline Vec3<T> cross(const Vec3<T> & other) const
   {
      return Vec3<T> (
               this->_y * other._z - this->_z * other._y,
               this->_z * other._x - this->_x * other._z,
               this->_x * other._y - this->_y * other._x
             );
   }

   inline T dot(const Vec3<T> & other) const
   {
      return (
               this->_x * other._x +
               this->_y * other._y +
               this->_z * other._z
             );
   }

   inline T lengthSquared() const
   {
      return (
               _x * _x +
               _y * _y +
               _z * _z
             );
   }

   inline T norm() const
   {
      return lengthSquared();
   }

   inline T length() const
   {
      return std::sqrt( lengthSquared() );
   }

   inline T magnitude() const
   {
      return length();
   }

   inline T normalize()
   {
      T len = length();
      //TODO: check if len is great than epsilon. If not...
      _x /= len;
      _y /= len;
      _z /= len;
      return len;
   }

   inline Vec3<T> operator-() const
   {
      return Vec3<T> (
               -_x,
               -_y,
               -_z
             );
   }

   inline Vec3<T> operator+(const Vec3<T> other) const
   {
      return Vec3<T> (
               this->_x + other._x,
               this->_y + other._y,
               this->_z + other._z
             );
   }

   inline Vec3<T> operator-(const Vec3<T> other) const
   {
      return Vec3<T> (
               this->_x - other._x,
               this->_y - other._y,
               this->_z - other._z
             );
   }

   inline Vec3<T> operator*(const T s) const
   {
      return Vec3<T> (
               this->_x * s,
               this->_y * s,
               this->_z * s
             );
   }

   inline Vec3<T> operator/(const T s) const
   {
      return Vec3<T> (
               this->_x / s,
               this->_y / s,
               this->_z / s
             );
   }

   inline Vec3<T> operator+=(const Vec3<T> other)
   {
      Vec3<T> tmp (
               this->_x + other._x,
               this->_y + other._y,
               this->_z + other._z
             );
      *this=tmp;
      return tmp;
   }

   inline Vec3<T> operator-=(const Vec3<T> other)
   {
      Vec3<T> tmp (
               this->_x - other._x,
               this->_y - other._y,
               this->_z - other._z
             );
      *this=tmp;
      return tmp;
   }

   inline Vec3<T> operator*=(const T s)
   {
      Vec3<T> tmp (
               this->_x * s,
               this->_y * s,
               this->_z * s
             );
      *this=tmp;
      return tmp;
   }

   inline Vec3<T> operator/=(const T s)
   {
      Vec3<T> tmp (
               this->_x / s,
               this->_y / s,
               this->_z / s
             );
      *this=tmp;
      return tmp;
   }

   inline bool operator<(const Vec3<T> other) const
   {
      for(int i=0; i<3; i++)
      {
         if(this->operator[](i) < other[i]) return true;
         if(this->operator[](i) > other[i]) return false;
      }
      return false;
   }

   inline Vec3<T> min(const Vec3<T> &other) const
   {
      return Vec3<T>(
               std::min(this->_x, other._x),
               std::min(this->_y, other._y),
               std::min(this->_z, other._z)
             );
   }

   inline Vec3<T> max(const Vec3<T> &other) const
   {
      return Vec3<T>(
               std::max(this->_x, other._x),
               std::max(this->_y, other._y),
               std::max(this->_z, other._z)
             );
   }

   inline operator cinolib::vec3<T>() const
   {
      return cinolib::vec3<T>(_x, _y, _z);
   }

};

template<typename T>
Vec3<T> operator*(const double & s, const Vec3<T> & v)
{
    return Vec3<T>(
              s * v.x(),
              s * v.y(),
              s * v.z()
           );
}

template<typename T>
Vec3<T> operator*(const Vec3<T> & v, const double & s)
{
    return Vec3<T>(
              s * v.x(),
              s * v.y(),
              s * v.z()
           );
}

template<typename T>
std::ostream& operator<<(std::ostream & stream, const Vec3<T> & v)
{
    stream << "[ " << v.x() << ", " << v.y() << ", " << v.z() << " ]";
    return stream;
}

typedef Vec3<double> Vec3d;
typedef Vec3<double> Point3d;
typedef Vec3<int>    Vec3i;
typedef Vec3<int>    Point3i;

}

#endif // VEC3_H
