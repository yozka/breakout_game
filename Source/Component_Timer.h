#pragma once
#include <memory>
#include <functional>

#include "ecs/update/aaComponent_Update.h"

namespace game
{
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// таймер
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentTimer
        :
        public ecs::AComponentUpdate
    {
        using super = ecs::AComponentUpdate;
        using functor = std::function<void(const AComponentTimer*)>;
    public:

        AComponentTimer(const float time, const functor &signal);
        ~AComponentTimer() override;


    public:

        void update(const float timeSpan) override;

    private:

        const float mTime = { 0 };
        float mCurrent = { 0 };
        functor mSignal = { nullptr };

    };
    ///-------------------------------------------------------------------------



}
