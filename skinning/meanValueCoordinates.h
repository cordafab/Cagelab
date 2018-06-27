#ifndef MEANVALUECOORDINATES_H
#define MEANVALUECOORDINATES_H

#include "skinning/weights.h"
#include "geom/character.h"
#include "geom/cage.h"
#include "geom/vec3.h"
#include "skinning/cageSkinning.h"

class MeanValueCoordinates:
      public CageSkinning
{
public:
   MeanValueCoordinates();
   MeanValueCoordinates(Weights     * _w,
                        Character   * _character,
                        Cage        * _cage);

   void deform();

   static bool generateCoords(Weights           * & weights,
                              Character         *   character,
                              Cage              *   cage);
};


#endif // MEANVALUECOORDINATES_H
