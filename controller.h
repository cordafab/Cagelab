#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

//Forward declarations
class DrawableCharacter;
class DrawableCage;

class DrawableObject;

class Weights;
class CageSkinning;
class NoCageSkinning;
class MeanValueCoordinates;
class GreenCoordinates;

class Animator;

class GlCanvas;
class FbxImportPanel;
class CharacterPanel;
class CagePanel;
class ToolsPanel;

//Interaction mode
enum InteractionMode {
   CAMERA_INTERACTION,
   SELECT_INTERACTION,
   DESELECT_INTERACTION,
   DEFORM_INTERACTION
};

class Controller
{
public:

   static Controller* get();

   //Data
   DrawableCharacter    * character;
   DrawableCage         * cage;

   bool                   isCharacterLoaded;
   bool                   isCageLoaded;

   //Skinning
   Weights              * cageWeights;
   CageSkinning         * cageSkinning;

   NoCageSkinning       * nc;
   MeanValueCoordinates * mvc;
   GreenCoordinates     * gc;

   bool                   areCageWeightsLoaded;
   bool                   isCageSkinningInitialized;
   bool                   isCageWeightsRenderActive;
   bool                   isCageDeformerActive;

   Animator             * animator;

   bool                   isAnimatorInitialized;

   //GUI
   GlCanvas             * glCanvas;
   FbxImportPanel       * fbxImportPanel;
   CharacterPanel       * characterPanel;
   CagePanel            * cagePanel;
   ToolsPanel           * toolsPanel;

   //Interaction
   InteractionMode        interactionMode;

   ~Controller();

protected:

   Controller();

private:

   static Controller * instance;

};

#endif // CONTROLLER_H
