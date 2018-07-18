#include "drawableCage.h"

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

#include "GUI/glUtils.h"
#include <vector>

//DEBUG FOR FRAME FLIP
//#include "cinolib/simplicial_map.h"
//#include "cinolib/matrix.h"


DrawableCage::DrawableCage()
   : Cage()
{
   init();
}

DrawableCage::DrawableCage(const std::vector<double>   & vertices ,
                           const std::vector<int>    & tris     )
   : Cage(vertices, tris)
{
   init();
}

DrawableCage::~DrawableCage()
{
   for(int i=0; i<getNumVertices(); ++i)
   {
      pickerController->removeIndex(vertex2PickableIndex[i]);
   }

}

void DrawableCage::init()
{
   type           = CAGE;
   drawMode       = DRAW_CAGE | DRAW_VERTICES  | DRAW_WIREFRAME ;//| DRAW_FRAMES;

   //initialize selectedVertices vector with false (all deselected)
   isVertexSelected.resize(getNumVertices(), false);

   pickerController = PickerController::get();

   //assign PickableIndexes to every vertex
   for(int i=0; i<getNumVertices(); ++i)
   {
      int pickableIndex = pickerController->generateIndex(this);
      pickableIndex2Vertex[pickableIndex] = i;
      vertex2PickableIndex[i] = pickableIndex;
   }

   sphereSize = boundingBox.diagonal()/200.0;
   sphereSizeScaleFactor = 0.0;
}

void DrawableCage::clear()
{
   Cage::clear();
}

void DrawableCage::draw() const
{
   if (drawMode & DRAW_CAGE)
   {
      if (drawMode & DRAW_WIREFRAME)
      {
         glDisable(GL_LIGHTING);
         glShadeModel(GL_FLAT);
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         glEnableClientState(GL_VERTEX_ARRAY);
         glVertexPointer(3, GL_DOUBLE, 0, vertices.data());

         //glLineWidth(3.0);
         //glColor3f(0.99, 0.85, 0.39);
         glLineWidth(0.2);
         glColor4f(0,0,0,0.1);
         glDrawElements(GL_TRIANGLES, tris.size(), GL_UNSIGNED_INT, tris.data());

         glDisableClientState(GL_VERTEX_ARRAY);
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }


      //double radius = boundingBox.diagonal()/150.0;

      if(drawMode & DRAW_VERTICES)
      {
         for(int i=0; i<getNumVertices(); ++i)
         {
            if (isVertexSelected[i])
               drawSphere(getVertex(i),
                          sphereSize + sphereSize * sphereSizeScaleFactor,
                          0.905, 0.305, 0.305);
            else
               drawSphere(getVertex(i),
                          sphereSize + sphereSize * sphereSizeScaleFactor,
                          0.5, 0.5, 0.5);
               //drawSphere(getVertex(i), radius, 0.99, 0.85, 0.39);
         }
      }

      //create a drawFrame fuction in glUtils
      if (drawMode & DRAW_FRAMES)
      {
         /*double length = boundingBox.diagonal()/50.0;
         for(int i=0; i<getNumVertices(); ++i)
         {
            cg3::Vec3d p = f.o();
            cg3::Vec3d s;

            glDisable(GL_LIGHTING);
            glShadeModel(GL_FLAT);
            glBegin(GL_LINES);
            s = p + (f.u()*length);
            glColor3f(1.0,0.0,0.0);
            glVertex3f(p.x(), p.y(), p.z());
            glVertex3f(s.x(), s.y(), s.z());
            s = p + (f.v()*length);
            glColor3f(0.0,1.0,0.0);
            glVertex3f(p.x(), p.y(), p.z());
            glVertex3f(s.x(), s.y(), s.z());
            s = p + (f.w()*length);
            glColor3f(0.0,0.0,1.0);
            glVertex3f(p.x(), p.y(), p.z());
            glVertex3f(s.x(), s.y(), s.z());
            glEnd();
         }*/
      }
   }
}

void DrawableCage::drawWithNames()
{
   double radius = boundingBox.diagonal()/200.0;

   if(drawMode & DRAW_VERTICES){
      for(int i=0; i<getNumVertices(); ++i)
      {
         glPushMatrix();
         glPushName(vertex2PickableIndex[i]);
         drawSphere(getVertex(i),
                    sphereSize + sphereSize * sphereSizeScaleFactor,
                    0.0, 0.0, 1.0);
         glPopName();
         glPopMatrix();
      }
   }
}

bool DrawableCage::sceneCenter(cg3::Vec3d & center) const
{
   center = boundingBox.center();
   return true;   //center is a valid value
}

bool DrawableCage::sceneRadius(double & radius) const
{
   radius = boundingBox.diagonal();
   return true;   //center is a valid value
}

bool DrawableCage::getSelectedObjectsBarycenter(cg3::Point3d & barycenter) const
{
   std::vector<cg3::Point3d> selectedVerticesPositions;

   for(int i=0; i<getNumVertices(); ++i)
   {
      if(isVertexSelected[i])
      {
         selectedVerticesPositions.push_back(getVertex(i));
      }
   }

   int numberOfSelectedVertices = (int)selectedVerticesPositions.size();

   for(int i=0; i<numberOfSelectedVertices; ++i)
   {
      if(i==0)
         barycenter = selectedVerticesPositions[0];
      else
         barycenter += selectedVerticesPositions[i];
   }

   if(numberOfSelectedVertices)
   {
      barycenter /= (double)numberOfSelectedVertices;
      return true;
   }

   return false;
}

void DrawableCage::selectObject(const int pickableIndex)
{
   int vertexIndex = pickableIndex2Vertex[pickableIndex];
   isVertexSelected[vertexIndex] = true;
   selectedVertices.insert(vertexIndex);
}

void DrawableCage::deselectObject(const int pickableIndex)
{
   int vertexIndex = pickableIndex2Vertex[pickableIndex];
   isVertexSelected[vertexIndex] = false;
   selectedVertices.erase(vertexIndex);
}

//Deformation
void DrawableCage::translate(const cg3::Vec3d & translation)
{
   //cg3::Vec3d tr(0.1,0.0,0.0);
   if(activateTransformation)
   {
      for(int i=0; i<getNumVertices(); ++i)
      {
         if(isVertexSelected[i])
         {
            cg3::Vec3d deformedPose = getVertex(i);
            cg3::Vec3d newPose = deformedPose + translation;
            setVertex(i,newPose);  
            _refreshCharacterPose = true;
         }
      }
   }

}

void DrawableCage::rotate(const cg3::dQuaternion & rotation,
                          const cg3::Point3d &rotationCenter)
{
   if(activateTransformation)
   {
      //cg3::Transform rotationMatrix(rotation);

      /*//Barycenter computation
      cg3::Point3d restRotationCenter;
      int numberOfSelectedVertices=0;
      for(int i=0; i<getNumVertices(); ++i)
      {
         if(isVertexSelected[i])
         {
            restRotationCenter+=getRestPoseVertex(i);
            ++numberOfSelectedVertices;
         }
      }
      if(numberOfSelectedVertices)
      {
         restRotationCenter /= (double)numberOfSelectedVertices;
      }*/


      for(int i=0; i<getNumVertices(); ++i)
      {
         if(isVertexSelected[i])
         {
            cg3::Point3d pose = getVertex(i);
            //rotate the position

            cg3::Point3d newPose = rotation.applyRotation(pose - rotationCenter);
            //restore position
            newPose += rotationCenter;
            setVertex(i,newPose);
            _refreshCharacterPose = true;
         }
      }
   }
}

void DrawableCage::scale(const cg3::Point3d & centerOfScaling,
                         const int delta)
{
   if(activateTransformation)
   {
      for(int i=0; i<getNumVertices(); ++i)
      {
         if(isVertexSelected[i])
         {
            cg3::Point3d pos = getVertex(i);
            cg3::Vec3d dir = centerOfScaling - pos;
            dir *=0.01;

            if(delta<0)
            {
               setVertex(i,pos-dir);         
            }
            else
            {
               setVertex(i,pos+dir);
            }

            _refreshCharacterPose = true;
         }
      }
   }
}

void DrawableCage::activateCageRendering(bool activate)
{
   if (activate)  drawMode |=  DRAW_CAGE;
   else           drawMode &= ~DRAW_CAGE;
}

void DrawableCage::changeCageSphereSize(double val)
{
   sphereSizeScaleFactor = val;
}
