#ifndef QTUTILS_H
#define QTUTILS_H

#include <string>

bool openFileSelectionDialog(std::string & filename,
                             const std::string & caption,
                             const std::string & filter);

bool openFileSaveDialog(std::string & filename,
                        const std::string & caption,
                        const std::string & filter);

void updateGUI();

#endif // QTUTILS_H
