#include "glUtils.h"

#ifdef __APPLE__
#include <gl.h>
#include <glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <vector>

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

void drawCube(cg3::Vec3d center, double radius, float r, float g, float b, bool wireframe)
{
   std::vector<double> vertices
   {
       1, 1,-1,
      -1,-1,-1,
      -1, 1,-1,
       1, 1, 1,
      -1,-1, 1,
       1,-1, 1,
       1, 1,-1,
       1,-1, 1,
       1,-1,-1,
       1,-1,-1,
      -1,-1, 1,
      -1,-1,-1,
      -1,-1,-1,
      -1, 1, 1,
      -1, 1,-1,
       1, 1, 1,
      -1, 1,-1,
      -1, 1, 1,
       1, 1,-1,
       1,-1,-1,
      -1,-1,-1,
       1, 1, 1,
      -1, 1, 1,
      -1,-1, 1,
       1, 1,-1,
       1, 1, 1,
       1,-1, 1,
       1,-1,-1,
       1,-1, 1,
      -1,-1, 1,
      -1,-1,-1,
      -1,-1, 1,
      -1, 1, 1,
       1, 1, 1,
       1, 1,-1,
      -1, 1,-1
   };

   std::vector<int> tris
   {
       0, 1, 2,
       3, 4, 5,
       6, 7, 8,
       9,10,11,
      12,13,14,
      15,16,17,
      18,19,20,
      21,22,23,
      24,25,26,
      27,28,29,
      30,31,32,
      33,34,35
   };

   std::vector<double> normals
   {
       0, 0,-1,
       0, 0,-1,
       0, 0,-1,
       0, 0, 1,
       0, 0, 1,
       0, 0, 1,
       1, 0, 0,
       1, 0, 0,
       1, 0, 0,
       0,-1, 0,
       0,-1, 0,
       0,-1, 0,
      -1, 0, 0,
      -1, 0, 0,
      -1, 0, 0,
       0, 1, 0,
       0, 1, 0,
       0, 1, 0,
       0, 0,-1,
       0, 0,-1,
       0, 0,-1,
       0, 0, 1,
       0, 0, 1,
       0, 0, 1,
       1, 0, 0,
       1, 0, 0,
       1, 0, 0,
       0,-1, 0,
       0,-1, 0,
       0,-1, 0,
      -1, 0, 0,
      -1, 0, 0,
      -1, 0, 0,
       0, 1, 0,
       0, 1, 0,
       0, 1, 0
   };

   if(wireframe)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glDisable(GL_LIGHTING);
      glShadeModel(GL_FLAT);
      glLineWidth(1.0);
   }
   else
   {
      glEnable(GL_LIGHTING);
      glShadeModel(GL_SMOOTH);
   }
   glPushMatrix();
   glTranslated(center.x(), center.y(), center.z());
   glScaled(radius, radius, radius);
   glColor3f(r,g,b);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   glVertexPointer(3, GL_DOUBLE, 0, vertices.data());
   glNormalPointer(GL_DOUBLE, 0, normals.data());
   glDrawElements(GL_TRIANGLES, tris.size(), GL_UNSIGNED_INT, tris.data());
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glPopMatrix();
   if(wireframe)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glEnable(GL_LIGHTING);
   }
}

void drawDiamond(cg3::Vec3d center, double radius, float r, float g, float b, bool wireframe)
{
   std::vector<double> vertices
   {
       0, 1, 0,
       0, 0, 1,
       1, 0, 0,

       0, 1, 0,
       1, 0, 0,
       0, 0,-1,

       0, 1, 0,
       0, 0,-1,
      -1, 0, 0,

       0, 1, 0,
      -1, 0, 0,
       0, 0, 1,

       0,-1, 0,
       0, 0, 1,
      -1, 0, 0,

       0,-1, 0,
       1, 0, 0,
       0, 0, 1,

       0,-1, 0,
       0, 0,-1,
       1, 0, 0,

       0,-1, 0,
      -1, 0, 0,
       0, 0,-1
   };

   std::vector<int> tris
   {
       0, 1, 2,
       3, 4, 5,
       6, 7, 8,
       9,10,11,
      12,13,14,
      15,16,17,
      18,19,20,
      21,22,23,
   };

   if(wireframe)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glDisable(GL_LIGHTING);
      glShadeModel(GL_FLAT);
      glLineWidth(2.0);
   }
   else
   {
      glEnable(GL_LIGHTING);
      glShadeModel(GL_SMOOTH);
   }
   glPushMatrix();
   glTranslated(center.x(), center.y(), center.z());
   glScaled(radius, radius, radius);
   glColor3f(r,g,b);
   glEnableClientState(GL_VERTEX_ARRAY);
   //glEnableClientState(GL_NORMAL_ARRAY);
   glVertexPointer(3, GL_DOUBLE, 0, vertices.data());
   //glNormalPointer(GL_DOUBLE, 0, normals.data());
   glDrawElements(GL_TRIANGLES, tris.size(), GL_UNSIGNED_INT, tris.data());
   //glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glPopMatrix();
   if(wireframe)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glEnable(GL_LIGHTING);
   }
}

void drawSphere(cg3::Vec3d center, double radius, float r, float g, float b, bool wireframe)
{
   if(wireframe)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glDisable(GL_LIGHTING);
      glShadeModel(GL_FLAT);
      glLineWidth(1.0);
   }
   else
   {
      glEnable(GL_LIGHTING);
      glShadeModel(GL_SMOOTH);
   }

   glPushMatrix();
   glTranslated(center.x(), center.y(), center.z());
   glColor3f(r, g, b);
   GLUquadric *sphere = gluNewQuadric();
   gluQuadricOrientation(sphere,GLU_OUTSIDE);
   gluSphere(sphere, radius, 20, 20);
   gluDeleteQuadric(sphere);
   glPopMatrix();
   if(wireframe)
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glEnable(GL_LIGHTING);
   }
}

void drawRay(cg3::dRay ray)
{
   cg3::Point3d origin;
   cg3::Point3d pointOnRay;

   origin = ray.origin();
   pointOnRay = ray.getPointOnRay(250000.0);

   glBegin(GL_LINES);
   glColor3f(1.0f, 0.0f, 0.0f);
   glVertex3d(origin.x(), origin.y(), origin.z());
   glVertex3d(pointOnRay.x(), pointOnRay.y(), pointOnRay.z());
   glEnd();
}

void drawPlane(cg3::dPlane plane)
{
   cg3::Point3d origin;
   cg3::Point3d pointOnRay;

   //origin = ray.origin();
   //pointOnRay = ray.getPointOnRay(250000.0);

   /*glBegin(GL_LINES);
   glColor3f(1.0f, 0.0f, 0.0f);
   glVertex3d(origin.x(), origin.y(), origin.z());
   glVertex3d(pointOnRay.x(), pointOnRay.y(), pointOnRay.z());
   glEnd();*/
}

void drawSelectionRectangle(int top, int bottom, int left, int right)
{
   //This function operates in screen coordinates space!
   glDisable(GL_LIGHTING);
   //glEnable(GL_BLEND);

   glColor4f(0.0, 0.0, 0.3f, 0.2f);
   glBegin(GL_QUADS);
   glVertex2i(left,  top);
   glVertex2i(right, top);
   glVertex2i(right, bottom);
   glVertex2i(left, bottom);
   glEnd();

   //glDisable(GL_BLEND);

   glLineWidth(2.0);
   glColor4f(0.2f, 0.2f, 0.2f, 0.7f);
   glBegin(GL_LINE_LOOP);
   glVertex2i(left, top);
   glVertex2i(right, top);
   glVertex2i(right, bottom);
   glVertex2i(left, bottom);
   glEnd();

   glEnable(GL_LIGHTING);
}
