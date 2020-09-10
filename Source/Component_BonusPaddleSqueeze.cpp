// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_BonusPaddleSqueeze.h"
#include "Component_Paddle.h"
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
AComponentBonusPaddleSqueeze::AComponentBonusPaddleSqueeze()
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
AComponentBonusPaddleSqueeze::~AComponentBonusPaddleSqueeze()
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
void AComponentBonusPaddleSqueeze::onUse()
{
    if (const auto container = getContainer())
    {
        if (const auto paddle = container->findComponent<AComponentPaddle>())
        {
            paddle->squeeze();
        }
    }
}
///-------------------------------------------------------------------------




