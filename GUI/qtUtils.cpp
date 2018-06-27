#include "qtUtils.h"

#include <QFileDialog>
#include "common/toolsOperation.h"

bool openFileSelectionDialog(std::string & filename,
                             const std::string & caption,
                             const std::string & filter)
{
   QString qtFilename = QFileDialog::getOpenFileName(nullptr,
                        caption.c_str(),
                        ".",
                        filter.c_str());

   filename = qtFilename.toStdString();

   return (!qtFilename.isEmpty());
}

bool openFileSaveDialog(std::string & filename,
                        const std::string & caption,
                        const std::string & filter)
{
   QString qtFilename = QFileDialog::getSaveFileName(NULL,
                        caption.c_str(),
                        ".",
                        filter.c_str());

   filename = qtFilename.toStdString();

   return (!qtFilename.isEmpty());
}

void updateGUI()
{
   updateToolsGUI();
}
