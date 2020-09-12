#pragma once
#include <memory>



#include "Component_Bonus.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Бонус, увеличивает раздваивает уже существующие шары
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentBonusBall
        :
        public AComponentBonus
    {
        using super = AComponentBonus;

    public:

        AComponentBonusBall();
        ~AComponentBonusBall() override;




    protected:

        void onUse() override;

    };
    ///-------------------------------------------------------------------------


    using PComponentBonusBall = std::shared_ptr< AComponentBonusBall >;

}
