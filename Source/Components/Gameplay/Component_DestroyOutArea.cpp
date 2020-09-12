// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_DestroyOutArea.h"
#include "ecs/aaContainer.h"
#include "Utils/Rect.h"
#include "Device.h"
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
AComponentDestroyOutArea::AComponentDestroyOutArea()
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
AComponentDestroyOutArea::~AComponentDestroyOutArea()
{

}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// удаление всех объектов которые вышли за пределы экрана
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentDestroyOutArea::updateSlow(const float timeSpan)
{
    const auto container = getContainer();
    if (!container)
    {
        return;
    }

    if (mCurrent == mObjects.cend())
    {
        //получение новых объектов для исследования
        mObjects.clear();
        container->findComponents<AComponentGeometry>(mObjects);
        mCurrent = mObjects.cbegin();
        return;
    }


    int count = 10;
    while (--count && mCurrent != mObjects.cend())
    {
        next();
    }
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// првоерим следующий объект
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentDestroyOutArea::next()
{
    if (const auto geometry = *mCurrent++)
    {
        const float padding = 200;
        const FRect area(-padding, dm::deviceWidth() + padding, -padding, dm::deviceHeight() + padding);
        if (!area.contains(geometry->position()))
        {
            const auto container = getContainer();
            container->remove(geometry->getActor());
        }
    }
}