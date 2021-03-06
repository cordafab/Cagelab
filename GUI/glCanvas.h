#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <QGLViewer/qglviewer.h>
#include "glm/glm.hpp"

#include "controller.h"

#include "drawables/pickerController.h"

#include "geom/vec3.h"
#include "geom/ray.h"
#include "geom/plane.h"

#include "GUI/clickConverter.h"

class GlCanvas
      : public QGLViewer
{
public :

   GlCanvas(QWidget * parent);

   void draw();
   void drawWithNames();

   void animate();

   void pushDrawableObject(const DrawableObject * object);
   void removeDrawableObject(const DrawableObject * object);

   void pushPickableObject(PickableObject *object);
   void removePickableObject(PickableObject *object);

   void refreshScene();
   void fitScene();

   void setInteractionMode(InteractionMode mode, bool quickMode=false, bool restorePreviousMode=false);

   //Utilities for Camera saving
   void saveCamera();
   void restoreCamera();



protected :

   Controller * controller;
   PickerController * pickerController;

   std::vector<const DrawableObject *> drawableObjects;
   std::vector<PickableObject *> pickableObjects;

   cg3::Vec3d sceneCenter;
   double sceneRadius;

   void init();

   QColor customBackgroundColor;

   //Mouse Customization
   void mousePressEvent(QMouseEvent *e);
   void mouseMoveEvent(QMouseEvent *e);
   void mouseReleaseEvent(QMouseEvent *e);
   void wheelEvent(QWheelEvent *e);

   //Keyboard Customization
   void keyPressEvent(QKeyEvent *e);

   //Selection
   void endSelection(const QPoint &);

   //Stuff for the selection rectangle
   QRect selectionRectangle;
   bool isSelectionRectangleActive;

   //Stuff for mouse spatial interaction
   ClickConverter clickConverter;

   //Utilities for rotations
   cg3::Point3d rotationCenter;
   cg3::Vec3d rotationAxis;
   bool computeCenterOfRotation();

   //Stuff for interactionModes
   InteractionMode previousInteractionMode;
   bool restoreInteractionMode;

   //Deformation of selected objects
   void computePickableObjectsTranslation();
   void computePickableObjectsRotation();
   void computePickableObjectsScaling(int direction);

   //Things for axis pivoting
   bool xPivot;
   bool yPivot;
   bool zPivot;

   //Utilities for Camera saving
   qglviewer::Vec savedCameraPosition;
   qglviewer::Quaternion savedCameraOrientation;
   qglviewer::Vec savedCameraUpVector;
   qglviewer::Vec savedCameraViewDirection;

   //Experimental stuffz
};

#endif // GLCANVAS_H
