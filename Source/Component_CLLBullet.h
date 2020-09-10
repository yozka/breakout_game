#pragma once
#include <memory>
#include <string>
#include <vector>


#include "Component_Collision.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Обработчик столкновения с физ объектом
    /// ударяется пуля
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentCLLBullet
        :
        public AComponentCollision
    {
        using super = AComponentCollision;

    public:

        AComponentCLLBullet();
        ~AComponentCLLBullet() override;

    public:

        bool collision(const std::vector<FPoint> &contacts, const PComponentBody &body)override;//обработка контакта взаимодействия

    private:

        int mContact = {10}; //количество контактов, потом себя удаляешь

        void destroySelf();//удалить себя
        void destroyBrick(const ecs::PActor &brick); //удалить кирпич
    };
    ///-------------------------------------------------------------------------


    using PComponentCLLBullet = std::shared_ptr< AComponentCLLBullet >;

}
