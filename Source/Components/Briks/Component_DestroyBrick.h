#pragma once
#include <memory>
#include <string>
#include <vector>


#include "ecs/aaComponent.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Корректное разрушение кирпича
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentDestroyBrick
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

        AComponentDestroyBrick();
        ~AComponentDestroyBrick() override;


        void destroy(); //удалить кирпич


    private:


    };
    ///-------------------------------------------------------------------------


    using PComponentDestroyBrick = std::shared_ptr< AComponentDestroyBrick >;

}
