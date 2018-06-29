#include "fbxOperations.h"

#include <vector>

#include "GUI/qtUtils.h"
#include "common/ioFBX.h"
#include "common/characterOperations.h"
#include "common/cageOperations.h"
#include "controller.h"
#include "drawables/drawableCharacter.h"
#include "GUI/glCanvas.h"
#include "skinning/cageSkinning.h"
#include "skinning/meanValueCoordinates.h"
#include "skinning/greenCoordinates.h"

void loadFbxFromFile()
{
   std::string filename;
   Controller * c = Controller::get();

   clearFbx();

   if (openFileSelectionDialog(filename, "Load FBX File", "FBX File (*.fbx)"))
   {
      std::cout << "Loading FBX File: " << filename << std::endl;
      ioFBX fbxImporter(filename.c_str());

      //Load Character Trimesh
      DrawableCharacter * character = nullptr;

      if(fbxImporter.loadCharacter(character,"Character"))
      {
         c->glCanvas->pushDrawableObject(character);
         c->character = character;
         c->isCharacterLoaded = true;
      }

      //Load Character Cage
      DrawableCage * cage = nullptr;

      if(fbxImporter.loadCage(cage,"Cage"))
      {
         c->glCanvas->pushDrawableObject(cage);
         c->glCanvas->pushPickableObject(cage);
         c->cage = cage;
         c->isCageLoaded = true;

         //Compute Cage Weights
         if(c->isCharacterLoaded)
         {
            /*
            MeanValueCoordinates * mvc = new MeanValueCoordinates(c->character,
                                                                  c->cage);
            c->cageSkinning = mvc;
            c->cageWeights = mvc->getWeights();
            c->areCageWeightsLoaded = true;
            c->isCageSkinningInitialized = true;
            c->isCageDeformerActive = true;
            */

            GreenCoordinates * gc = new GreenCoordinates(c->character,
                                                         c->cage);

            if(gc->generateCoords())
            {
               c->cageWeights  = gc->getWeights();
               c->cageSkinning = gc;

               c->areCageWeightsLoaded = true;
               c->isCageSkinningInitialized = true;
               c->isCageDeformerActive = true;
            }
            else
            {
               delete gc;
            }
         }
      }
   }

   updateGUI();

}

void clearFbx()
{
   clearCharacter();
   clearCage();
   updateGUI();

}
