#pragma once
#include <memory>
#include <string>


#include "ecs/aaActor.h"
#include "Point.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------
    




     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Сборщик игровых сущностей
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class ACreatorGameObject
    {


    public:

        ACreatorGameObject();
        virtual ~ACreatorGameObject();

    public:


        ecs::PActor createPaddle            (const float length); //создание платформы игрока
        ecs::PActor createBall              (const int speed, const FPoint &position = {0.0f, 0.0f}, const float scale = 1.0f); //созать шар

        ecs::PActor createBrick_blueRect    (const FPoint &position, const float angle); //создать синий кирпич
        ecs::PActor createBrick_greenRect   (const FPoint &position, const float angle);
        ecs::PActor createBrick_greyRect    (const FPoint &position, const float angle);
        ecs::PActor createBrick_purpleRect  (const FPoint &position, const float angle);
        ecs::PActor createBrick_redRect     (const FPoint &position, const float angle);
        ecs::PActor createBrick_yellowRect  (const FPoint &position, const float angle);

        ecs::PActor createBrick_blueSquare  (const FPoint &position, const float angle);
        ecs::PActor createBrick_greenSquare (const FPoint &position, const float angle);
        ecs::PActor createBrick_greySquare  (const FPoint &position, const float angle);
        ecs::PActor createBrick_purpleSquare(const FPoint &position, const float angle);
        ecs::PActor createBrick_redSquare   (const FPoint &position, const float angle);
        ecs::PActor createBrick_yellowSquare(const FPoint &position, const float angle);


  


        ecs::PActor createBonus_lives           (const FPoint &position); //бонус, прибавить одну жизнь
        ecs::PActor createBonus_livesFull       (const FPoint &position); //бонус, увеличивает все потраченные жизни
        ecs::PActor createBonus_paddleExpand    (const FPoint &position); //бонус, увеличивает ракетку
        ecs::PActor createBonus_paddleSqueeze   (const FPoint &position); //бонус, уменьшает ракетку
        ecs::PActor createBonus_ball            (const FPoint &position); //бонус, удваевает шары
        ecs::PActor createBonus_ballSpeed       (const FPoint &position); //бонус, уменьшает скорость шаров
        ecs::PActor createBonus_weapon          (const FPoint &position); //бонус, оружие


        ecs::PActor createBullet(const FPoint &position, const FPoint &direct); //создание пули
        
    private:

        ecs::PActor createBrick(const std::string &name, const FPoint &position, const float angle);
        ecs::PActor createBonus(const FPoint &position); //бонус


    };
    ///-------------------------------------------------------------------------



  



}
