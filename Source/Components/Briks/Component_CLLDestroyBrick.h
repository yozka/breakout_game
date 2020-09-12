#pragma once
#include <memory>
#include <string>



#include "Physics/Component_Collision.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Обработчик столкновения с физ объектом
    /// удаляем кирпичь, когда на него ударился шар
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentCLLDestroyBrick
        :
        public AComponentCollision
    {
        using super = AComponentCollision;

    public:

        AComponentCLLDestroyBrick();
        ~AComponentCLLDestroyBrick() override;

 
    public:

        bool collision(const std::vector<FPoint> &contacts, const PComponentBody &body)override;//обработка контакта взаимодействия

    private:
        
        void destroySelf();//удалить себя

    };
    ///-------------------------------------------------------------------------


    using PComponentCLLDestroyBrick = std::shared_ptr< AComponentCLLDestroyBrick >;

}
