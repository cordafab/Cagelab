#include "cagePanel.h"
#include "ui_cagePanel.h"

#include "controller.h"
#include "drawables/drawableCage.h"
#include "GUI/glCanvas.h"

#include "common/cageOperations.h"

//TEST
#include "drawables/drawableCharacter.h"
#include "Eigen/SparseCore"
#include "skinning/weights.h"
#include "GUI/qtUtils.h"
#include "common/importFiles.h"
#include "common/exportFiles.h"
#include "cinolib/linear_solvers.h"

CagePanel::CagePanel(QWidget *parent) :
   QDockWidget(parent),
   ui(new Ui::CagePanel)
{
   ui->setupUi(this);
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
