#include "cageSkinning.h"

CageSkinning::CageSkinning()
{

}

CageSkinning::CageSkinning(Weights *_w,
                           Character *_character,
                           Cage *_cage)
{
   setWeights(_w);
   setCharacter(_character);
   setCage(_cage);
}
