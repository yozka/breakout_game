#pragma once
#include <memory>



#include "ecs/aaComponent.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Оружие
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentWeapon
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

        AComponentWeapon();
        ~AComponentWeapon() override;

    public:


        //спрайты оружия
        enum eWeaponTag : int
        {
            left = 10,
            right = 11,
            bulletPanel = 12,
            bulletNumber = 13
            
        };

    public:


        void assignContainer() override; //доавляем себя в контейнера

    public:

        void resize(); //изменить размеры
        void appendBullet(const int count); //добавить патроны
        void reset(); //убрать все патроноы

        bool runShot(); //сделать один выстрел

    private:

        int mBullet = { 0 }; //текущее количество патронов

        float position() const; //выесним позицию где должны находится оружие


    };
    ///-------------------------------------------------------------------------


    using PComponentWeapon = std::shared_ptr< AComponentWeapon >;

}
