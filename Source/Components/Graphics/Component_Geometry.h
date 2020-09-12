#pragma once
#include <memory>
#include <string>

#include "Utils/Point.h"
#include "ecs/aaComponent.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Геометрия и расположение графического объекта
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentGeometry
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:


        virtual FPoint  boundingSize() const = 0; //прямоугольник, который описывает элемент


        virtual FPoint  position() const = 0; //позиция центр объекта
        virtual float   angle() const = 0; //поворот


        virtual void    setPosition(const FPoint &pos) = 0; //установка текущей позиции
        virtual void    setAngle(const float degrees ) = 0; //установка угла наклона




    };
    ///-------------------------------------------------------------------------


    using PComponentGeometry = std::shared_ptr< AComponentGeometry >;


}
