#pragma once
#include <memory>
#include <string>



#include "BuildEndGame.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Сборщик окна выигрыша
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class ABuildGameWins
        :
        public ABuildEndGame
    {
        using super = ABuildEndGame;

    public:

        ABuildGameWins(ecs::AContainer *container);


    protected:



        void onBuild() override; //




    private:





    private:


    };
    ///-------------------------------------------------------------------------




}
