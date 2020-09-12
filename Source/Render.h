#pragma once
#include <memory>
#include <list>
#include <SFML/Graphics.hpp>
#include "Utils/Point.h"

namespace dm
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------






     ///------------------------------------------------------------------------
    ///
    ///
    ///
    /// Система отрисовки
    ///
    ///
    ///-------------------------------------------------------------------------
    class ARender
    {
    public:

        ARender(sf::RenderTarget &target);
        virtual ~ARender();

    public:

        void pushMatrix();
        void popMatrix();
        
        void matrixTranslate(const FPoint &position);
        void matrixRotate(const float angle);

        void render(const sf::Drawable& drawable);


    private:

        sf::RenderTarget &mTarget;


        sf::RenderStates                mStates = {sf::RenderStates::Default};
        std::list< sf::RenderStates >   mStack; //хранение предыдущих состояний

    };
    ///-------------------------------------------------------------------------


}
