#include "animator.h"

Animator::Animator(Cage * _cage)
{
   cage = _cage;
   keyframeIndex = 0;
   debugCount = 0.0;
}

void  Animator::addKeyframe(double t, const std::vector<double> & keyframe)
{
   keyframeTime.push_back(t);
   cageKeyframes.push_back(keyframe);
}

void Animator::setNextPose()
{
   if(cageKeyframes.size()>0)
   {
      cage->setKeyframe(cageKeyframes[keyframeIndex]);
      keyframeIndex++;
      keyframeIndex %= cageKeyframes.size();
   }
}

void Animator::populateKeyframesDebug(int nVert)
{
   std::vector<double> k(nVert);
   k[0] = 1;
   k[1] = 1;
   k[2] = 1;

   k[3] = -1;
   k[4] = -1;
   k[5] = -1;

   keyframeTime.push_back(debugCount);
   debugCount += 1;
   cageKeyframes.push_back(k);

   k[0] = -1;
   k[1] = -1;
   k[2] = -1;

   k[3] = 1;
   k[4] = 1;
   k[5] = 1;

   keyframeTime.push_back(debugCount);
   debugCount += 1;
   cageKeyframes.push_back(k);

   k[0] = 1;
   k[1] = 1;
   k[2] = 1;

   k[3] = -1;
   k[4] = -1;
   k[5] = -1;

   keyframeTime.push_back(debugCount);
   debugCount += 1;
   cageKeyframes.push_back(k);

   k[0] = -1;
   k[1] = -1;
   k[2] = -1;

   k[3] = 1;
   k[4] = 1;
   k[5] = 1;

   keyframeTime.push_back(debugCount);
   debugCount += 1;
   cageKeyframes.push_back(k);

}
