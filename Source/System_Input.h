#pragma once
#include <memory>

#include "Device.h"
#include "ecs/aaSystem.h"
#include "Component_Input.h"


namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------






     ///------------------------------------------------------------------------
    ///
    ///
    ///
    /// Система обработки пользовательского ввода
    ///
    ///
    ///-------------------------------------------------------------------------
    class ASystemInput
        :
        public ecs::ASystem<AComponentInput>
    {
    public:


        ASystemInput();
        ~ASystemInput() override;



        ///-------------------------------------------------------------------------

    public:


        bool mouseDown      (const dm::EventInput &input);
        void mouseMove      (const dm::EventInput &input);
        void mouseUp        (const dm::EventInput &input);



        void update         (const float timeSpan);

        ///-------------------------------------------------------------------------

    private:




    };
    ///-------------------------------------------------------------------------




}
