#pragma once
#include <memory>
#include <string>
#include <vector>


#include "ecs/aaComponent.h"
#include "Component_Body.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Обработчик столкновения с физ объектом
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentCollision
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:


        virtual bool collision(const std::vector<FPoint> &contacts, const PComponentBody &body) = 0; //обработка контакта взаимодействия



    };
    ///-------------------------------------------------------------------------


    using PComponentCollision = std::shared_ptr< AComponentCollision >;

}
