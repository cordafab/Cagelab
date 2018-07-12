#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <vector>
#include "geom/cage.h"


class Animator
{
public:
   Animator(Cage * _cage);

   void loadAnimation(const std::vector<double> & _t,
                      const std::vector<std::vector<double>> & _cageKeyframes );

   void addKeyframe(double t, const std::vector<double> & keyframe);
   void setNextPose();

   const std::vector<double> & getKeyframeTime() const;
   const std::vector<std::vector<double>> & getCageKeyframes() const;

private:
   std::vector<double> keyframeTime;
   std::vector<std::vector<double>> cageKeyframes;

   Cage * cage;
   double lastKeyframeT;

   int keyframeIndex;
};

#endif // ANIMATOR_H
