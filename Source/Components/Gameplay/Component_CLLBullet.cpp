// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_CLLBullet.h"
#include "Components/Balls/Component_Ball.h"
#include "Components/Briks/Component_Brick.h"
#include "Components/Briks/Component_DestroyBrick.h"

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
AComponentCLLBullet::AComponentCLLBullet()
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
AComponentCLLBullet::~AComponentCLLBullet()
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
bool AComponentCLLBullet::collision(const std::vector<FPoint> &contacts, const PComponentBody &body)
{
    if (body->findComponent<AComponentBrick>())
    {
        //
        destroyBrick(body->getActor());
        destroySelf();
        return true;
    }
    
    if (body->findComponent<AComponentCLLBullet>())
    {
        destroySelf();
        return true;
    }

    if (body->findComponent<AComponentBall>())
    {
        destroySelf();
        return true;
    }

    mContact--;
    if (mContact < 0)
    {
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
void AComponentCLLBullet::destroySelf()
{
    auto container = getContainer();
    auto actor = getActor();
    if (container && actor)
    {
        container->remove(actor);
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// удалить кирпич
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentCLLBullet:: destroyBrick(const ecs::PActor &brick)
{
    if (!brick)
    {
        return;
    }

    if (const auto destractor = brick->findComponent<AComponentDestroyBrick>())
    {
        destractor->destroy();
        return;
    }

    if (const auto container = getContainer())
    {
        container->remove(brick);
    }
}
///-------------------------------------------------------------------------



