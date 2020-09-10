// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_Ball.h"
#include "Component_Body.h"
#include "MathUtils.h"



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
AComponentBall::AComponentBall(const float factor)
    :
        mFactor(factor)
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
AComponentBall::~AComponentBall()
{

}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// скорость выброса шара
/// </summary>
///
///-------------------------------------------------------------------------
float AComponentBall :: powerImpulse()const
{
    return mPowerImpulse * mFactor;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// номинальная скорость шара
/// </summary>
///
///-------------------------------------------------------------------------
float AComponentBall::speedBall()const
{
    return mSpeedBallMin * mFactor;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// уменьшение текущей скорости
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentBall::speedDecrement()
{
    if (const auto body = findComponent<AComponentBody>())
    {
        float speed = body->ballSpeed();
        if (math::isEqualFloat(speed, 0.0f))
        {
            return;
        }
        speed = speed * 0.95f;

        speed = math::clamp(mSpeedBallMin * mFactor, mSpeedBallMax * mFactor, speed);
        body->setBallSpeed(speed);
    }
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// увелечение текущей скорости
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentBall::speedIncrement()
{
    if (const auto body = findComponent<AComponentBody>())
    {
        float speed = body->ballSpeed();
        if (math::isEqualFloat(speed, 0.0f))
        {
            return;
        }

        speed += mSpeedBallMin * mFactor * 0.18f;

        speed = math::clamp(mSpeedBallMin * mFactor, mSpeedBallMax * mFactor, speed);
        body->setBallSpeed(speed);
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// сбросить скорость до медленной
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentBall :: speedSlow()
{
    mSpeedBallMin = mSpeedBallSlow;

    if (const auto body = findComponent<AComponentBody>())
    {
        float speed = body->ballSpeed();
        if (math::isEqualFloat(speed, 0.0f))
        {
            return;
        }
        body->setBallSpeed(mSpeedBallMin * mFactor);

        const auto velocity = body->velocity();
        body->setVelocity(velocity * 0.5f);
    }
}
///-------------------------------------------------------------------------

