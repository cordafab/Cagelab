#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

//Forward declarations
class DrawableCharacter;
class DrawableCage;

class DrawableObject;

class Weights;
class CageSkinning;

class GlCanvas;
class FbxImportPanel;
class CharacterPanel;
class CagePanel;
class ToolsPanel;

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

   bool                   areCageWeightsLoaded;
   bool                   isCageSkinningInitialized;
   bool                   isCageWeightsRenderActive;
   bool                   isCageDeformerActive;

   //GUI
   GlCanvas             * glCanvas;
   FbxImportPanel       * fbxImportPanel;
   CharacterPanel       * characterPanel;
   CagePanel            * cagePanel;
   ToolsPanel           * toolsPanel;

   ~Controller();

protected:

   Controller();

private:

   static Controller * instance;

};

#endif // CONTROLLER_H
