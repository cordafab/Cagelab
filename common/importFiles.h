#ifndef IMPORTFILES_H
#define IMPORTFILES_H

#include <vector>

void loadMesh  (const char                * filename,
               std::vector<double>        & vertices,
               std::vector<int>           & faces   );

void loadOBJ   (const char                * filename,
               std::vector<double>        & vertices,
               std::vector<int>           & faces   );

void loadPLY   (const char                * filename,
               std::vector<double>        & vertices,
               std::vector<int>           & faces   );

#endif // IMPORTFILES_H
