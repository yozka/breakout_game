// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_Lives.h"
#include "Components/Graphics/Component_Sprite.h"

#include "ecs/utils/aaUtils.h"

///-------------------------------------------------------------------------
using namespace game;
///-------------------------------------------------------------------------



///-------------------------------------------------------------------------
namespace settings
{
    constexpr int   tagFull     = 100102; //рандомный тегспрайтов которые отрисовывают количество жизней
    constexpr int   tagEmpty    = 100103; //исопльзованная жизнь

}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Constructor
///
///
///-------------------------------------------------------------------------
AComponentLives::AComponentLives(const int count)
    :
        mCount(count),
        mCurrent(count)
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
AComponentLives::~AComponentLives()
{

}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// обновить сотояние
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLives :: refresh()
{
    if (mRefreshing)
    {
        return;
    }
    mRefreshing = true;

    makeCondition("hudHeart_full",  settings::tagFull,  mCurrent);
    makeCondition("hudHeart_empty", settings::tagEmpty, mCount - mCurrent);

    //расставляем в ряд
    const float size = 30.0f; //размер спрайтов
    const float wh = 35;
    float x = size * 0.5f;
    auto list = ecs::findsByTag<AComponentSprite>(this, settings::tagFull);
    ecs::findsByTag<AComponentSprite>(this, settings::tagEmpty, list);
    for (const auto &sprite : list)
    {
        sprite->setPosition({x, -size * 0.5f});
        sprite->setScale(size / sprite->width());
        x += wh;
    }

    mRefreshing = false;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// привести количество спрайтов в соотвветствие
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLives :: makeCondition(const std::string &name, const int tag, const int count)
{
    auto actor = getActor();
    if (!actor)
    {
        return;
    }
    const auto list = ecs::findsByTag<AComponentSprite>(this, tag);
    int im = count - list.size();
    for (int i = 0; i < im; i++)
    {
        //добавляем
        actor->create<AComponentSprite>(name, tag, 1000);
    }
    for (int i = 0; i < -im; i++)
    {
        //удоляем
        actor->remove(list[i]);
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// компаненты поменялись, чтото добавилось, чтото удалилось
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLives :: changeComponents()
{
    refresh();
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// проверка, есть жизни или нет
/// </summary>
///
///-------------------------------------------------------------------------
bool AComponentLives :: isEmpty() const
{
    return mCurrent == 0 ? true : false;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// уменьшить на одну жизнь
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLives :: reduce()
{
    mCurrent--;
    if (mCurrent < 0)
    {
        mCurrent = 0;
    }
    refresh();
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// увеличть одну жизнь
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLives::increase()
{
    mCurrent++;
    if (mCurrent < 0)
    {
        mCurrent = 1;
    }

    if (mCurrent > mCount)
    {
        mCount = mCurrent;
    }

    refresh();
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// востановить все жизни
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLives::restoreFull()
{
    if (mCurrent == mCount)
    {
        mCount++;
    }
    mCurrent = mCount;
    refresh();
}
///-------------------------------------------------------------------------


