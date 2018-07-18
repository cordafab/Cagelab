#ifndef CAGEPANEL_H
#define CAGEPANEL_H

#include <QDockWidget>

namespace Ui {
   class CagePanel;
}

class CagePanel : public QDockWidget
{
   Q_OBJECT

public:
   explicit CagePanel(QWidget *parent = 0);
   ~CagePanel();

private:
   Ui::CagePanel *ui;

private slots:
   void on_load_clicked();
   void on_drawCageCB_clicked(bool checked);
   void on_weightsExport_clicked();
   void on_save_clicked(bool checked);
   void on_computeWeights_clicked();
   void on_noCoordinates_toggled(bool checked);
   void on_mvcCoordinates_toggled(bool checked);
   void on_greenCoordinates_toggled(bool checked);
   void on_sphereSize_sliderMoved(int position);
};

#endif // CAGEPANEL_H
