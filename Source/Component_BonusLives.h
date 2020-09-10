#pragma once
#include <memory>



#include "Component_Bonus.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Бонус, увеличивает количество жизней
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentBonusLives
        :
        public AComponentBonus
    {
        using super = AComponentBonus;

    public:

        AComponentBonusLives();
        ~AComponentBonusLives() override;




    protected:

        void onUse() override;

    };
    ///-------------------------------------------------------------------------


    using PComponentBonusLives = std::shared_ptr< AComponentBonusLives >;

}
