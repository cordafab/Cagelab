#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <vector>
#include "geom/cage.h"


class Animator
{
public:
   Animator(Cage * _cage);

   void addKeyframe(double t, const std::vector<double> & keyframe);
   void setNextPose();

private:
   std::vector<double> keyframeTime;
   std::vector<std::vector<double>> cageKeyframes;

   Cage * cage;
   double lastKeyframeT;

   int keyframeIndex;
};

#endif // ANIMATOR_H
