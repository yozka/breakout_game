// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <SFML/Graphics.hpp>

#include "Device.h"
#include "Render.h"
#include "ArcanoidScena.h"


#include <windows.h>


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(static_cast<int>(dm::deviceWidth()), static_cast<int>(dm::deviceHeight())), "Breakout Game", sf::Style::Default, settings);

    dm::EventInput input;

    dm::ARender render(window);
    game::AArcanoidScena scena;
    scena.beginGame();
    sf::Clock clock;
    sf::Time timeLast = clock.getElapsedTime();
    while (window.isOpen())
    {
        //обрабатываем ввод
        input.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed    : window.close(); break;
            case sf::Event::MouseMoved:
            {
                const auto pt = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
                input.position  = { pt.x, pt.y }; 
                input.mouseMove = true; 
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                input.mouseLeft  |= event.mouseButton.button == sf::Mouse::Left;
                input.mouseRigth |= event.mouseButton.button == sf::Mouse::Right;
                break;
            }

            default:
                break;
            }
            
        }
        //

        //время и запуск логики
        auto timeNew = clock.getElapsedTime();
        auto time = timeNew - timeLast;
        timeLast = timeNew;
        scena.input(input);
        scena.keyPressed();
        scena.update(time.asSeconds());
        

        //отрисовка
        window.clear();
        scena.draw(render);
        window.display();
        
        
        //задержка на частоту кадров
        const auto slp = sf::seconds(1.0f / 60.0f) - time;
        if (slp.asSeconds() > 0)
        {
            sf::sleep(slp);
        }
        
    }



    return 0;
}