#include "toolsOperation.h"
#include "GUI/toolsPanel.h"

#include "controller.h"
#include "GUI/glCanvas.h"
#include "drawables/drawableCharacter.h"

//TEST
#include "common/exportFiles.h"
#include "GUI/qtUtils.h"


void updateToolsGUI()
{
   Controller * c = Controller::get();
   c->toolsPanel->updateCageDeformationButton();
   c->toolsPanel->updateInteractionModeButtons();
}

void saveCamera()
{
   Controller * c = Controller::get();

   c->glCanvas->saveCamera();
}

void restoreCamera()
{
   Controller * c = Controller::get();

   c->glCanvas->restoreCamera();
}

void activateCameraInteractionMode()
{
   Controller * c = Controller::get();

   c->glCanvas->setInteractionMode(CAMERA_INTERACTION);
}

void activateSelectionInteractionMode()
{
   Controller * c = Controller::get();

   c->glCanvas->setInteractionMode(SELECT_INTERACTION);
}

void activateDeselectInteractionMode()
{
   Controller * c = Controller::get();

   c->glCanvas->setInteractionMode(DESELECT_INTERACTION);
}

void activateDeformationInteractionMode()
{
   Controller * c = Controller::get();

   c->glCanvas->setInteractionMode(DEFORM_INTERACTION);
}
