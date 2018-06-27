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

   void pushDrawableObject(const DrawableObject * object);
   void removeDrawableObject(const DrawableObject * object);

   void pushPickableObject(PickableObject *object);
   void removePickableObject(PickableObject *object);

   void refreshScene();
   void fitScene();

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

   enum InteractionMode { CAMERA, SELECT, DESELECT, DEFORM };
   InteractionMode interactionMode;

   void init();

   QColor customBackgroundColor;

   //Mouse Customization
   void mousePressEvent(QMouseEvent *e);
   void mouseMoveEvent(QMouseEvent *e);
   void mouseReleaseEvent(QMouseEvent *e);
   void wheelEvent(QWheelEvent *e);

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

   //Deformation of selected objects
   void computePickableObjectsTranslation();
   void computePickableObjectsRotation();
   void computePickableObjectsScaling(int direction);

   //Utilities for Camera saving
   qglviewer::Vec savedCameraPosition;
   qglviewer::Quaternion savedCameraOrientation;
   qglviewer::Vec savedCameraUpVector;
   qglviewer::Vec savedCameraViewDirection;

   //Experimental stuffz
};

#endif // GLCANVAS_H
