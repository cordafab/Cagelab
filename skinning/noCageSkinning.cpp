#include "noCageSkinning.h"

NoCageSkinning::NoCageSkinning()
{

}

NoCageSkinning::NoCageSkinning(Character * _character, Cage * _cage)
   :CageSkinning(_character, _cage)
{
   weights = new Weights(0,0);
}

void NoCageSkinning::deform()
{

}

Weights * NoCageSkinning::getWeights()
{
   return weights;
}
