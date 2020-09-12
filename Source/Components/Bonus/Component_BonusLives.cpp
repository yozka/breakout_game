// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_BonusLives.h"
#include "Components/Widget/Component_Lives.h"
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
AComponentBonusLives::AComponentBonusLives()
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
AComponentBonusLives::~AComponentBonusLives()
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
void AComponentBonusLives::onUse()
{
    if (const auto container = getContainer())
    {
        if (const auto lives = container->findComponent<AComponentLives>())
        {
            lives->increase();
        }
    }
}
///-------------------------------------------------------------------------




