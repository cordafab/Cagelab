#ifndef CLICKCONVERTER_H
#define CLICKCONVERTER_H

#include "geom/vec3.h"
#include "math/quaternion.h"
#include "geom/ray.h"
#include "geom/plane.h"

class ClickConverter
{
public:
   ClickConverter();
   void init(const int mouseX,
             const int mouseY,
             const cg3::Point3d & cameraPosition,
             const cg3::Vec3d & cameraDirection,
             const cg3::Point3d & sceneCenter,
             const float projectionMatrix[],
             const float viewMatrix[],
             const int windowsWidth,
             const int windowsHeight);
   void updateMouseMovement(const int mouseX, const int mouseY);
   void getTranslation(cg3::Vec3d & translation);
   void getRotation(cg3::dQuaternion & rotation,
                    cg3::Vec3d & rotationAxis,
                    const double scaleFactor);
   void generateRay(const int mouseX, const int mouseY, cg3::dRay &ray) const;

private:
   int _previousMouseX;
   int _previousMouseY;
   int _actualMouseX;
   int _actualMouseY;
   cg3::Vec3d _cameraPosition;
   cg3::Vec3d _cameraDirection;
   float _projectionMatrix[16];
   float _viewMatrix[16];
   int _windowsWidth;
   int _windowsHeight;
   cg3::dPlane midPlane;
   cg3::dRay previousClickRay;
   cg3::dRay actualClickRay;
};

#endif // CLICKCONVERTER_H
