#ifndef TOOLSPANEL_H
#define TOOLSPANEL_H

#include <QDockWidget>

namespace Ui {
   class ToolsPanel;
}

class ToolsPanel : public QDockWidget
{
   Q_OBJECT

public:
   explicit ToolsPanel(QWidget *parent = 0);
   ~ToolsPanel();
   void updateCageDeformationButton();

private slots:
   void on_cageDeformation_clicked();
   void on_saveCamera_clicked();
   void on_restoreCamera_clicked();


private:
   Ui::ToolsPanel *ui;
};

#endif // TOOLSPANEL_H
