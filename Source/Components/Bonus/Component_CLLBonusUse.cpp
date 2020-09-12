// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_CLLBonusUse.h"
#include "Component_Bonus.h"
#include "Components/Player/Component_Paddle.h"




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
AComponentCLLBonusUse::AComponentCLLBonusUse()
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
AComponentCLLBonusUse::~AComponentCLLBonusUse()
{

}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// обработка контакта взаимодействия
/// </summary>
///
///-------------------------------------------------------------------------
bool AComponentCLLBonusUse::collision(const std::vector<FPoint> &contacts, const PComponentBody &body)
{
    const auto paddle = body->findComponent<AComponentPaddle>();
    const auto bonus = findComponent<AComponentBonus>();
    if (paddle && bonus)
    {
        bonus->use();
    }
    return true;
}
///-------------------------------------------------------------------------












