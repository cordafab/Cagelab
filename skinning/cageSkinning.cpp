#include "cageSkinning.h"

CageSkinning::CageSkinning()
{

}

CageSkinning::CageSkinning(Character * _character,
                           Cage      * _cage)
{
   setCharacter(_character);
   setCage(_cage);
}
