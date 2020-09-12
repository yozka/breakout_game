#pragma once
#include <memory>



#include "Component_Bonus.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Бонус, заполняет всю линейку жизней
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentBonusLivesFull
        :
        public AComponentBonus
    {
        using super = AComponentBonus;

    public:

        AComponentBonusLivesFull();
        ~AComponentBonusLivesFull() override;




    protected:

        void onUse() override;

    };
    ///-------------------------------------------------------------------------


    using PComponentBonusLivesFull = std::shared_ptr< AComponentBonusLivesFull >;

}
