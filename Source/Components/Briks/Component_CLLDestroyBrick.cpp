// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_CLLDestroyBrick.h"
#include "Components/Balls/Component_Ball.h"
#include "Component_DestroyBrick.h"
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
AComponentCLLDestroyBrick::AComponentCLLDestroyBrick()
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
AComponentCLLDestroyBrick::~AComponentCLLDestroyBrick()
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
bool AComponentCLLDestroyBrick::collision(const std::vector<FPoint> &contacts, const PComponentBody &body)
{
    if (body->isBall() && body->findComponent<AComponentBall>())
    {
        //
        destroySelf();
    }
    return true;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// удалить себя
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentCLLDestroyBrick :: destroySelf()
{
    if (const auto destractor = findComponent<AComponentDestroyBrick>())
    {
        destractor->destroy();
        return;
    }
    
    //удалем по старинке
    auto container = getContainer();
    auto actor = getActor();
    if (container && actor)
    {
        container->remove(actor);
    }
}
///-------------------------------------------------------------------------














