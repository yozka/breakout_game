#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Utils/Point.h"

namespace dm
{

    float deviceWidth();
    float deviceHeight();

    sf::Sprite loadSprite(const std::string &name); //подгрузить спрайт

    struct EventInput
    {
        bool    mouseLeft   = { false };
        bool    mouseRigth  = { false };
        bool    mouseMove   = { false };
        IPoint  position    = { 0, 0};

        void clear()
        {
            mouseLeft = false;
            mouseRigth = false;
            mouseMove = false;
        }


    };


}
