// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_WaitToBall.h"
#include "Component_Ball.h"
#include "Component_Cling.h"
#include "Component_Paddle.h"
#include "Component_CLLCounter.h"
#include "Component_Options.h"

#include "CreatorGameObject.h"
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
AComponentWaitToBall::AComponentWaitToBall()
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
AComponentWaitToBall::~AComponentWaitToBall()
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
void AComponentWaitToBall::updateSlow(const float timeSpan)
{
    const auto container = getContainer();
    if (!container)
    {
        mTime = 0.0f;
        return;
    }

    if (!container->findComponent<AComponentBall>())
    {
        //нет шаров
        mTime = 0.0f;
        return;
    }

    const auto paddle   = container->findComponent<AComponentPaddle>();
    const auto cling    = container->findComponent<AComponentCling>();
    if (!paddle || !cling)
    {
        //чтото нето, нету штуки ккоторой приклеиваются мячи
        mTime = 0.0f;
        return;
    }


    if (!cling->isEmpty())
    {
        //ракетка занята какимто мячом
        mTime = 0.0f;
        return;
    }

    const auto counter = paddle->findComponent<AComponentCLLCounter<AComponentBall>>();
    if (!counter)
    {
        mTime = 0.0f;
        return;
    }

    const auto contact = mCounter;
    mCounter = counter->contactCount();
    if (contact != mCounter)
    {
        mTime = 0.0f;
        return;
    }


    mTime += timeSpan;
    if (mTime < settings::wait_time)
    {
        //время еще не прошло
        return;
    }
    mTime = 0;

    //возьмем из настроек скорость шара
    int speedBall = 100;
    if (const auto options = container->findComponent<parser::AComponentOptions>())
    {
        speedBall = options->speedBall();
    }
    //
    
    ACreatorGameObject creator;
    auto ball = container->append(creator.createBall(speedBall));
    cling->clingBall(ball);

}
///-------------------------------------------------------------------------



