#ifndef DRAWABLETRIMESH_H
#define DRAWABLETRIMESH_H

#include "drawables/drawableObject.h"
#include "geom/trimesh.h"

class DrawableTrimesh
      : public Trimesh,
        public DrawableObject
{
public:

   enum
   {
      DRAW_TRIMESH      = 0x00000001,
      DRAW_VERTICES     = 0x00000002,
      DRAW_FLAT         = 0x00000004,
      DRAW_SMOOTH       = 0x00000008,
      DRAW_WIREFRAME    = 0x00000010,
      DRAW_TEXTURE1D    = 0x00000020
   };

   DrawableTrimesh();
   DrawableTrimesh(const std::vector<double>   & vertices ,
                   const std::vector<int>      & tris   );

   ~DrawableTrimesh();

   void init();
   void clear();

   //DrawableObject interface
   void draw()                             const;
   bool sceneCenter(cg3::Vec3d & center)   const;
   bool sceneRadius(double & radius)       const;

   //Rendering settings
   void activateTrimeshRendering(bool activate);

   void activateSmoothColouration();
   void activateFlatColouration();
   void activateWireframe();
   void activateTexture1D();

   void updateTexture1D(std::vector<float> _textureScalars);

protected:

   int drawMode;

   unsigned int texture_id;
   std::vector<float> textureScalars;

};

#endif // DRAWABLETRIMESH_H
