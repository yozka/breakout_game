// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "ecs/utils/aaUtils.h"
#include "Device.h"

#include "Component_Paddle.h"
#include "Component_Body.h"
#include "Component_ShapePolygon.h"
#include "Component_Sprite.h"
#include "Component_Weapon.h"
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
AComponentPaddle::AComponentPaddle(const float length)
    :
        mBaseLength(length),
        mLength(length)
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
AComponentPaddle::~AComponentPaddle()
{

}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// обновление размеров ракетки
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPaddle::update(const float timeSpan)
{
    if (mChangeSize)
    {
        //нужно поменять размер
        resizing();
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
void AComponentPaddle :: changeComponents() 
{
    super::changeComponents();
    if (const auto body = findComponent<AComponentBody>())
    {
        body->setStatic();
        auto pos = body->position();
        pos.y = dm::deviceHeight() - 40.0f;
        if (math::isEqualFloat(pos.x, 0.0f))
        {
            pos.x = dm::deviceWidth() * 0.5f;
        }
        body->setPosition(pos);
    }
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// установим размер ракетки
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPaddle :: setLength(const float length)
{
    mLength = length;
    mChangeSize = true;
    resizing();

    if (const auto weapon = findComponent<AComponentWeapon>())
    {
        weapon->resize();
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// изменение размера ракетки
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPaddle :: resizing()
{
    mChangeSize = false;

    const float height = 32; //ширина ракетки
    const float lengthDiv = mLength * 0.5f;

    //размер физтела
    if (const auto shape = findComponent<AComponentShapePolygon>())
    {
        shape->setBox(lengthDiv, height * 0.5f);
    }
    else mChangeSize = true;

    //утсанавливам размер спрайтов ракетки
    //слева
    float widthCenter = mLength;
    if (const auto sprite = ecs::findByTag<AComponentSprite>(this, left))
    {
        sprite->setPosition({-lengthDiv + sprite->width() * 0.5f, 0.0f});
        widthCenter -= sprite->width();
    }
    else mChangeSize = true;
    //

    //справа
    if (const auto sprite = ecs::findByTag<AComponentSprite>(this, right))
    {
        sprite->setPosition({ lengthDiv - sprite->width() * 0.5f, 0.0f });
        widthCenter -= sprite->width();
    }
    else mChangeSize = true;
    //

    //центр
    if (const auto sprite = ecs::findByTag<AComponentSprite>(this, center))
    {
        const auto w = sprite->width();
        sprite->setScale({widthCenter / w, 1.0f});
    }
    else mChangeSize = true;
    
}
///-------------------------------------------------------------------------











 ///------------------------------------------------------------------------
///
/// <summary>
/// расширить ракетку
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPaddle :: expand()
{
    const float incf = 0.5f;
    const float maxlen = mBaseLength * 2.0f;
    const float newlen = mLength + mBaseLength * incf;
    const float dif = maxlen / newlen;
    const float cf = math::clamp(0.1f, 1.0f, dif);
    setLength(mLength + mBaseLength * incf * cf);
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// востановить ракетку в исходное состояние
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPaddle::reset()
{
    setLength(mBaseLength);
    if (const auto weapon = findComponent<AComponentWeapon>())
    {
        weapon->reset();
    }
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// скукожить ракетку
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPaddle::squeeze()
{
    const float sqlen = mBaseLength * 0.3f;
    const float len = math::clamp(sqlen, mLength, mLength - sqlen);
    setLength(len);
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// текущая длина ракетки
/// </summary>
///
///-------------------------------------------------------------------------
float AComponentPaddle::length() const
{
    return mLength;
}
///-------------------------------------------------------------------------




