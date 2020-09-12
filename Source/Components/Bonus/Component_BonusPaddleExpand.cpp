// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_BonusPaddleExpand.h"
#include "Components/Player/Component_Paddle.h"

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
AComponentBonusPaddleExpand::AComponentBonusPaddleExpand()
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
AComponentBonusPaddleExpand::~AComponentBonusPaddleExpand()
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
void AComponentBonusPaddleExpand::onUse()
{
    if (const auto container = getContainer())
    {
        if (const auto paddle = container->findComponent<AComponentPaddle>())
        {
            paddle->expand();
        }
    }
}
///-------------------------------------------------------------------------




