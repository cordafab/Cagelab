#ifndef PICKERCONTROLLER_H
#define PICKERCONTROLLER_H

#include <map>

class PickableObject;

class PickerController
{
public:
   static PickerController* get();

   int generateIndex(PickableObject *pickableObject);
   //A PickableObject can have multiple indexes associated

   void removeIndex(const int &index);

   void removeObject(PickableObject *pickableObject);

   PickableObject* getObject(const int &index);
   //Returns the PickableObject associated to the given index

   //PickableObject* checkCollision () = 0;

protected:
   PickerController();

private:
   static PickerController * instance;

   std::map<int, PickableObject *> pickableIds;
   int firstFreeIndex;
};

#endif // PICKERCONTROLLER_H
