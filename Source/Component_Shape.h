#pragma once
#include <memory>
#include <string>



#include "Point.h"
#include "ShapeType.h"
#include "ecs/aaComponent.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Фигура для физического объекта
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentShape
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

        void changeComponents() override //компаненты поменялись, чтото добавилось, чтото удалилось
        {
            super::changeComponents();
            initialize();
        }


    public:





    public:

        virtual EShapeType   type() const = 0; //тип объекта

        virtual void    initialize() = 0; //инциализация
        virtual void    computeMass(const float density) = 0; //подсчитать массу объекта density - плотность объекта
        virtual void    setAngleRadian(const float radians) = 0; //ориентация объекта

        virtual FPoint  boundingSize() const = 0; //прямоугольник, который описывает элемент
        virtual FPoint  getSupport(const FPoint &dir) const = 0; //Самая последния точка вдоль направления внутри многоугольника


    };
    ///-------------------------------------------------------------------------




}
