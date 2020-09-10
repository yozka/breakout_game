#pragma once
#include <memory>



#include "ecs/aaComponent.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Бонус, который можно получить
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentBonus
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

        AComponentBonus();
        ~AComponentBonus() override;
    
    public:

        void use(); //использовать бонус


    protected:
    
        virtual void onUse() {};

    private:
        bool mUsing = false; //бонус не исопльзован

    };
    ///-------------------------------------------------------------------------


    using PComponentBonus = std::shared_ptr< AComponentBonus >;

}
