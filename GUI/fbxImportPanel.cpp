#include "fbxImportPanel.h"
#include "ui_fbxImportPanel.h"

#include "common/fbxOperations.h"

FbxImportPanel::FbxImportPanel(QWidget *parent) :
   QDockWidget(parent),
   ui(new Ui::fbxImportPanel)
{
   ui->setupUi(this);
}

FbxImportPanel::~FbxImportPanel()
{
   delete ui;
}

void FbxImportPanel::on_load_clicked()
{
   loadFbxFromFile();
}
