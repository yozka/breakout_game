// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_BonusBallSpeed.h"
#include "Component_Ball.h"
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
AComponentBonusBallSpeed::AComponentBonusBallSpeed()
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
AComponentBonusBallSpeed::~AComponentBonusBallSpeed()
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
void AComponentBonusBallSpeed::onUse()
{
    const auto container = getContainer();
    if (!container) return;

    for (const auto &ball : container->findComponents<AComponentBall>())
    {
        ball->speedSlow();
    }
}
///-------------------------------------------------------------------------




