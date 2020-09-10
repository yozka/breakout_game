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
    /// Если нет мячей, то из преобразуем одну жизнь в мяч
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentLivesToBall
        :
        public ecs::AComponentUpdate
    {
        using super = ecs::AComponentUpdate;

    public:

        AComponentLivesToBall();
        ~AComponentLivesToBall() override;


    public:

        void updateSlow(const float timeSpan) override;


    };
    ///-------------------------------------------------------------------------



}
