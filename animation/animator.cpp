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
   int i=0;
   std::vector<double>::iterator it = keyframeTime.begin();
   while(i<keyframeTime.size() && keyframeTime[i] < t )
   {
      i++;
   }

   if(i==keyframeTime.size())
   {
      keyframeTime.push_back(t);
      cageKeyframes.push_back(keyframe);
      lastKeyframeT = t;
   } else {
      keyframeTime.insert(keyframeTime.begin()+i,t);
      cageKeyframes.insert(cageKeyframes.begin()+i,keyframe);
      lastKeyframeT = t;
   }
}

void Animator::editKeyframeTime(int index, double newTime)
{
   std::vector<double> keyframe = cageKeyframes[index];
   deleteKeyframe(index);
   addKeyframe(newTime, keyframe);
}

void Animator::setKeyframe(int index)
{
   if(index < cageKeyframes.size())
   {
      cage->setKeyframe(cageKeyframes[index]);
      keyframeIndex = index;
   }

}

void Animator::deleteKeyframe(int index)
{
   if(index < cageKeyframes.size())
   {
      keyframeTime.erase(keyframeTime.begin()+index);
      cageKeyframes.erase(cageKeyframes.begin()+index);
   }
}

bool Animator::setNextKeyframe()
{
   if(cageKeyframes.size()>0)
   {
      cage->setKeyframe(cageKeyframes[keyframeIndex]);
      keyframeIndex++;
      keyframeIndex %= cageKeyframes.size();
      return true;
   } else
      return false;
}

const std::vector<double> & Animator::getKeyframeTimeVector() const
{
   return keyframeTime;
}

const std::vector<std::vector<double> > & Animator::getCageKeyframesVector() const
{
   return cageKeyframes;
}
