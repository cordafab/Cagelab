#include "toolsPanel.h"
#include "ui_toolsPanel.h"

#include "controller.h"
#include "common/cageOperations.h"
#include "common/toolsOperation.h"

ToolsPanel::ToolsPanel(QWidget *parent) :
   QDockWidget(parent),
   ui(new Ui::ToolsPanel)
{
   ui->setupUi(this);
}

ToolsPanel::~ToolsPanel()
{
   delete ui;
}

void ToolsPanel::updateCageDeformationButton()
{
   Controller * c = Controller::get();

   if(c->isCageDeformerActive)
   {
      ui->cageDeformation->setText("CageON");
   }
   else
   {
      ui->cageDeformation->setText("CageOFF");
   }
}

void ToolsPanel::on_cageDeformation_clicked()
{
   switchCageDeformation();
}


void ToolsPanel::on_saveCamera_clicked()
{
    saveCamera();
}

void ToolsPanel::on_restoreCamera_clicked()
{
    restoreCamera();
}
