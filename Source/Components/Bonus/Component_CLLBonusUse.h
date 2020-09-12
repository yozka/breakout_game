#pragma once
#include <memory>



#include "Physics/Component_Collision.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Обработчик столкновения с физ объектом
    /// используем бонус, если он соприкоснулся с ракеткой
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentCLLBonusUse
        :
        public AComponentCollision
    {
        using super = AComponentCollision;

    public:

        AComponentCLLBonusUse();
        ~AComponentCLLBonusUse() override;

    public:

        bool collision(const std::vector<FPoint> &contacts, const PComponentBody &body)override;//обработка контакта взаимодействия



    };
    ///-------------------------------------------------------------------------


    using PComponentCLLBonusUse = std::shared_ptr< AComponentCLLBonusUse >;

}
