// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_DestroyBrick.h"
#include "Component_Geometry.h"
#include "Component_GeometryData.h"
#include "Component_ScrollCan.h"
#include "Component_ScrollDown.h"
#include "Component_Sprite.h"

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
AComponentDestroyBrick::AComponentDestroyBrick()
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
AComponentDestroyBrick::~AComponentDestroyBrick()
{

}
///-------------------------------------------------------------------------










 ///------------------------------------------------------------------------
///
/// <summary>
/// удалить себя
/// то на место блока, устанавливается его полупразрачная тень
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentDestroyBrick::destroy()
{
    const auto container = getContainer();
    const auto actor = getActor();
    if (!container || !actor)
    {
        return;
    }
    const auto geometry = actor->findComponent<AComponentGeometry>();
    if (!geometry) return;


    auto shadow = container->append(std::make_shared< ecs::AActor >());
    const auto shadowGeometry = shadow->create<AComponentGeometryData>(geometry->position(), geometry->boundingSize());
    shadow->create<AComponentSprite>("element_shadow_rectangle", 0, -1);
    shadow->create<AComponentScrollCan>();


    //добавим себя в скроллинг, если есть скролл
    if (const auto scroll = container->findComponent<AComponentScollDown>())
    {
        scroll->replacement(geometry, shadowGeometry);
    }


    //удалим блок
    container->remove(actor);
}
///-------------------------------------------------------------------------

