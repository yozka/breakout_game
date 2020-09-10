#pragma once
#include <memory>
#include <string>
#include <vector>


#include "ecs/update/aaComponent_Update.h"

namespace game
{
    ///-------------------------------------------------------------------------
    namespace settings
    {
        constexpr float wait_time = 15; //время ожидания для следующего мяча 10сек
    }




     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Проверка, если нет активности, но есть мяч, то сгенерируем новый мяч
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentWaitToBall
        :
        public ecs::AComponentUpdate
    {
        using super = ecs::AComponentUpdate;

    public:

        AComponentWaitToBall();
        ~AComponentWaitToBall() override;


    public:

        void updateSlow(const float timeSpan) override;

    private:
        
        float mTime = {0.0f}; //время ожидания
        size_t mCounter = {0}; //количество активностей


        void resetTime(); //сбросить время

    };
    ///-------------------------------------------------------------------------



}
