#pragma once
#include <memory>

#include "ecs/aaSystem.h"
#include "Components/Graphics/Component_Draw.h"


namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------






     ///------------------------------------------------------------------------
    ///
    ///
    ///
    /// Система отрисовки компонентов
    ///
    ///
    ///-------------------------------------------------------------------------
    class ASystemRenderDraw
        :
        public ecs::ASystem<AComponentDraw>
    {
        using super = ecs::ASystem<AComponentDraw>;
    public:


        ASystemRenderDraw();
        ~ASystemRenderDraw() override;



        ///-------------------------------------------------------------------------

    public:

        void refreshComponents() override;
        void draw(dm::ARender &render);


    };
    ///-------------------------------------------------------------------------




}
