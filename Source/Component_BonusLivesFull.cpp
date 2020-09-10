// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_BonusLivesFull.h"
#include "Component_Lives.h"
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
AComponentBonusLivesFull::AComponentBonusLivesFull()
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
AComponentBonusLivesFull::~AComponentBonusLivesFull()
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
void AComponentBonusLivesFull::onUse()
{
    if (const auto container = getContainer())
    {
        if (const auto lives = container->findComponent<AComponentLives>())
        {
            lives->restoreFull();
        }
    }
}
///-------------------------------------------------------------------------




