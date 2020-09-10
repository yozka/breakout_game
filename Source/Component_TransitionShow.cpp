// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_TransitionShow.h"


///-------------------------------------------------------------------------




///-------------------------------------------------------------------------
using namespace game;
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Constructor
///
///
///-------------------------------------------------------------------------
AComponentTransitionShow::AComponentTransitionShow(const int cols, const int rows, const std::function<void()> &completed)
    :
    super(cols, rows),
    mCompleted(completed)
{

}
///-------------------------------------------------------------------------








 ///------------------------------------------------------------------------
///
/// <summary>
/// destructor
/// </summary>
///
///-------------------------------------------------------------------------
AComponentTransitionShow::~AComponentTransitionShow()
{

}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentTransitionShow::update(const float timeSpan)
{
    super::update(timeSpan);

    const float time = 0.6f; //время работы
    bool end = false;

    mTime += timeSpan;
    if (mTime > time)
    {
        mTime = time;
        end = true;
    }

    const float dm = (1.0f / time) * mTime;
    const float scale = 1.0f - dm;
    const float angle = 90.0f * (1.0f - dm);
    for (const auto &obj : blocks)
    {
        if (!obj) continue;
        obj->setScale(scale);
        obj->setAngle(angle);
    }


    if (end)
    {
        destroy();
        if (mCompleted)
        {
            mCompleted();
        }
    }

}
///-------------------------------------------------------------------------



