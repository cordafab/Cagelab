#ifndef ANIMATOROPERATIONS_H
#define ANIMATOROPERATIONS_H



void initializeAnimator();
void loadAnimationFromFile();
void saveAnimationToFile();
void exportCageKeyframes();
void exportCharacterKeyframes();
void setNextKeyframe();
void setKeyframe(int index);
void addKeyframe();
void deleteKeyframe(int index);
void editKeyframeTime(int index);
#endif // ANIMATOROPERATIONS_H
