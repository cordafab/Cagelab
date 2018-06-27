#include "mainWindow.h"
#include "ui_mainWindow.h"

#include "GUI/glCanvas.h"
#include "GUI/fbxImportPanel.h"
#include "GUI/characterPanel.h"
#include "GUI/cagePanel.h"
#include "GUI/toolsPanel.h"

#include "GUI/qtUtils.h"

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   controller = Controller::get();

   //configure glCanvas
   controller->glCanvas = new GlCanvas(ui->centralWidget);
   controller->glCanvas->setObjectName(QStringLiteral("GlCanvas"));
   ui->verticalLayout->addWidget(controller->glCanvas);

   //configure fbxImportPanel
   if(!controller->fbxImportPanel)
   {
      controller->fbxImportPanel = new FbxImportPanel(this);
   }
   controller->fbxImportPanel->show();
   addDockWidget(Qt::LeftDockWidgetArea, controller->fbxImportPanel);

   //configure trimeshPanel
   if(!controller->characterPanel)
   {
      controller->characterPanel = new CharacterPanel(this);
   }
   controller->characterPanel->show();
   addDockWidget(Qt::LeftDockWidgetArea, controller->characterPanel);


   //configure CagePanel
   if(!controller->cagePanel)
   {
      controller->cagePanel = new CagePanel(this);
   }
   controller->cagePanel->show();
   addDockWidget(Qt::LeftDockWidgetArea, controller->cagePanel);


   //configure ToolPanel
   if(!controller->toolsPanel)
   {
      controller->toolsPanel = new ToolsPanel(this);
   }
   controller->toolsPanel->show();
   addDockWidget(Qt::RightDockWidgetArea, controller->toolsPanel);

   updateGUI();

   /*tabifyDockWidget(controller->fbxImportPanel, controller->trimeshPanel);
   tabifyDockWidget(controller->trimeshPanel, controller->cagePanel);
   tabifyDockWidget(controller->cagePanel, controller->skeletonPanel);
   controller->fbxImportPanel->raise();*/

   showMaximized();
}

MainWindow::~MainWindow()
{
   delete ui;
}
