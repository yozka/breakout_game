#pragma once
#include <memory>



#include "Component_Bonus.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Бонус, скукоживает ракетку игрока до минимального значения
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentBonusPaddleSqueeze
        :
        public AComponentBonus
    {
        using super = AComponentBonus;

    public:

        AComponentBonusPaddleSqueeze();
        ~AComponentBonusPaddleSqueeze() override;




    protected:

        void onUse() override;

    };
    ///-------------------------------------------------------------------------


    using PComponentBonusPaddleSqueeze = std::shared_ptr< AComponentBonusPaddleSqueeze >;

}
