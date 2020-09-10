// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "aaSystem_Update.h"


using namespace ecs;
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Constructor
///
///
///-------------------------------------------------------------------------
ASystemUpdate::ASystemUpdate(const float timeSlow)
    :
    mTimeSlow(timeSlow)
{

}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Destructor
///
///
///-------------------------------------------------------------------------
ASystemUpdate::~ASystemUpdate()
{


}
///-------------------------------------------------------------------------











 ///------------------------------------------------------------------------
///
///
///
/// ќбновление логики
///
///
///-------------------------------------------------------------------------
void ASystemUpdate::update(const float timeSpan)
{
    updatingSystem();


    // мделенное обновление
    // ссзадержкой
    mTime += timeSpan;
    bool slow = (mTime > mTimeSlow) ? true : false;


    for (const auto &obj : components)
    {
        obj->update(timeSpan);
        if (slow)
        {
            obj->updateSlow(mTime);
        }
    }


    if (slow)
    {
        mTime -= mTimeSlow;
    }
}
///-------------------------------------------------------------------------

