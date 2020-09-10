#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Point.h"
#include "ecs/update/aaComponent_Update.h"

namespace game
{




     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Штука которая приклеивает шарик, и выпускает его со силой
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentCling
        :
        public ecs::AComponentUpdate
    {
        using super = ecs::AComponentUpdate;

    public:

        AComponentCling();
        ~AComponentCling() override;



    public:

        void update(const float timeSpan) override;



    public:

        bool isEmpty() const; //проверка, есть захваченный мяч или нет

        void clingBall(const ecs::PActor &actor); //приклеить шар
        bool runBall(); //запустить шар
        

    private:

        ecs::PActor     mBall;
        bool            mActive = {false}; //шар приклеен или нет

    private:
        
        void moveBall(); //двигаем шар
        FPoint position(); //текущая позиция куда нужно приклеить шар
    };
    ///-------------------------------------------------------------------------


    using PComponentCling = std::shared_ptr< AComponentCling >;

}
