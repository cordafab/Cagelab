#include "animatorPanel.h"
#include "ui_animatorPanel.h"

#include "common/animatorOperations.h"
#include "animation/animator.h"
#include "controller.h"

AnimatorPanel::AnimatorPanel(QWidget *parent) :
   QDockWidget(parent),
   ui(new Ui::AnimatorPanel)
{
   ui->setupUi(this);

   ui->loadAnimation->setIcon(QIcon(QPixmap(":/GUI/icons/open.png")));
   ui->loadAnimation->setStyleSheet("padding:5px; text-align:left;");
   ui->loadAnimation->setIconSize(QSize(18, 18));

   ui->saveAnimation->setIcon(QIcon(QPixmap(":/GUI/icons/save.png")));
   ui->saveAnimation->setStyleSheet("padding:5px; text-align:left;");
   ui->saveAnimation->setIconSize(QSize(18, 18));

   ui->exportCharKframes->setIcon(QIcon(QPixmap(":/GUI/icons/export.png")));
   ui->exportCharKframes->setStyleSheet("padding:5px; text-align:left;");
   ui->exportCharKframes->setIconSize(QSize(18, 18));

   ui->exportCagesKframes->setIcon(QIcon(QPixmap(":/GUI/icons/export.png")));
   ui->exportCagesKframes->setStyleSheet("padding:5px; text-align:left;");
   ui->exportCagesKframes->setIconSize(QSize(18, 18));

   ui->addKeyframe->setIcon(QIcon(QPixmap(":/GUI/icons/add.png")));
   ui->addKeyframe->setIconSize(QSize(18, 18));

   ui->deleteKeyframe->setIcon(QIcon(QPixmap(":/GUI/icons/clear.png")));
   ui->deleteKeyframe->setIconSize(QSize(18, 18));

   ui->editTime->setIcon(QIcon(QPixmap(":/GUI/icons/edit.png")));
   ui->editTime->setIconSize(QSize(18, 18));

   ui->nextKeyframe->setIcon(QIcon(QPixmap(":/GUI/icons/next.png")));
   ui->nextKeyframe->setIconSize(QSize(18, 18));

}

AnimatorPanel::~AnimatorPanel()
{
   delete ui;
}

void AnimatorPanel::updateKeyframeList()
{
   Controller * c = Controller::get();
   const std::vector<double> & t = c->animator->getKeyframeTimeVector();
   ui->keyframeList->clear();
   for(int i=0; i<t.size(); ++i)
   {
      std::string label = std::to_string(i) + " " + std::to_string(t[i]);
      ui->keyframeList->addItem( label.c_str() );
   }
}

void AnimatorPanel::on_addKeyframe_clicked()
{
    addKeyframe();
    updateKeyframeList();
}

void AnimatorPanel::on_nextKeyframe_clicked()
{
    setNextKeyframe();
}

void AnimatorPanel::on_saveAnimation_clicked()
{
    saveAnimationToFile();
}

void AnimatorPanel::on_loadAnimation_clicked()
{
    loadAnimationFromFile();
    updateKeyframeList();
}

void AnimatorPanel::on_exportCagesKframes_clicked()
{
    exportCageKeyframes();
}

void AnimatorPanel::on_exportCharKframes_clicked()
{
    exportCharacterKeyframes();
}

void AnimatorPanel::on_keyframeList_itemClicked(QListWidgetItem *item)
{
   std::string label = item->text().toStdString();
   std::istringstream iss(label);

   int keyFrameIndex;
   iss >> keyFrameIndex;
   setKeyframe(keyFrameIndex);
}

void AnimatorPanel::on_deleteKeyframe_clicked()
{
   if(ui->keyframeList->count()>0)
   {
      QList<QListWidgetItem *> items = ui->keyframeList->selectedItems();

      if(items.size()>0)
      {
         QListWidgetItem * item = items[0];
         std::string label = item->text().toStdString();
         std::istringstream iss(label);

         int keyFrameIndex;
         iss >> keyFrameIndex;
         deleteKeyframe(keyFrameIndex);
         updateKeyframeList();
      }
   }
}

void AnimatorPanel::on_editTime_clicked()
{
   if(ui->keyframeList->count()>0)
   {
      QList<QListWidgetItem *> items = ui->keyframeList->selectedItems();

      if(items.size()>0)
      {
         QListWidgetItem * item = items[0];
         std::string label = item->text().toStdString();
         std::istringstream iss(label);

         int keyFrameIndex;
         iss >> keyFrameIndex;
         editKeyframeTime(keyFrameIndex);
         updateKeyframeList();
      }
   }
}
