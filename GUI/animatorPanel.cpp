#include "animatorPanel.h"
#include "ui_animatorPanel.h"

#include "common/animatorOperations.h"

AnimatorPanel::AnimatorPanel(QWidget *parent) :
   QDockWidget(parent),
   ui(new Ui::AnimatorPanel)
{
   ui->setupUi(this);
}

AnimatorPanel::~AnimatorPanel()
{
   delete ui;
}

void AnimatorPanel::on_addKeyframe_clicked()
{
    addKeyframe();
}

void AnimatorPanel::on_IterateKeyframe_clicked()
{
    setNextKeyframe();
}
