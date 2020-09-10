// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "BuildGameWins.h"
#include "Device.h"

#include "Component_GeometryData.h"
#include "Component_Sprite.h"

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
ABuildGameWins::ABuildGameWins(ecs::AContainer *container)
    :
    super(container)
{


}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// Сборка 
/// </summary>
///
///-------------------------------------------------------------------------
void ABuildGameWins::onBuild()
{
    const float width = dm::deviceWidth();
    const float height = dm::deviceHeight();


    auto obj = mContainer->append(std::make_shared< ecs::AActor >());
    obj->create<AComponentGeometryData>(FPoint({ width * 0.5f, height * 0.3f }));
    obj->create<AComponentSprite>("banner_game_wins", 0, 100);
}
///-------------------------------------------------------------------------









