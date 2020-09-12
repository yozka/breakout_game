#pragma once
#include <memory>
#include <string>
#include <vector>


#include "Physics/Component_Collision.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Обработчик столкновения с физ объектом
    /// увеличиваем скорость у мяча
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentCLLSpeedBall
        :
        public AComponentCollision
    {
        using super = AComponentCollision;

    public:

        AComponentCLLSpeedBall();
        ~AComponentCLLSpeedBall() override;

    public:

        bool collision(const std::vector<FPoint> &contacts, const PComponentBody &body)override;//обработка контакта взаимодействия

    private:



    };
    ///-------------------------------------------------------------------------


    using PComponentCLLSpeedBall = std::shared_ptr< AComponentCLLSpeedBall >;

}
