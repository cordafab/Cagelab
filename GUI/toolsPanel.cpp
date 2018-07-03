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

void ToolsPanel::updateInteractionModeButtons()
{
   Controller * c = Controller::get();
   ui->interCamera->setText("Camera NO");
   ui->interSelect->setText("Select NO");
   ui->interDeselect->setText("Deselect NO");
   ui->interDeform->setText("Deform NO");
   switch(c->interactionMode)
   {
      case CAMERA_INTERACTION:
         ui->interCamera->setText("Camera YES");
         break;
      case SELECT_INTERACTION:
         ui->interSelect->setText("Select YES");
         break;
      case DESELECT_INTERACTION:
         ui->interDeselect->setText("Deselect YES");
         break;
      case DEFORM_INTERACTION:
         ui->interDeform->setText("Deform YES");
         break;
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

void ToolsPanel::on_interCamera_clicked()
{
   activateCameraInteractionMode();
}

void ToolsPanel::on_interSelect_clicked()
{
   activateSelectionInteractionMode();
}

void ToolsPanel::on_interDeselect_clicked()
{
   activateDeselectInteractionMode();
}

void ToolsPanel::on_interDeform_clicked()
{
   activateDeformationInteractionMode();
}
