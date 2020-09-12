// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_Button.h"
#include "Components/Graphics/Component_Geometry.h"
#include "Components/Graphics/Component_Sprite.h"
#include "Utils/MathUtils.h"
#include "Utils/Rect.h"
#include "ecs/utils/aaUtils.h"


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
AComponentButton::AComponentButton(const TSignal &signal)
    :
        mSignalClick(signal)
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
AComponentButton::~AComponentButton()
{

}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// нажатие на кнопку мыш
/// </summary>
///
///-------------------------------------------------------------------------
bool AComponentButton::mouseDown(const dm::EventInput &input)
{
    if (isArea(input.position) && input.mouseLeft)
    {
        mPushed = true;
        changeStatus(pushed);
        return true;
    }

    //нажали в пустую область
    mPushed = false;
    changeStatus(none);
    return false;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// двжиение мыш
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentButton::mouseMove(const dm::EventInput &input)
{
    if (!isArea(input.position))
    {
        //мыша не находится на кнопке
        changeStatus(none);
        return;
    }
    //мыша под кнопкой
    if (mPushed)
    {
        changeStatus(pushed);
    }
    else
    {
        changeStatus(hover);
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// опыстили кнопку мыш
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentButton::mouseUp(const dm::EventInput &input)
{
    mPushed = false;
    if (!isArea(input.position))
    {
        changeStatus(none);
        return;
    }
    changeStatus(hover);

    if (mSignalClick)
    {
        mSignalClick();
    }
}
///-------------------------------------------------------------------------








 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentButton::update(const float timeSpan)
{
   
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// установка нового статуса
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentButton::changeStatus(const STATUS &st)
{
    if (st == mStatus)
    {
        return;
    }
    mStatus = st;

    const auto sNormal  = ecs::findByTag<AComponentSprite>(this, tagNormal);
    const auto sPushed  = ecs::findByTag<AComponentSprite>(this, tagPushed);
    const auto sHover   = ecs::findByTag<AComponentSprite>(this, tagHover);

    if (!sNormal || !sPushed || !sHover)
    {
        return;
    }

    switch ( mStatus)
    {
        case none:   sNormal->setVisible(true);  sPushed->setVisible(false); sHover->setVisible(false);break;
        case hover:  sNormal->setVisible(false); sPushed->setVisible(false); sHover->setVisible(true); break;
        case pushed: sNormal->setVisible(false); sPushed->setVisible(true);  sHover->setVisible(false); break;
    }
    
    correctIcon();
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// првоерка, мышка находится на кнопке или нет
/// </summary>
///
///-------------------------------------------------------------------------
bool AComponentButton::isArea(const IPoint &mouse) const
{
    if (const auto geometry = findComponent<AComponentGeometry>())
    {
        const auto size = geometry->boundingSize();
        const auto pos = geometry->position() - size * 0.5f;

        IRect rect(pos.x, pos.x + size.x, pos.y, pos.y + size.y);
        return rect.contains(mouse);
    }
    return false;
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// выставляем корректную позицию иконки, взависемости нажата или нет кнопка
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentButton::correctIcon()
{
    if (const auto sIcon = ecs::findByTag<AComponentSprite>(this, tagIcon))
    {
        switch (mStatus)
        {
            case none:
            case hover:
                sIcon->setPosition({ 0, -3 });
                break;

            case pushed:
                sIcon->setPosition({ 0, 0 });
                break;
        }
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
void AComponentButton::changeComponents()
{
    correctIcon();
}