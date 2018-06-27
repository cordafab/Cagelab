#ifndef IOFBX_H
#define IOFBX_H

#include "drawables/drawableCharacter.h"
#include "drawables/drawableCage.h"

#include "skinning/weights.h"

#include "fbxsdk.h"
#include "fbxsdk/fileio/fbxiosettings.h"


class ioFBX
{
public:
   ioFBX(const char * filename);
   ~ioFBX();
   bool loadCharacter(DrawableCharacter * & character, const char * name);
   bool loadCage(DrawableCage * & cage, const char * name);


private:

   const char * file;
   bool error;

   FbxManager * lSdkManager;
   FbxIOSettings * ios;
   FbxScene * lScene;

   void init();

   cg3::Transform fromFbxMatrixToTransform(const FbxAMatrix & matrix);
};

#endif // IOFBX_H
