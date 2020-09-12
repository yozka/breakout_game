#pragma once
#include <memory>
#include <string>
#include <vector>


#include "ecs/aaComponent.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Компонент показывающий и хранящий количество жизней
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentLives
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

        AComponentLives(const int count);
        ~AComponentLives() override;

        void changeComponents() override;//компоненты поменялись, что-то добавилось, что-то удалилось

    public:

        bool isEmpty() const; //проверка, есть жизни или нет
        void reduce(); //уменьшить на одну жизнь
        void increase(); //увеличть одну жизнь
        void restoreFull(); //востановить все жизни

    private:
        int         mCount      = {0}; //количество жизней всего
        int         mCurrent    = {0}; //текущее количество жизней

        bool        mRefreshing = {false}; //идет процесс обновления
    private:

        void refresh(); //обновить сотояние
        void makeCondition(const std::string &name, const int tag, const int count); //привести количество спрайтов в соотвветствие
    };
    ///-------------------------------------------------------------------------


    using PComponentLives = std::shared_ptr< AComponentLives >;

}
