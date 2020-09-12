// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_LivesToBall.h"
#include "Components/Balls/Component_Ball.h"
#include "Components/Widget/Component_Lives.h"
#include "Components/Player/Component_Cling.h"
#include "Components/Player/Component_Paddle.h"
#include "Components/Options/Component_Options.h"

#include "Builders/CreatorGameObject.h"
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
AComponentLivesToBall::AComponentLivesToBall()
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
AComponentLivesToBall::~AComponentLivesToBall()
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
void AComponentLivesToBall::updateSlow(const float timeSpan)
{
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
    const auto cling = container->findComponent<AComponentCling>();
    if (!lives || !cling)
    {
        //что-то нето, нет системы_жизней 
        //и нету штуки к которой приклеиваются мячи
        return;
    }
    
    if (lives->isEmpty())
    {
        //жизней больше нет
        return;
    }

    if (!cling->isEmpty())
    {
        //ракетка занята какимто мячом
        return;
    }


    //уменьшим количество жизней и выпустим новй шар
    lives->reduce();

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

    //также, востановим ракетку
    if (const auto paddle = container->findComponent<AComponentPaddle>())
    {
        paddle->reset();
    }
}
///-------------------------------------------------------------------------



