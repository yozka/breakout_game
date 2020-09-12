#pragma once
#include <memory>
#include <string>





#include "Component_Shape.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Фигура для физического объекта
    /// ввиде круга
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentShapeCircle
        :
        public AComponentShape
    {
        using super = AComponentShape;
        friend class AComponentPhysicsDebug;

    public:

        AComponentShapeCircle(const float radius);


    public:

        EShapeType  type() const override { return EShapeType::eCircle; }; //тип объекта


        void    initialize  () override; //инциализация
        void    computeMass (const float density) override; //подсчитать массу объекта
        void    setAngleRadian(const float radians) override; //ориентация объекта
        FPoint  boundingSize() const override; //ограничиваюшая рамка элемента
        FPoint  getSupport(const FPoint &dir) const override; //Самая последния точка вдоль направления внутри многоугольника



    public:

        float   radius()const; //радиус круга

    private:

        
        float mRadius = { 0.0f };

    };
    ///-------------------------------------------------------------------------



    using PComponentShapeCircle = std::shared_ptr< AComponentShapeCircle >;


}
