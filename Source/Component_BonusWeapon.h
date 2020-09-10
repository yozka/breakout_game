#pragma once
#include <memory>



#include "Component_Bonus.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Бонус, устанавилвает оружие, которое может стрелять по блокам
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentBonusWeapon
        :
        public AComponentBonus
    {
        using super = AComponentBonus;

    public:

        AComponentBonusWeapon();
        ~AComponentBonusWeapon() override;




    protected:

        void onUse() override;

    };
    ///-------------------------------------------------------------------------


    using PComponentBonusWeapon = std::shared_ptr< AComponentBonusWeapon >;

}
