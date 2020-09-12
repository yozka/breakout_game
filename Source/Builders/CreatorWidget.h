#pragma once
#include <memory>
#include <string>
#include <functional>

#include "Utils/Point.h"
#include "ecs/aaActor.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Сборщик виджетов
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class ACreatorWidget
    {


    public:

        ACreatorWidget();
        virtual ~ACreatorWidget();

    public:


        ecs::PActor createButtonIcon(const FPoint &pos, const std::string &icon, const std::function<void()> &signal); //кнопка

        ecs::PActor createHUD(const int lives); //создадим компонент с количеством жизней
        ecs::PActor createBackgroundForest();//создадим задник фон
        ecs::PActor createBackground();//создадим задник фон


        ecs::PActor createTransitionHide(const std::function<void()> &completed = nullptr);//штука, которая скрывает весь игровой экран
        ecs::PActor createTransitionShow(const std::function<void()> &completed = nullptr);

    private:

        ecs::PActor createTransition(int &outCols, int &outRows);

    
    };
    ///-------------------------------------------------------------------------




}
