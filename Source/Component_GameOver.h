#pragma once
#include <memory>
#include <string>
#include <vector>


#include "ecs/update/aaComponent_Update.h"

namespace game
{
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Проверяет, когда игра закончена
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentGameOver
        :
        public ecs::AComponentUpdate
    {
        using super = ecs::AComponentUpdate;

    public:

        AComponentGameOver();
        ~AComponentGameOver() override;


    public:

        void updateSlow(const float timeSpan) override;

    private:

        bool  mComplete = { false }; //конец игры произошел
        float mTimeWait = { 2.0f }; //ожидаем 2 сек

    };
    ///-------------------------------------------------------------------------



}
