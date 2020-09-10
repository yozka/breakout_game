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
    /// Сборщик окна проигрыша
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class ABuildGameOver
        :
            public ABuildEndGame
    {
        using super = ABuildEndGame;

    public:

        ABuildGameOver(ecs::AContainer *container);
    

    protected:



        void onBuild() override; //




    private:





    private:

 
    };
    ///-------------------------------------------------------------------------




}
