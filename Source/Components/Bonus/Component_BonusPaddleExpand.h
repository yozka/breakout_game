#pragma once
#include <memory>



#include "Component_Bonus.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Бонус, увеличивает ракетку игрока
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentBonusPaddleExpand
        :
        public AComponentBonus
    {
        using super = AComponentBonus;

    public:

        AComponentBonusPaddleExpand();
        ~AComponentBonusPaddleExpand() override;




    protected:

        void onUse() override;

    };
    ///-------------------------------------------------------------------------


    using PComponentBonusPaddleExpand = std::shared_ptr< AComponentBonusPaddleExpand >;

}
