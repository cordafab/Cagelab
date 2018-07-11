#include "glCanvas.h"

#include <math.h>
#include <algorithm>

#include "controller.h"
#include "drawables/drawableCharacter.h"
#include "drawables/drawableCage.h"

#include "skinning/cageSkinning.h"

#include "common/cageOperations.h"
#include "common/toolsOperation.h"

#include <QMouseEvent>
#include "QGLviewer/camera.h"
#include "GUI/glUtils.h"
#include "Eigen/Eigen"
#include "QGLviewer/vec.h"
#include "geom/plane.h"
#include "math/quaternion.h"
#include "QGLviewer/manipulatedCameraFrame.h"

#include <iostream>
#include <chrono>


GlCanvas::GlCanvas(QWidget *parent)
   : QGLViewer(parent)
{
   init();
}

void GlCanvas::init()
{
   controller = Controller::get();
   pickerController = PickerController::get();

   fitScene();

   controller->interactionMode = CAMERA_INTERACTION;
   previousInteractionMode = CAMERA_INTERACTION;
   restoreInteractionMode = false;

   xPivot = yPivot = zPivot = false;

   isSelectionRectangleActive = false;

   customBackgroundColor.setRgb(255,255,255);

   setFPSIsDisplayed(true);

   camera()->frame()->setSpinningSensitivity(100.0);
}

void GlCanvas::pushDrawableObject(const DrawableObject * object)
{
   drawableObjects.push_back(object);
   fitScene();
   refreshScene();
}

void GlCanvas::removeDrawableObject(const DrawableObject * object)
{
   std::vector<const DrawableObject *>::iterator itr = drawableObjects.begin();
   while (itr != drawableObjects.end()) {
      if (*itr == object) {
         itr = drawableObjects.erase(itr);
      } else {
         ++itr;
      }
   }
   refreshScene();
}

void GlCanvas::pushPickableObject(PickableObject * object)
{
   pickableObjects.push_back(object);
   refreshScene();
}

void GlCanvas::removePickableObject(PickableObject *object)
{
   std::vector<PickableObject *>::iterator itr = pickableObjects.begin();
   while (itr != pickableObjects.end()) {
      if (*itr == object) {
         itr = pickableObjects.erase(itr);
      } else {
         ++itr;
      }
   }
   refreshScene();
}

void GlCanvas::draw()
{
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   setBackgroundColor(customBackgroundColor);

   for(unsigned long i=0; i<drawableObjects.size(); ++i)
   {
      drawableObjects[i]->draw();
   }

   if (isSelectionRectangleActive)
   {
      startScreenCoordinatesSystem();
      drawSelectionRectangle(selectionRectangle.top(),
                             selectionRectangle.bottom(),
                             selectionRectangle.left(),
                             selectionRectangle.right());
      stopScreenCoordinatesSystem();
   }
}

void GlCanvas::drawWithNames()
{
   for(unsigned long i=0; i<pickableObjects.size(); ++i)
   {
      pickableObjects[i]->drawWithNames();
   }
}

void GlCanvas::refreshScene()
{
   updateGL();
}

void GlCanvas::fitScene()
{
   sceneCenter.set(0.0,0.0,0.0);
   sceneRadius = 0.00001;

   int numberOfValidObjectCentroid = 0;

   for(int i=0; i<(int)drawableObjects.size(); ++i)
   {
      const DrawableObject * obj = drawableObjects[i];

      cg3::Vec3d objSceneCenter;
      double objSceneRadius;

      if(i==0)
      {
         if(obj->sceneCenter(objSceneCenter))
         {
            sceneCenter = objSceneCenter;
            numberOfValidObjectCentroid++;
         }
      }
      else
      {
         if(obj->sceneCenter(objSceneCenter))
         {
            sceneCenter += objSceneCenter;
            numberOfValidObjectCentroid++;
         }
      }

      if(obj->sceneRadius(objSceneRadius))
      {
         sceneRadius  = std::max(sceneRadius, objSceneRadius);
      }
   }

   if(numberOfValidObjectCentroid > 1)
   {
      sceneCenter /= (double)numberOfValidObjectCentroid;
   }

   setSceneCenter(qglviewer::Vec(sceneCenter.x(), sceneCenter.y(), sceneCenter.z()));
   setSceneRadius(sceneRadius);

   showEntireScene();
}

void GlCanvas::setInteractionMode(InteractionMode mode, bool quickMode, bool restorePreviousMode)
{

   controller->interactionMode = mode;
   switch(mode)
   {
      case CAMERA_INTERACTION:
         setMouseBinding(Qt::NoModifier, Qt::LeftButton, QGLViewer::CAMERA, QGLViewer::ROTATE);
         setMouseBinding(Qt::NoModifier, Qt::RightButton, QGLViewer::CAMERA, QGLViewer::TRANSLATE);
         //emit disable_none_button();
         //std::cout << "NONE MODE ACTIVATED" << endl;
         if(!quickMode)
         {
            if(!restorePreviousMode) displayMessage("CAMERA MODE ACTIVATED. PRESS H FOR HELP.", 4000);
         } else {
            displayMessage("QUICK CAMERA MODE ACTIVATED. PRESS H FOR HELP.", 2000);
         }
         //updateGL();
         break;
      case SELECT_INTERACTION:
         setMouseBinding(Qt::NoModifier, Qt::LeftButton, QGLViewer::NO_CLICK_ACTION, false, Qt::NoButton);
         setMouseBinding(Qt::NoModifier, Qt::RightButton, QGLViewer::NO_CLICK_ACTION, false, Qt::NoButton);
         //emit disable_add_button();
         //std::cout << "ADD MODE ACTIVATED" << endl;
         if(!quickMode)
         {
            if(!restorePreviousMode) displayMessage("SELECT CAGE VERTEX MODE ACTIVATED. PRESS H FOR HELP.", 4000);
         } else {
            displayMessage("QUICK SELECT CAGE VERTEX MODE ACTIVATED. PRESS H FOR HELP.", 2000);
         }
         //updateGL();
         break;
      case DESELECT_INTERACTION:
         setMouseBinding(Qt::NoModifier, Qt::LeftButton, QGLViewer::NO_CLICK_ACTION, false, Qt::NoButton);
         setMouseBinding(Qt::NoModifier, Qt::RightButton, QGLViewer::NO_CLICK_ACTION, false, Qt::NoButton);
         //emit disable_remove_button();
         //std::cout << "REMOVE MODE ACTIVATED" << endl;
         if(!quickMode)
         {
            if(!restorePreviousMode) displayMessage("DESELECT CAGE VERTEX MODE ACTIVATED. PRESS H FOR HELP.", 4000);
         } else {
            displayMessage("QUICK DESELECT CAGE VERTEX MODE ACTIVATED. PRESS H FOR HELP.", 2000);
         }
         //updateGL();
         break;
      case DEFORM_INTERACTION:   //If is cage skinning activated?
         setMouseBinding(Qt::NoModifier, Qt::LeftButton, QGLViewer::NO_CLICK_ACTION, false, Qt::NoButton);
         setMouseBinding(Qt::NoModifier, Qt::RightButton, QGLViewer::NO_CLICK_ACTION, false, Qt::NoButton);
         //emit disable_deform_button();
         //std::cout << "DEFORM MODE ACTIVATED" << endl;
         if(!quickMode)
         {
            if(!restorePreviousMode) displayMessage("CAGE DEFORMATION MODE ACTIVATED. PRESS H FOR HELP.", 4000);
         } else {
            displayMessage("QUICK CAGE DEFORMATION MODE ACTIVATED. PRESS H FOR HELP.", 2000);
         }
         //updateGL();
         break;
   }
   updateToolsGUI();

}

void GlCanvas::saveCamera()
{
   savedCameraPosition = camera()->position();
   savedCameraOrientation = camera()->orientation();
   savedCameraUpVector = camera()->upVector();
   savedCameraViewDirection = camera()->viewDirection();
}

void GlCanvas::restoreCamera()
{
   camera()->setPosition(savedCameraPosition);
   camera()->setOrientation(savedCameraOrientation);
   camera()->setUpVector(savedCameraUpVector);
   camera()->setViewDirection(savedCameraViewDirection);
   updateGL();
}

// Customized mouse events
void GlCanvas::mousePressEvent(QMouseEvent* e)
{
   if ( e->modifiers()==Qt::ShiftModifier ){
      previousInteractionMode = controller->interactionMode;
      restoreInteractionMode = true;
      setInteractionMode(SELECT_INTERACTION, true);
      } else
   if ( e->modifiers()==Qt::AltModifier ){
      previousInteractionMode = controller->interactionMode;
      restoreInteractionMode = true;
      setInteractionMode(DESELECT_INTERACTION, true);
      } else
   if ( e->modifiers()==Qt::ControlModifier ){
      previousInteractionMode = controller->interactionMode;
      restoreInteractionMode = true;
      setInteractionMode(DEFORM_INTERACTION, true);
   }

   if ((controller->interactionMode == SELECT_INTERACTION) || (controller->interactionMode == DESELECT_INTERACTION))
   {
      selectionRectangle = QRect(e->pos(), e->pos());
      isSelectionRectangleActive = true;
      } else
   if (controller->interactionMode == DEFORM_INTERACTION)
   {
      //ClickConverter Initialization
      qglviewer::Vec qglCameraPosition = camera()->position();
      qglviewer::Vec qglCameraDirection = camera()->viewDirection();
      qglviewer::Vec qglCameraUp = camera()->upVector();
      cg3::Vec3d cameraPosition(qglCameraPosition.x, qglCameraPosition.y, qglCameraPosition.z);
      cg3::Vec3d cameraDirection(qglCameraDirection.x, qglCameraDirection.y, qglCameraDirection.z);
      cg3::Vec3d cameraUp(qglCameraUp.x, qglCameraUp.y, qglCameraUp.z);
      GLfloat projectionMatrix[16];
      GLfloat viewMatrix[16];
      camera()->getProjectionMatrix(projectionMatrix);
      camera()->getModelViewMatrix(viewMatrix);
      clickConverter.init(e->x(),
                          e->y(),
                          cameraPosition,
                          cameraDirection,
                          cameraUp,
                          sceneCenter,
                          projectionMatrix,
                          viewMatrix,
                          width(),
                          height());

      if (e->buttons() & Qt::RightButton)
      {

      } else
      if (e->buttons() & Qt::LeftButton)
      {
         computeCenterOfRotation();
      }
   }
   else
      QGLViewer::mousePressEvent(e);
}

void GlCanvas::mouseMoveEvent(QMouseEvent* e)
{
   if ((controller->interactionMode == SELECT_INTERACTION) || (controller->interactionMode == DESELECT_INTERACTION))
   {
      selectionRectangle.setBottomRight(e->pos());
      updateGL();
      } else
   if ( controller->interactionMode == DEFORM_INTERACTION )
   {

      if (e->buttons() & Qt::RightButton)
      {
         clickConverter.updateMouseMovement(e->x(),e->y());
         computePickableObjectsTranslation();
      } else
      if (e->buttons() & Qt::LeftButton)
      {
         clickConverter.updateMouseMovement(e->x(),e->y());
         computePickableObjectsRotation();
      }

      if(controller->isCageSkinningInitialized &&
         controller->cage->refreshCharacterPose())
      {
         controller->cageSkinning->deform();
         controller->cage->updateNormals();
         //controller->cage->characterPoseRefreshed();
      }
      updateGL();
   }
   else
      QGLViewer::mouseMoveEvent(e);
}

void GlCanvas::mouseReleaseEvent(QMouseEvent* e)
{
   if ((controller->interactionMode == SELECT_INTERACTION) || (controller->interactionMode == DESELECT_INTERACTION))
   {
      selectionRectangle = selectionRectangle.normalized();
      int width = selectionRectangle.width();
      if(width>1)
          setSelectRegionWidth(width);
      else
          setSelectRegionWidth(1);
      int height = selectionRectangle.height();
      if(height>1)
          setSelectRegionHeight(height);
      else
          setSelectRegionHeight(1);
      select(selectionRectangle.center());
      isSelectionRectangleActive = false;
      updateGL();
   }
   else if (controller->interactionMode==DEFORM_INTERACTION)
   {
      if(controller->isCageSkinningInitialized &&
            controller->cage->refreshCharacterPose())
      {

         controller->cage->characterPoseRefreshed();
         //controller->character->updateNormals();
      }
      updateGL();
   }

   if(restoreInteractionMode)
   {
      restoreInteractionMode = false;
      setInteractionMode(previousInteractionMode, false, true);
   }

   QGLViewer::mouseReleaseEvent(e);
}

void GlCanvas::wheelEvent(QWheelEvent *e)
{
   if(e->modifiers()==Qt::ControlModifier)
   {
      previousInteractionMode = controller->interactionMode;
      restoreInteractionMode = true;
      setInteractionMode(DEFORM_INTERACTION, true);
   }

   if(controller->interactionMode==DEFORM_INTERACTION)
   {
      if(controller->isCageSkinningInitialized)
      {
         computeCenterOfRotation();
         computePickableObjectsScaling(e->delta());
         controller->cageSkinning->deform();
         controller->cage->characterPoseRefreshed();
         updateGL();
      }

      if(restoreInteractionMode)
      {
         restoreInteractionMode = false;
         setInteractionMode(previousInteractionMode, false, true);
      }
   }
   else
      QGLViewer::wheelEvent(e);
}

void GlCanvas::keyPressEvent(QKeyEvent *e)
{
   switch (e->key())
   {
      case Qt::Key_1:
         setInteractionMode(CAMERA_INTERACTION);
         break;
      case Qt::Key_2:
         setInteractionMode(SELECT_INTERACTION);
         break;
      case Qt::Key_3:
         setInteractionMode(DESELECT_INTERACTION);
         break;
      case Qt::Key_4:
         setInteractionMode(DEFORM_INTERACTION);
         break;
      case Qt::Key_X:
         xPivot = !xPivot;
         yPivot = zPivot = false;
         break;
      case Qt::Key_Y:
         yPivot = !yPivot;
         xPivot = zPivot = false;
         break;
      case Qt::Key_Z:
         zPivot = !zPivot;
         xPivot = yPivot = false;
         break;
      default:
         QGLViewer::keyPressEvent(e);
   }
}


//Selection
void GlCanvas::endSelection(const QPoint&)
{
   glFlush();
   GLint nbHits = glRenderMode(GL_RENDER);
   if (nbHits > 0)
   {
      // (selectBuffer())[4*i+3] is the id pushed on the stack.
      for (int i=0; i<nbHits; ++i)
      {
         int pickedIndex = (selectBuffer())[4*i+3];
         switch(controller->interactionMode)
         {
            case SELECT_INTERACTION:
               pickerController->getObject(pickedIndex)->selectObject(pickedIndex);
               break;
            case DESELECT_INTERACTION:
               pickerController->getObject(pickedIndex)->deselectObject(pickedIndex);
               break;
            default: break;
         }
      }

      if(controller->interactionMode==SELECT_INTERACTION || controller->interactionMode==DESELECT_INTERACTION){
         if(controller->isCageWeightsRenderActive)
            updateCageInfluenceTexture();
      }
   }
}

//Valuta se eliminarlo. Ora il calcolo del centro di rotazione è ridondante all'interno di DrawableCage
bool GlCanvas::computeCenterOfRotation()
{
   std::vector<cg3::Point3d> selectedObjectsBarycenters;

   for(unsigned long i=0; i<pickableObjects.size(); ++i)
   {
      cg3::Point3d barycenter;
      if(pickableObjects[i]->getSelectedObjectsBarycenter(barycenter))
      {
         selectedObjectsBarycenters.push_back(barycenter);
      }
   }

   int numberOfBarycenters = (int)selectedObjectsBarycenters.size();

   for(int i=0; i<numberOfBarycenters; ++i)
   {
      if(i==0)
         rotationCenter = selectedObjectsBarycenters[0];
      else
         rotationCenter += selectedObjectsBarycenters[i];
   }

   if(numberOfBarycenters)
   {
      rotationCenter /= (double)numberOfBarycenters;
      return true;
   }

   return false;
}

//Deformation of selected objects
void GlCanvas::computePickableObjectsTranslation()
{
   cg3::Vec3d delta;
   clickConverter.getTranslation(delta, xPivot, yPivot, zPivot);

   for(unsigned long i=0; i<pickableObjects.size(); ++i)
   {
      pickableObjects[i]->translate(delta);
   }
}

void GlCanvas::computePickableObjectsRotation()
{
   cg3::dQuaternion rotation;
   clickConverter.getRotation(rotation, rotationAxis, sceneRadius, xPivot, yPivot, zPivot);  //TODO: Riscrivi per cg3::Transform

   for(unsigned long i=0; i<pickableObjects.size(); ++i)
   {
      pickableObjects[i]->rotate(rotation, rotationCenter);
      //cg3::Transform transformRotation(rotation);
      //pickableObjects[i]->rotate(transformRotation, rotationCenter);
   }
}

void GlCanvas::computePickableObjectsScaling(int direction)
{
   for(unsigned long i=0; i<pickableObjects.size(); ++i)
   {
      pickableObjects[i]->scale(rotationCenter, direction);
   }
}
