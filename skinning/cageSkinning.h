#ifndef CAGESKINNING_H
#define CAGESKINNING_H

#include "skinning/weights.h"
#include "geom/cage.h"
#include "geom/character.h"
#include "geom/transform.h"

class CageSkinning
{
public:
   CageSkinning();
   CageSkinning(Weights * _w,
                Character * _character,
                Cage * _cage);

   inline void setWeights(Weights * _w) { w = _w; }
   inline void setCharacter(Character * _character) { character = _character; }
   inline void setCage(Cage * _cage) { cage = _cage; }

   virtual void deform() = 0;

protected:
   Weights * w;
   Character * character;
   Cage * cage;
};

#endif // CAGESKINNING_H
