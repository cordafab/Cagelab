#ifndef EXPORTFILES_H
#define EXPORTFILES_H

#include "skinning/weights.h"
#include <vector>

void saveMesh  (const char                * filename,
                const std::vector<double> & vertices,
                const std::vector<int>    & faces   );

void saveOBJ   (const char                * filename,
                const std::vector<double> & vertices,
                const std::vector<int>    & faces   );

void savePLY   (const char                * filename,
                const std::vector<double> & vertices,
                const std::vector<int>    & faces   );

void saveWeights  (const char    * filename,
                   const Weights & weights);

void saveAnimation (const char                              * filename,
                    const std::vector<double>               & t,
                    const std::vector<std::vector<double> > & cageKeyframes);

#endif // EXPORTFILES_H
