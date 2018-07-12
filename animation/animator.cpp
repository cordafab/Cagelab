#include "animator.h"

Animator::Animator(Cage * _cage)
{
   cage = _cage;
   keyframeIndex = 0;
}

void Animator::loadAnimation(const std::vector<double> & _t,
                             const std::vector<std::vector<double> > & _cageKeyframes)
{
   keyframeTime = _t;
   cageKeyframes = _cageKeyframes;
}



void  Animator::addKeyframe(double t, const std::vector<double> & keyframe)
{
   keyframeTime.push_back(t);
   cageKeyframes.push_back(keyframe);
   lastKeyframeT = t;
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

const std::vector<double> & Animator::getKeyframeTime() const
{
   return keyframeTime;
}

const std::vector<std::vector<double> > & Animator::getCageKeyframes() const
{
   return cageKeyframes;
}
