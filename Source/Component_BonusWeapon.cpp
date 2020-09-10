// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_BonusWeapon.h"
#include "Component_Weapon.h"
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
AComponentBonusWeapon::AComponentBonusWeapon()
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
AComponentBonusWeapon::~AComponentBonusWeapon()
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
void AComponentBonusWeapon::onUse()
{
    if (const auto container = getContainer())
    {
        if (const auto weapon = container->findComponent<AComponentWeapon>())
        {
            weapon->appendBullet(50);
        }
    }
}
///-------------------------------------------------------------------------




