#include "toolsPanel.h"
#include "ui_toolsPanel.h"

#include "controller.h"
#include "common/cageOperations.h"
#include "common/toolsOperation.h"
#include "common/animatorOperations.h"

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
   /*ui->interCamera->setText("Camera NO");
   ui->interSelect->setText("Select NO");
   ui->interDeselect->setText("Deselect NO");
   ui->interDeform->setText("Deform NO");*/
   ui->interCamera->setIcon(QIcon(QPixmap(":/GUI/icons/noneIconButton.png")));
   ui->interCamera->setIconSize(QSize(48, 48));

   ui->interSelect->setIcon(QIcon(QPixmap(":/GUI/icons/selectIconButton.png")));
   ui->interSelect->setIconSize(QSize(48, 48));

   ui->interDeselect->setIcon(QIcon(QPixmap(":/GUI/icons/deselectIconButton.png")));
   ui->interDeselect->setIconSize(QSize(48, 48));

   ui->interDeform->setIcon(QIcon(QPixmap(":/GUI/icons/deformIconButton.png")));
   ui->interDeform->setIconSize(QSize(48, 48));
   switch(c->interactionMode)
   {
      case CAMERA_INTERACTION:
         ui->interCamera->setIcon(QIcon(QPixmap(":/GUI/icons/AnoneIconButton.png")));
         ui->interCamera->setIconSize(QSize(48, 48));
         break;
      case SELECT_INTERACTION:
         ui->interSelect->setIcon(QIcon(QPixmap(":/GUI/icons/AselectIconButton.png")));
         ui->interSelect->setIconSize(QSize(48, 48));
         break;
      case DESELECT_INTERACTION:
         ui->interDeselect->setIcon(QIcon(QPixmap(":/GUI/icons/AdeselectIconButton.png")));
         ui->interDeselect->setIconSize(QSize(48, 48));
         break;
      case DEFORM_INTERACTION:
         ui->interDeform->setIcon(QIcon(QPixmap(":/GUI/icons/AdeformIconButton.png")));
         ui->interDeform->setIconSize(QSize(48, 48));
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

void ToolsPanel::on_NextKey_clicked()
{
   setNextKeyframe();
}

void ToolsPanel::on_SaveKey_clicked()
{
    addKeyframe();
}
