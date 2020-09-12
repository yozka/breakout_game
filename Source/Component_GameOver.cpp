// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_GameOver.h"
#include "Component_Ball.h"
#include "Component_Lives.h"
#include "BuildGameOver.h"

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
AComponentGameOver::AComponentGameOver()
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
AComponentGameOver::~AComponentGameOver()
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
void AComponentGameOver::updateSlow(const float timeSpan)
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

    if (container->findComponent<AComponentBall>())
    {
        //есть хоть один шар
        return;
    }

    const auto lives = container->findComponent<AComponentLives>();
    if (!lives)
    {
        //что-то нето, нет системы_жизней 
        return;
    }

    if (!lives->isEmpty())
    {
        //есть еще жизни
        return;
    }

   
    //нет жизней нет мячей, сделаем отсчет
    if (mTimeWait < 0)
    {
        return;
    }

    mTimeWait -=timeSpan;
    if (mTimeWait > 0)
    {
        return;
    }
    //

    //все. наступил полный геймова
    ABuildGameOver builder(container);
    builder.build();
    mComplete = true;
}
///-------------------------------------------------------------------------



