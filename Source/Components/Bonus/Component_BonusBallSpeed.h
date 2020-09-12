#pragma once
#include <memory>



#include "Component_Bonus.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Бонус, уменьшает скорость шаров
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentBonusBallSpeed
        :
        public AComponentBonus
    {
        using super = AComponentBonus;

    public:

        AComponentBonusBallSpeed();
        ~AComponentBonusBallSpeed() override;




    protected:

        void onUse() override;

    };
    ///-------------------------------------------------------------------------


    using PComponentBonusBallSpeed = std::shared_ptr< AComponentBonusBallSpeed >;

}
