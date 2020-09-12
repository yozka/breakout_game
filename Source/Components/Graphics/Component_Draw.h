#pragma once
#include <memory>
#include <string>

#include "Render.h"
#include "ecs/aaComponent.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Компонент который может отрисовыватся на экране
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentDraw
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

        AComponentDraw(const int depth = 0)
            :
                depth(depth)
        {

        }
        const int depth = { 0 }; //глубина отрисовки


        virtual bool isVisible() const = 0; //проверка спрайт нужно отрисовывать или нет
        virtual void draw(dm::ARender &render) = 0; //отрисовка 
    






    };
    ///-------------------------------------------------------------------------



    ///-------------------------------------------------------------------------
    using PComponentDraw = std::shared_ptr< AComponentDraw >;
    ///-------------------------------------------------------------------------




}
