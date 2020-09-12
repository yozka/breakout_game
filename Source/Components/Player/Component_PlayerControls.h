#pragma once
#include <memory>
#include <string>


#include "Systems/Component_Input.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Управление игровым объектом посредством мыш
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentPlayerControls
        :
        public AComponentInput
    {
        using super = AComponentInput;

    public:

        AComponentPlayerControls();
        ~AComponentPlayerControls();


        bool mouseDown  (const dm::EventInput &input) override;
        void mouseMove  (const dm::EventInput &input) override;
        void mouseUp    (const dm::EventInput &input) override;

        void update(const float timeSpan) override;

    private:


        bool mMoving = {false}; //ракетка в движении
        float mVelocity = 0.0f; //скорость перемещения ракетки


    };
    ///-------------------------------------------------------------------------




}
