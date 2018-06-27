/**
   @author     Fabrizio Corda (cordafab@gmail.com)
   @copyright  Fabrizio Corda, 2017
**/

#include <QApplication>
#include <QStyleFactory>
#include "GUI/mainWindow.h"

int main(int argc, char* argv[])
{
   QApplication app(argc,argv);
   QApplication::setStyle(QStyleFactory::create("Fusion"));

   MainWindow gui;
   gui.show();

   return app.exec();
}
