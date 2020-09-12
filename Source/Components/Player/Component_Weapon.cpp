// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_Weapon.h"
#include "Component_Paddle.h"

#include "Builders/CreatorGameObject.h"
#include "Components/Graphics/Component_Sprite.h"
#include "Components/Graphics/Component_Geometry.h"
#include "Components/Graphics/Component_DrawNumber.h"

#include "ecs/utils/aaUtils.h"
#include "ecs/aaContainer.h"


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
AComponentWeapon::AComponentWeapon()
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
AComponentWeapon::~AComponentWeapon()
{

}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// доавляем себя в контейнера
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentWeapon::assignContainer()
{
    resize();
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// изменить размеры
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentWeapon::resize()
{
    const bool enabled = mBullet > 0 ? true : false;
    const auto lengthDiv = position();
    const float top = -5.0f;
    if (const auto sprite = ecs::findByTag<AComponentSprite>(this, left))
    {
        sprite->setPosition({ -lengthDiv, top });
        sprite->setVisible(enabled);
    }

    if (const auto sprite = ecs::findByTag<AComponentSprite>(this, right))
    {
        sprite->setPosition({ lengthDiv, top });
        sprite->setVisible(enabled);
    }

    if (const auto sprite = ecs::findByTag<AComponentSprite>(this, bulletPanel))
    {
        sprite->setVisible(enabled);
    }

    if (const auto label = ecs::findByTag<AComponentDrawNumber>(this, bulletNumber))
    {
        label->setNumber(mBullet);
        label->setVisible(enabled);
    }
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// убрать все патроноы
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentWeapon::reset()
{
    mBullet = 0;
    resize();
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// выесним позицию где должны находится оружие
/// </summary>
///
///-------------------------------------------------------------------------
float AComponentWeapon::position() const
{
    if (const auto paddle = findComponent<AComponentPaddle>())
    {
        return paddle->length() * 0.5f - 20.0f;
    }
    
    return 50.0f;
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// добавить патроны
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentWeapon::appendBullet(const int count)
{
    mBullet += count;
    resize();
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// сделать один выстрел
/// </summary>
///
///-------------------------------------------------------------------------
bool AComponentWeapon::runShot()
{
    const auto container = getContainer();
    const auto geometry = findComponent<AComponentGeometry>();
    if (!geometry || !container || mBullet <= 0)
    {
        return false;
    }

    mBullet--;


    const FPoint force = FPoint(0.0f, -1.0f);

    
    const auto pos = position();
    const float top = -40.0f;

    ACreatorGameObject creator;
    container->append(creator.createBullet(geometry->position() + FPoint(-pos, top), force));
    container->append(creator.createBullet(geometry->position() + FPoint( pos, top), force));

    resize();
    return true;
}
///-------------------------------------------------------------------------



