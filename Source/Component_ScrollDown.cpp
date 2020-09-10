// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_ScrollDown.h"
#include "Component_ScrollCan.h"
#include "Component_LevelContent.h"
#include "ecs/aaContainer.h"
#include "MathUtils.h"
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
AComponentScollDown::AComponentScollDown(const int rows)
    :
        mRows(rows)
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
AComponentScollDown::~AComponentScollDown()
{

}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// скроллинг элементов
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentScollDown::update(const float timeSpan)
{
    if (!mScolling)
    {
        return;
    }

    mTimer += timeSpan;
    float dm = std::sin(mTimer);
    if (mTimer > math::PI * 0.5f)
    {
        mScolling = false;
        dm = 1.0f;
    }
    FPoint shift(0, settings::scrolling_height * dm);

    auto item = mObjects.cbegin();
    while (item != mObjects.cend())
    {
        const auto &geometry = item->second;
        if (!geometry->getContainer())
        {
            item = mObjects.erase(item);
            continue;
        }

        const auto pos = item->first + shift;
        geometry->setPosition(pos);

        ++item;
    }


    if (!mScolling)
    {
        mObjects.clear();

        if (const auto level = findComponent<AComponentLevelContent>())
        {
            level->nextSpawn();
        }
        scrollStart();
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// нахождение новых элементов для скроллинга
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentScollDown::updateSlow(const float timeSpan)
{
    if (!mScolling)
    {
        scrollStart();
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// начало скроллинга
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentScollDown::scrollStart()
{
    mScolling = false;

    bool bStopScroll = false;
    if (const auto level = findComponent<AComponentLevelContent>())
    {
        if (level->isEmpty())
        {
            //кирпичей новых больше нет
            //нужно остановить скроллинг
            bStopScroll = true;
        }
    }


    const auto container = getContainer();
    if (!container)
    {
        return;
    }

    const float top = settings::scrolling_height / 2;
    const float bottom = (mRows - 1) * settings::scrolling_height; //нижняя граница когда нужно двигать
    
    mObjects.clear();
    for (const auto &can : container->findComponents<AComponentScrollCan>())
    {
        if (const auto geometry = can->findComponent<AComponentGeometry>())
        {
            const auto size = geometry->boundingSize().y * 0.5f;
            const auto pos = geometry->position();
            
            const auto canTop = pos.y - size;
            const auto canBottom = pos.y + size;
            if (canBottom > bottom && can->isScrollingControl())
            {
                //ненужно двигать все вниз
                //ибо есть элементы которые находятся ниже черты
                mObjects.clear();
                return;
            }
            if (canTop < top)
            {
                //наверху есть еще блоки,
                //нужно сдвигать
                bStopScroll = false;
            }
            mObjects.push_back({pos, geometry});
        }
    }
    
    if (bStopScroll)
    {
        mObjects.clear();
        return;
    }

    mScolling = true;
    mTimer = 0.0f;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// добавить принудительно на скроллинг если есть скролл
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentScollDown::replacement(const PComponentGeometry &old, const PComponentGeometry &obj)
{
    if (!mScolling)
    {
        return;
    }
    
    auto item = std::find_if(mObjects.begin(), mObjects.end(), [old](const auto &id)
    {
        return old == id.second;
    });
    
    if (item != mObjects.end())
    {
        item->second = obj;
    }
        
    
}