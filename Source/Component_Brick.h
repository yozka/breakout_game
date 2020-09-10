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
   /// Кирпич который нужно разрушить
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentBrick
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

        AComponentBrick();
        ~AComponentBrick() override;

  

    private:


    };
    ///-------------------------------------------------------------------------


    using PComponentBrick = std::shared_ptr< AComponentBrick >;

}
