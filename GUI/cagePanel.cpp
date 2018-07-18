#include "cagePanel.h"
#include "ui_cagePanel.h"

#include "controller.h"
#include "drawables/drawableCage.h"
#include "GUI/glCanvas.h"

#include "common/cageOperations.h"
#include "skinning/cageSkinning.h"

//TEST
#include "drawables/drawableCharacter.h"
#include "Eigen/SparseCore"
#include "skinning/weights.h"
#include "GUI/qtUtils.h"
#include "common/importFiles.h"
#include "common/exportFiles.h"

CagePanel::CagePanel(QWidget *parent) :
   QDockWidget(parent),
   ui(new Ui::CagePanel)
{
   ui->setupUi(this);

   ui->load->setIcon(QIcon(QPixmap(":/GUI/icons/open.png")));
   ui->load->setStyleSheet("padding:5px; text-align:left;");
   ui->load->setIconSize(QSize(18, 18));

   ui->save->setIcon(QIcon(QPixmap(":/GUI/icons/save.png")));
   ui->save->setStyleSheet("padding:5px; text-align:left;");
   ui->save->setIconSize(QSize(18, 18));

   ui->weightsExport->setIcon(QIcon(QPixmap(":/GUI/icons/save.png")));
   ui->weightsExport->setStyleSheet("padding:5px; text-align:left;");
   ui->weightsExport->setIconSize(QSize(18, 18));

   ui->computeWeights->setIcon(QIcon(QPixmap(":/GUI/icons/compute.png")));
   ui->computeWeights->setStyleSheet("padding:5px; text-align:left;");
   ui->computeWeights->setIconSize(QSize(18, 18));

}

CagePanel::~CagePanel()
{
   delete ui;
}

void CagePanel::on_load_clicked()
{
   loadCageFromFile();
}

void CagePanel::on_drawCageCB_clicked(bool checked)
{
   Controller * c = Controller::get();
   if(c->isCageLoaded)
   {
      c->cage->activateCageRendering(checked);
      c->glCanvas->updateGL();
   }
}

void CagePanel::on_weightsExport_clicked()
{
   saveCageWeightsToFile();
}

void CagePanel::on_save_clicked(bool checked)
{
   saveCageToFile();
}

void CagePanel::on_computeWeights_clicked()
{
   computeCageWeights();
   ui->noCoordinates->setEnabled(true);
   ui->mvcCoordinates->setEnabled(true);
   ui->greenCoordinates->setEnabled(true);
}

void CagePanel::on_noCoordinates_toggled(bool checked)
{
   Controller * c = Controller::get();
   if(c->areCageWeightsLoaded)
   {
      c->cageSkinning = (CageSkinning *)c->nc;
      c->cageWeights = c->cageSkinning->getWeights();
      c->glCanvas->updateGL();
   }
}

void CagePanel::on_mvcCoordinates_toggled(bool checked)
{
   Controller * c = Controller::get();
   if(c->areCageWeightsLoaded)
   {
      c->cageSkinning = (CageSkinning *)c->mvc;
      c->cageWeights = c->cageSkinning->getWeights();
      c->glCanvas->updateGL();
   }
}

void CagePanel::on_greenCoordinates_toggled(bool checked)
{
   Controller * c = Controller::get();
   if(c->areCageWeightsLoaded)
   {
      c->cageSkinning = (CageSkinning *)c->gc;
      c->cageWeights = c->cageSkinning->getWeights();
      c->glCanvas->updateGL();
   }
}

void CagePanel::on_sphereSize_sliderMoved(int position)
{
   Controller * c = Controller::get();
   if(c->isCageLoaded)
   {
      double val = (double) position / 100.0;
      c->cage->changeCageSphereSize(val);
      c->glCanvas->updateGL();
   }
}
