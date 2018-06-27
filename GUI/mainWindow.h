#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"

namespace Ui {
   class MainWindow;
}

class MainWindow
      : public QMainWindow
{
   Q_OBJECT

public:

   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private:

   Ui::MainWindow *  ui;
   Controller     *  controller;

};

#endif // MAINWINDOW_H
