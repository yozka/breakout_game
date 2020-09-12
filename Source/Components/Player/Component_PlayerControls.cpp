// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_PlayerControls.h"
#include "Components/Graphics/Component_Geometry.h"
#include "Component_Cling.h"
#include "Component_Weapon.h"
#include "Utils/MathUtils.h"
#include "Device.h"


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
AComponentPlayerControls::AComponentPlayerControls()
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
AComponentPlayerControls::~AComponentPlayerControls()
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
bool AComponentPlayerControls::mouseDown(const dm::EventInput &input)
{
    if (input.mouseRigth)
    {
        if (const auto cling = findComponent<AComponentCling>())
        {
            return cling->runBall();
        }
    }

    if (input.mouseLeft)
    {
        if (const auto weapon = findComponent<AComponentWeapon>())
        {
            return weapon->runShot();
        }
    }
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
void AComponentPlayerControls::mouseMove(const dm::EventInput &input)
{
    const auto geometry = findComponent<AComponentGeometry>();
    if (!geometry)
    {
        return;
    }
    const auto size = geometry->boundingSize();
    const auto divx = size.x * 0.5f;
    const auto width = dm::deviceWidth() - divx;

    const auto pos = geometry->position();
    auto newPos = pos;
    newPos.x = static_cast<float>(input.position.x);
    if (newPos.x < divx)
    {
        newPos.x = divx;
    }else
        if (newPos.x > width)
        {
            newPos.x = width;
        }

    geometry->setPosition(newPos);

    if (!math::isEqualFloat(pos.x, 0.0f))
    {
        mVelocity += newPos.x - pos.x;
        mMoving = true;
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
void AComponentPlayerControls::mouseUp(const dm::EventInput &input)
{
    
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// при резком перемещении ракетки, она меняет угол наклона
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPlayerControls::update(const float timeSpan)
{
    if (!mMoving)
    {
        return;
    }

    const float speed = 200.0f;//скорость
    const float range = 500.0f;//максимальное отклонение в пикселях
    const float angle = 20.0f; //максимальное отклонение ракетки

    float dm = speed  * timeSpan;
    if (mVelocity > 0)
    {
        mVelocity -= dm;
        if (mVelocity < 0)
        {
            mVelocity = 0.0f;
            mMoving = false;
        }
    }
    else
    if (mVelocity < 0)
    {
        mVelocity += dm;
        if (mVelocity > 0)
        {
            mVelocity = 0.0f;
            mMoving = false;
        }

    }
    mVelocity = math::clamp(-range, range, mVelocity);


    //повернем ракетку
    if (const auto geometry = findComponent<AComponentGeometry>())
    {
        const float actualAngle = (angle / range) * -mVelocity;
        geometry->setAngle(actualAngle);
    }

}
///-------------------------------------------------------------------------



