// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_CLLSpeedBall.h"
#include "Component_Ball.h"
#include "Component_Paddle.h"
#include "Component_Brick.h"





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
AComponentCLLSpeedBall::AComponentCLLSpeedBall()
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
AComponentCLLSpeedBall::~AComponentCLLSpeedBall()
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
bool AComponentCLLSpeedBall::collision(const std::vector<FPoint> &contacts, const PComponentBody &body)
{
    const auto ball = findComponent<AComponentBall>();
    if (!ball)
    {
        return true;
    }

    if (body->isBall())
    {
        //удар между мечами не увеличивает скорость
        return true;
    }

    
    if (body->findComponent<AComponentPaddle>())
    {
        //удар по ракетке, уменьшим скорость
        ball->speedDecrement();
        return true;
    }

    if (body->findComponent<AComponentBrick>())
    {
        //удар по другим объектам увеличит скорость
        ball->speedIncrement();
        return true;
    }
    return true;
}
///-------------------------------------------------------------------------





