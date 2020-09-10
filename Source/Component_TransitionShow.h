#pragma once
#include <memory>
#include <string>
#include <vector>
#include <functional>

#include "Component_Transition.h"

namespace game
{
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Переход между экранами
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentTransitionShow
        :
        public AComponentTransition
    {
        using super = AComponentTransition;

    public:

        AComponentTransitionShow(const int cols, const int rows, const std::function<void()> &completed);
        ~AComponentTransitionShow() override;


    public:

        void update(const float timeSpan) override;


    private:

        std::function<void()> mCompleted = { nullptr };

        float mTime = { 0.0f };
    };
    ///-------------------------------------------------------------------------



}
