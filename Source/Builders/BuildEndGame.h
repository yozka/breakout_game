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
    /// Сборщик окна конца игры
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class ABuildEndGame
    {


    public:

        ABuildEndGame(ecs::AContainer *container);
        virtual ~ABuildEndGame();

    public:




        void build(); //сборка




    protected:


        ecs::AContainer *mContainer; //контейнер с игровыми элементами


        virtual void onBuild() {};//сборка 



        //удаление компонентов полностью
        template <class T>
        void remove()
        {
            while (const auto obj = mContainer->findComponent<T>())
            {
                mContainer->remove(obj->getActor());
            }
        }

    };
    ///-------------------------------------------------------------------------




}
