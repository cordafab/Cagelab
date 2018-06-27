#ifndef GLUTILS_H
#define GLUTILS_H

#include "geom/vec3.h"
#include "geom/ray.h"
#include "geom/plane.h"
#include "common/types.h"

void drawCube(cg3::Vec3d center, double radius, float r, float g, float b, bool wireframe=false);
void drawDiamond(cg3::Vec3d center, double radius, float r, float g, float b, bool wireframe=false);
void drawSphere(cg3::Vec3d center, double radius, float r, float g, float b, bool wireframe=false);
void drawRay(cg3::dRay ray);
void drawPlane(cg3::dPlane plane);
void drawSelectionRectangle(int top, int bottom, int left, int right);


#endif // GLUTILS_H
