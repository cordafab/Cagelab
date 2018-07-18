#ifndef DRAWABLECAGE_H
#define DRAWABLECAGE_H

#include "drawables/drawableObject.h"
#include "drawables/pickableObject.h"
#include "drawables/pickerController.h"
#include "geom/cage.h"

#include <unordered_set>

class DrawableCage
      : public Cage,
        public DrawableObject,
        public PickableObject
{
public:

   enum
   {
      DRAW_CAGE         = 0x00000001,
      DRAW_VERTICES     = 0x00000002,
      DRAW_WIREFRAME    = 0x00000004,
      DRAW_FRAMES       = 0x00000008
   };

   DrawableCage();
   DrawableCage(const std::vector<double>   & vertices  ,
                const std::vector<int>      & faces     );

   ~DrawableCage();

   void init();
   void clear();

   //DrawableObject interface
   void draw() const;
   void drawWithNames();
   bool sceneCenter(cg3::Vec3d & center) const;
   bool sceneRadius(double & radius) const;

   //skinning flags
   inline bool refreshCharacterPose() const { return _refreshCharacterPose; }
   inline void characterPoseRefreshed() { _refreshCharacterPose = false; }

   //PickableObject interface
   bool getSelectedObjectsBarycenter(cg3::Point3d & barycenter) const;
   void selectObject(const int pickableIndex);
   void deselectObject(const int pickableIndex);

   //Deformation
   void translate (const cg3::Vec3d        & translation);
   void rotate    (const cg3::dQuaternion  & rotation,
                   const cg3::Point3d      & rotationCenter);
   void scale     (const cg3::Point3d      & centerOfScaling,
                   const int                 delta);

   inline const std::vector<bool> & getSelectedVertices() const
      { return isVertexSelected; }

   void activateCageRendering(bool activate);

   void changeCageSphereSize(double val);

protected:

   int drawMode;
   bool _refreshCharacterPose;
   double sphereSize;
   double sphereSizeScaleFactor;

   //technical stuff for picking
   PickerController* pickerController;
   std::map<int,int> pickableIndex2Vertex;
   std::map<int,int> vertex2PickableIndex;
   std::vector<bool> isVertexSelected;
   std::unordered_set<int> selectedVertices;

};


#endif // DRAWABLECAGE_H
