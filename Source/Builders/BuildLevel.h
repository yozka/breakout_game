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
    /// Сборщик уровней
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class ABuildLevel
    {


    public:

        ABuildLevel(ecs::AContainer *container);
        virtual ~ABuildLevel();

    public:




        void build(); //сборка уровня




    private:


        ecs::AContainer *mContainer; //контейнер с игровыми элементами




    private:

        void makeBoundingArea(); //создадим ограничители
        void makeGameplay();//создадим базовый геймплей
        void makeLevel(const std::string &fileName); //создание уровня из файла

    };
    ///-------------------------------------------------------------------------




}
