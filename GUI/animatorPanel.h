#ifndef ANIMATORPANEL_H
#define ANIMATORPANEL_H

#include <QDockWidget>

namespace Ui {
   class AnimatorPanel;
}

class AnimatorPanel : public QDockWidget
{
   Q_OBJECT

public:
   explicit AnimatorPanel(QWidget *parent = 0);
   ~AnimatorPanel();

private slots:
   void on_addKeyframe_clicked();

   void on_IterateKeyframe_clicked();

   void on_saveAnimation_clicked();

   void on_loadAnimation_clicked();

private:
   Ui::AnimatorPanel *ui;
};

#endif // ANIMATORPANEL_H
