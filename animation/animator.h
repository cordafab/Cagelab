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
   void editKeyframeTime(int index, double newTime);

   //iterate
   inline int getNumberOfKeyframes() const {return keyframeTime.size();}
   inline double getKeyframeTime(int index) const {return keyframeTime[index];}
   inline void resetIterator(){keyframeIndex = 0;}
   inline double getActualTimePose() const {return keyframeTime[keyframeIndex];}
   void setKeyframe(int index);
   void deleteKeyframe(int index);
   bool setNextKeyframe();

   const std::vector<double> & getKeyframeTimeVector() const;
   const std::vector<std::vector<double>> & getCageKeyframesVector() const;

private:
   std::vector<double> keyframeTime;
   std::vector<std::vector<double>> cageKeyframes;

   Cage * cage;
   double lastKeyframeT;

   int keyframeIndex;
};

#endif // ANIMATOR_H
