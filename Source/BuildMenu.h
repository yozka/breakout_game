#pragma once
#include <memory>
#include <string>



#include "ecs/aaContainer.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Сборщик главного меню
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class ABuildMenu
    {


    public:

        ABuildMenu(ecs::AContainer *container);
        virtual ~ABuildMenu();

    public:




        void build(); //сборка меню




    private:


        ecs::AContainer *mContainer; //контейнер с игровыми элементами




    private:

        void makeBanner();
        void makeBrick(const float posY);
        void makeSpawnBall();
    };
    ///-------------------------------------------------------------------------




}
