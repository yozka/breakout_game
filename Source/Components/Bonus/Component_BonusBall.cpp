// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_BonusBall.h"
#include "Components/Balls/Component_Ball.h"
#include "Components/Options/Component_Options.h"
#include "Builders/CreatorGameObject.h"
#include "Physics/Component_Body.h"
#include "Utils/MathUtils.h"
#include "Utils/base_Random.h"

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
AComponentBonusBall::AComponentBonusBall()
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
AComponentBonusBall::~AComponentBonusBall()
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
void AComponentBonusBall::onUse()
{
    const auto container = getContainer();
    if (!container) return;

    ACreatorGameObject creator;
    const auto &random = dm::ARandom::instance();

    //возьмем из настроек скорость шара
    int speedBall = 100;
    if (const auto options = container->findComponent<parser::AComponentOptions>())
    {
        speedBall = options->speedBall();
    }
    //

    for (const auto &parentBall : container->findComponents<AComponentBall>())
    {
        const auto parentBody = parentBall->findComponent<AComponentBody>();
        if (!parentBody) continue;
        parentBody->setBallSpeed(parentBall->speedBall());

        //создадим новый шар
        const float scale = random.next(0.8f, 1.5f);
        const auto ball = creator.createBall(speedBall, parentBody->position(), scale);
        const auto body = ball->findComponent<AComponentBody>();
        if (!body) continue;
        container->append(ball);

        //зададим направление
        const auto mass = parentBody->massInverse();
        if (!math::isEqualFloat(mass, 0.0f))
        {
            const auto impulse = parentBody->velocity() / mass;
            body->applyImpulse(impulse, {0.0f, 0.0f});
        }
        body->setBallSpeed(parentBall->speedBall());
    }


}
///-------------------------------------------------------------------------




