#ifndef ANIMATORPANEL_H
#define ANIMATORPANEL_H

#include <QDockWidget>
#include <QListWidgetItem>

namespace Ui {
   class AnimatorPanel;
}

class AnimatorPanel : public QDockWidget
{
   Q_OBJECT

public:
   explicit AnimatorPanel(QWidget *parent = 0);
   ~AnimatorPanel();

   void updateKeyframeList();

private slots:
   void on_addKeyframe_clicked();

   void on_IterateKeyframe_clicked();

   void on_saveAnimation_clicked();

   void on_loadAnimation_clicked();

   void on_exportCagesKframes_clicked();

   void on_exportCharKframes_clicked();

   void on_keyframeList_itemClicked(QListWidgetItem *item);

   void on_deleteKeyframe_clicked();

   void on_editTime_clicked();

private:
   Ui::AnimatorPanel *ui;
};

#endif // ANIMATORPANEL_H
