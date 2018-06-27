#include "characterOperations.h"

#include <vector>

#include "GUI/qtUtils.h"
#include "common/importFiles.h"
#include "common/exportFiles.h"
#include "controller.h"
#include "drawables/drawableCharacter.h"
#include "skinning/cageSkinning.h"
#include "GUI/glCanvas.h"

void loadCharacterFromFile()
{
   std::string filename;
   Controller * c = Controller::get();

   clearCharacter();

   if (openFileSelectionDialog(filename, "Load Character", "3D Meshes (*.off *.obj *.ply)"))
   {
      std::cout << "Loading mesh: " << filename << std::endl;

      std::vector<double> v;
      std::vector<int> f;

      loadMesh(filename.c_str(),v,f);
      DrawableCharacter * character = new DrawableCharacter(v,f);

      c->glCanvas->pushDrawableObject(character);
      c->character = character;
      c->isCharacterLoaded = true;
   }

   updateGUI();

}

void clearCharacter()
{
   Controller * c = Controller::get();

   if(c->isCharacterLoaded)
   {
      c->glCanvas->removeDrawableObject(c->character);
      delete c->character;
      c->character = nullptr;
      c->isCharacterLoaded = false;
   }

   if(c->isCageSkinningInitialized)
   {
      delete c->cageSkinning;
      c->cageSkinning = nullptr;
      c->isCageSkinningInitialized = false;
   }

   updateGUI();

}


void saveCharacterToFile()
{
   std::string filename;
   Controller * c = Controller::get();

   if (openFileSaveDialog(filename, "Save Character", "3D Meshes (*.obj *.ply)"))
   {
      if(c->isCharacterLoaded)
      {
         std::vector<double> v = c->character->getVerticesVector();
         std::vector<int>    f = c->character->getTrianglesVector();

         saveMesh(filename.c_str(), v, f);
      }
   }

   updateGUI();

}
