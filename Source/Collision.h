#pragma once
#include <memory>
#include <functional>


#include "ShapeType.h"
#include "Component_Body.h"
#include "Component_Shape.h"
#include "Component_ShapeCircle.h"
#include "Component_ShapePolygon.h"


namespace game
{
    ///-------------------------------------------------------------------------
    class AManifold;
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Просчет колиззии между объектами
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class ACollision
    {
        using functorCollision = std::function<void(AManifold *m, const PComponentBody &a, const PComponentBody &b)>;

    public:


        //вызов функции проверки колиизии
        //взависемости от типа фигур
        static void dispatcher(AManifold *m, const PComponentBody &a, const PComponentBody &b)
        {
            static functorCollision fn[EShapeType::eCount][EShapeType::eCount] =
            {
                {
                    CircleToCircle, CircleToPolygon
                },
                {
                    PolygonToCircle, PolygonToPolygon
                }
            };

            const auto shapeA = a->shapeType();
            const auto shapeB = b->shapeType();

            if (shapeA == eCount || shapeB == eCount)
            {
                //проблема с типом фигур
                //возможно что-тонехватает
                return;
            }

            fn[shapeA][shapeB](m, a, b);
        }


    private:


        static void CircleToCircle      (AManifold *m, const PComponentBody &a, const PComponentBody &b);
        static void CircleToPolygon     (AManifold *m, const PComponentBody &a, const PComponentBody &b);
        static void PolygonToCircle     (AManifold *m, const PComponentBody &a, const PComponentBody &b);
        static void PolygonToPolygon    (AManifold *m, const PComponentBody &a, const PComponentBody &b);

    private:

        static int clip(const FPoint &n, const float c, FPoint face[]);
        static float findAxisLeastPenetration(size_t &faceIndex, const PComponentShapePolygon &polygonA, const PComponentShapePolygon &polygonB, const FPoint &positionA, const FPoint &positionB);
        static void findIncidentFace(FPoint v[], const PComponentShapePolygon &refPoly, const PComponentShapePolygon &incPoly, const FPoint &incPosition, const size_t referenceIndex);
    };
    ///-------------------------------------------------------------------------





}
