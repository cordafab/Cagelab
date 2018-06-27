#ifndef CHARACTERPANEL_H
#define CHARACTERPANEL_H

#include <QDockWidget>

namespace Ui {
   class CharacterPanel;
}

class CharacterPanel : public QDockWidget
{
   Q_OBJECT

public:
   explicit CharacterPanel(QWidget *parent = 0);
   ~CharacterPanel();

private:
   Ui::CharacterPanel *ui;

private slots:
   void on_load_clicked();

   void on_drawTrimeshCB_clicked(bool checked);
   void on_smoothColourRB_clicked(bool checked);
   void on_flatColourRB_clicked(bool checked);
   void on_wireColourRB_clicked(bool checked);
   void on_cageColourRB_clicked(bool checked);
   void on_save_clicked(bool checked);
};

#endif // CHARACTERPANEL_H
