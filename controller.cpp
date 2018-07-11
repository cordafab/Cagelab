#include "controller.h"

Controller::Controller()
{
   character                        = nullptr;
   cage                             = nullptr;

   isCharacterLoaded                = false;
   isCageLoaded                     = false;

   cageWeights                      = nullptr;
   cageSkinning                     = nullptr;
   nc                               = nullptr;
   mvc                              = nullptr;
   gc                               = nullptr;

   areCageWeightsLoaded             = false;
   isCageSkinningInitialized        = false;
   isCageWeightsRenderActive        = false;
   isCageDeformerActive             = false;



   glCanvas                         = nullptr;
   fbxImportPanel                   = nullptr;
   characterPanel                   = nullptr;
   cagePanel                        = nullptr;
   toolsPanel                       = nullptr;

   interactionMode                  = CAMERA_INTERACTION;
}

Controller::~Controller()
{
   /*delete trimesh;
   delete cage;


   delete cageWeights;
   delete cageSkinning;

   delete glCanvas;
   delete fbxImportManager;
   delete cageManager;*/
}

Controller* Controller::instance = 0;

Controller* Controller::get()
{
    if (instance == 0)
        instance = new Controller;
    return instance;
}
