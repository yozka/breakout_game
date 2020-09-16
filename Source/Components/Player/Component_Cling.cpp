// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Utils/MathUtils.h"
#include "Component_Cling.h"
#include "Physics/Component_Body.h"
#include "Physics/Component_Shape.h"
#include "Components/Balls/Component_Ball.h"
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
AComponentCling::AComponentCling()
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
AComponentCling::~AComponentCling()
{

}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// обновление 
/// двигаем мяч к ракетке
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentCling::update(const float timeSpan)
{
    if (mActive)
    {
        moveBall();
    }
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// приклеить шар
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentCling::clingBall(const ecs::PActor &actor)
{
    mBall = actor;
    mActive = true;

    if (const auto body = mBall->findComponent<AComponentBody>(); body)
    {
        body->setBallSpeed(0);
    }
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// текущая позиция куда нужно приклеить шар
/// </summary>
///
///-------------------------------------------------------------------------
FPoint AComponentCling::position()
{
    const auto geometry = findComponent<AComponentGeometry>();
    const auto shapeA   = findComponent<AComponentShape>();
    const auto shapeB   = mBall->findComponent<AComponentShape>();

    if (!geometry || !shapeA || !shapeB)
    {
        return { 0.0f, 0.0f };
    }

    const auto pt1 = shapeB->getSupport({ 0.0f,  1.0f });
    const auto pt2 = shapeA->getSupport({ 0.0f, -1.0f});
    const auto dir = pt2.y - pt1.y;
    
    return geometry->position() + FPoint(0.0f, dir);
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// двигаем шар в центр рокетки
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentCling::moveBall()
{
    if (const auto body = mBall->findComponent<AComponentBody>(); body)
    {
        body->setPosition(position());
    }
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// запустить шар
/// </summary>
///
///-------------------------------------------------------------------------
bool AComponentCling::runBall()
{
    if (!mBall)
    {
        return false;
    }

    const auto ball = mBall->findComponent<AComponentBall>();
    if (!ball)
    {
        return false;
    }


    //
    FPoint force(0.0f, ball->powerImpulse());
    if (const auto geometry = findComponent<AComponentGeometry>(); geometry)
    {
        float angle = (math::PI / 180.0f) * geometry->angle() * 5.0f;
        const float range = math::PI * 0.4f;
        angle = math::clamp(-range, range, angle);
        math::matrix2 mat;
        mat.setAngle(angle);
        force = mat * force;
    }

    
    if (const auto body = mBall->findComponent<AComponentBody>(); body)
    {
        body->applyImpulse(force, {0.0f, 0.0f});
        body->setBallSpeed(ball->speedBall());
    }
    mBall = ecs::PActor();
    mActive = false;
    return true;
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// проверка, есть захваченный мяч или нет
/// </summary>
///
///-------------------------------------------------------------------------
bool AComponentCling::isEmpty() const
{
    return !mActive && !mBall;
}
