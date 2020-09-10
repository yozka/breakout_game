#pragma once
#include <memory>
#include <string>


#include "Component_Geometry.h"

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
    class AComponentGeometryData
        :
        public AComponentGeometry
    {
        using super = AComponentGeometry;

    public:

        AComponentGeometryData(const FPoint &position = FPoint(), const FPoint &size = FPoint(), const float angle = 0.0f);


        FPoint  boundingSize() const override; //ограничиваюшая рамка элемента

        FPoint  position() const override; //позиция
        float   angle() const override; //поворот 

        void    setPosition(const FPoint &pos) override; //установка текущей позиции
        void    setAngle(const float degrees) override; //установка угла наклона

    private:

        FPoint  mPosition   = { 0.0f, 0.0f };
        FPoint  mSize       = { 0.0f, 0.0f };
        float   mAngle      = { 0.0f };




    };
    ///-------------------------------------------------------------------------




}
