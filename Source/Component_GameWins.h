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
    class AComponentGameWins
        :
        public ecs::AComponentUpdate
    {
        using super = ecs::AComponentUpdate;

    public:

        AComponentGameWins();
        ~AComponentGameWins() override;


    public:

        void update(const float timeSpan) override;

    private:

        bool  mComplete = { false }; //    

    };
    ///-------------------------------------------------------------------------



}
