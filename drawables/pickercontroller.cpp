#include "pickerController.h"

PickerController::PickerController()
{
   firstFreeIndex = 0;
}

PickerController* PickerController::instance = 0;

PickerController* PickerController::get()
{
    if (instance == 0)
        instance = new PickerController;
    return instance;
}

int PickerController::generateIndex(PickableObject *pickableObject)
{
   pickableIds[firstFreeIndex] = pickableObject;
   firstFreeIndex++;
   return firstFreeIndex-1;
}

void PickerController::removeIndex(const int & index)
{
    pickableIds.erase(index);
}

void PickerController::removeObject(PickableObject *pickableObject)
{

}

PickableObject* PickerController::getObject(const int & index)
{
    return pickableIds[index];
}
