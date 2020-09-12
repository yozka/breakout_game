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
    /// Шар
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentBall
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

        AComponentBall(const float factor);
        ~AComponentBall() override;

    public:

        float powerImpulse()const; //скорость выброса шара
        float speedBall()const; //номинальная скорость шара

    public:

        void speedDecrement(); //уменьшение текущей скорости
        void speedIncrement(); //увелечение текущей скорости
        void speedSlow(); //сбросить скорость до медленной
        

    private:

        float mFactor           = { 1.0f }; //множитель скорости

        float mPowerImpulse     = { 500000.0f }; //мощность отскока
        float mSpeedBallMin     = { 100000.0f }; //номинальная скорость мяча
        float mSpeedBallMax     = { 600000.0f }; //максимальная скорость мяча

        float mSpeedBallSlow    = {  40000.0f }; //очень медленная скорость мяча
    };
    ///-------------------------------------------------------------------------


    using PComponentBall = std::shared_ptr< AComponentBall >;

}
