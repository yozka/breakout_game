// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_GameWins.h"
#include "Component_LevelContent.h"
#include "Components/Briks/Component_Brick.h"
#include "Builders/BuildGameWins.h"

#include "ecs/aaContainer.h"
///-------------------------------------------------------------------------




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
AComponentGameWins::AComponentGameWins()
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
AComponentGameWins::~AComponentGameWins()
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
void AComponentGameWins::update(const float timeSpan)
{
    if (mComplete)
    {
        return;
    }

    const auto container = getContainer();
    if (!container)
    {
        return;
    }

    if (container->findComponent<AComponentBrick>())
    {
        //есть хоть один блок
        return;
    }


    if (const auto level = container->findComponent<AComponentLevelContent>())
    {
        if (!level->isEmpty())
        {
            //уровень еще не пройден
            return;
        }
    }

    //все. наступил полный выигрышь
    ABuildGameWins builder(container);
    builder.build();
    mComplete = true;
}
///-------------------------------------------------------------------------



