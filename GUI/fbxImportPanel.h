#ifndef FBXIMPORTPANEL_H
#define FBXIMPORTPANEL_H

#include <QDockWidget>

namespace Ui {
   class fbxImportPanel;
}

class FbxImportPanel : public QDockWidget
{
   Q_OBJECT

public:
   explicit FbxImportPanel(QWidget *parent = 0);
   ~FbxImportPanel();

private slots:
   void on_load_clicked();

private:
   Ui::fbxImportPanel *ui;
};

#endif // FBXIMPORTPANEL_H
