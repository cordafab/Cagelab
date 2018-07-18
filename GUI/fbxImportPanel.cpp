#include "fbxImportPanel.h"
#include "ui_fbxImportPanel.h"

#include "common/fbxOperations.h"

FbxImportPanel::FbxImportPanel(QWidget *parent) :
   QDockWidget(parent),
   ui(new Ui::fbxImportPanel)
{
   ui->setupUi(this);

   ui->load->setIcon(QIcon(QPixmap(":/GUI/icons/fbx.png")));
   ui->load->setStyleSheet("padding:5px; text-align:left;");
   ui->load->setIconSize(QSize(18, 18));
}

FbxImportPanel::~FbxImportPanel()
{
   delete ui;
}

void FbxImportPanel::on_load_clicked()
{
   loadFbxFromFile();
}
