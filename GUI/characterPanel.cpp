#include "characterPanel.h"
#include "ui_characterPanel.h"

#include "controller.h"
#include "drawables/drawableCharacter.h"
#include "GUI/glCanvas.h"

#include "common/characterOperations.h"
#include "common/cageOperations.h"

#include <QColorDialog>

CharacterPanel::CharacterPanel(QWidget *parent) :
   QDockWidget(parent),
   ui(new Ui::CharacterPanel)
{
   ui->setupUi(this);

   ui->load->setIcon(QIcon(QPixmap(":/GUI/icons/open.png")));
   ui->load->setStyleSheet("padding:5px; text-align:left;");
   ui->load->setIconSize(QSize(18, 18));

   ui->save->setIcon(QIcon(QPixmap(":/GUI/icons/save.png")));
   ui->save->setStyleSheet("padding:5px; text-align:left;");
   ui->save->setIconSize(QSize(18, 18));

   ui->changeColour->setIcon(QIcon(QPixmap(":/GUI/icons/colourPick.png")));
   ui->changeColour->setStyleSheet("padding:5px; text-align:left;");
   ui->changeColour->setIconSize(QSize(18, 18));



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

void CharacterPanel::on_save_clicked(bool checked)
{
   saveCharacterToFile();
}

void CharacterPanel::on_renderCageWeightsCB_clicked(bool checked)
{
   Controller * c = Controller::get();
   if(c->isCharacterLoaded          &&
      c->isCageLoaded               &&
      c->isCageSkinningInitialized  &&
      c->areCageWeightsLoaded         )
   {
      c->isCageWeightsRenderActive = checked;
      updateCageInfluenceTexture();
      c->character->activateTexture1D(checked);
      c->glCanvas->updateGL();
   }

}

void CharacterPanel::on_changeColour_clicked()
{


    Controller * c = Controller::get();
    if(c->isCharacterLoaded)
    {
       QColor colour = QColorDialog::getColor(Qt::white, this);
       c->character->changeColour((double) (colour.red())  /255.0,
                                  (double) (colour.green())/255.0,
                                  (double) (colour.blue())/255.0);
       //c->character->changeColour(0.5, 0.1, 0.3);
       c->glCanvas->updateGL();
    }

}

void CharacterPanel::on_noColourRB_clicked()
{
   Controller * c = Controller::get();
   if(c->isCharacterLoaded)
   {
      c->character->deactivateColour();
      std::cout << "NOCOL" << std::endl;
      c->glCanvas->updateGL();
   }
}

void CharacterPanel::on_renderWireframeCB_clicked(bool checked)
{
   Controller * c = Controller::get();
   if(c->isCharacterLoaded)
   {
      c->character->activateWireframe(checked);
      std::cout << "WIRE" << std::endl;
      c->glCanvas->updateGL();
   }
}
