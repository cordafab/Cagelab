#include "characterPanel.h"
#include "ui_characterPanel.h"

#include "controller.h"
#include "drawables/drawableCharacter.h"
#include "GUI/glCanvas.h"

#include "common/characterOperations.h"
#include "common/cageOperations.h"

CharacterPanel::CharacterPanel(QWidget *parent) :
   QDockWidget(parent),
   ui(new Ui::CharacterPanel)
{
   ui->setupUi(this);
}

CharacterPanel::~CharacterPanel()
{
   delete ui;
}

void CharacterPanel::on_load_clicked()
{
   loadCharacterFromFile();
}

void CharacterPanel::on_drawTrimeshCB_clicked(bool checked)
{
   Controller * c = Controller::get();
   if(c->isCharacterLoaded)
   {
      c->character->activateCharacterRendering(checked);
      c->glCanvas->updateGL();
   }
}

void CharacterPanel::on_smoothColourRB_clicked(bool checked)
{
   Controller * c = Controller::get();
   if(c->isCharacterLoaded)
   {
      c->isCageWeightsRenderActive = false;
      c->character->activateSmoothColouration();
      c->glCanvas->updateGL();

   }
}

void CharacterPanel::on_flatColourRB_clicked(bool checked)
{
   Controller * c = Controller::get();
   if(c->isCharacterLoaded)
   {
      c->isCageWeightsRenderActive = false;
      c->character->activateFlatColouration();
      c->glCanvas->updateGL();
   }
}

void CharacterPanel::on_wireColourRB_clicked(bool checked)
{
   Controller * c = Controller::get();
   if(c->isCharacterLoaded)
   {
      c->isCageWeightsRenderActive = false;
      c->character->activateWireframe();
      c->glCanvas->updateGL();
   }
}

void CharacterPanel::on_cageColourRB_clicked(bool checked)
{
   Controller * c = Controller::get();
   if(c->isCharacterLoaded          &&
      c->isCageLoaded               &&
      c->isCageSkinningInitialized  &&
      c->areCageWeightsLoaded         )
   {
      c->isCageWeightsRenderActive = true;
      updateCageInfluenceTexture();
      c->character->activateTexture1D();
      c->glCanvas->updateGL();
   }
}

void CharacterPanel::on_save_clicked(bool checked)
{
   saveCharacterToFile();
}
