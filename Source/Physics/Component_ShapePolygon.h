#pragma once
#include <memory>
#include <string>


#include "Utils/MathUtils.h"
#include "Component_Shape.h"

namespace game
{
    ///-------------------------------------------------------------------------
    namespace settings
    {
        //максимальное количество вертексов
        constexpr size_t max_poly_vertex_count = 64; 
    }
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Фигура для физического объекта
    /// ввиде замкнутого полигона
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentShapePolygon
        :
        public AComponentShape
    {
        using super = AComponentShape;
        friend class AComponentPhysicsDebug;

    public:

        AComponentShapePolygon();
        AComponentShapePolygon(const float hw, const float hh);
        AComponentShapePolygon(const FPoint &sizeDiv);

    public:

        EShapeType   type() const override { return EShapeType::ePoly; }; //тип объекта


        void    initialize() override; //инциализация
        void    computeMass(const float density) override; //подсчитать массу объекта
        void    setAngleRadian(const float radians) override; //ориентация объекта
        FPoint  boundingSize() const override; //ограничиваюшая рамка элемента
        FPoint  getSupport(const FPoint &dir) const override; //Самая последния точка вдоль направления внутри многоугольника


    public:

        void setBox(const float hw, const float hh); //сгенерим из полигонов прямоугольник

    
        math::matrix2 transpose() const; //возвратим матрицу для вычесления положения
        size_t vertexCount() const; //количество вершин
        FPoint normal(const size_t index) const; //возвратим нормаль
        FPoint vertex(const size_t index) const; //возвратим вершину
        math::matrix2 transform() const; //возвратим матрицу
    private:


        math::matrix2 mTransform; //матрица трансформации для полигонов


        size_t mVertexCount = { 0 }; //количетсво вершин
        FPoint mVertices    [settings::max_poly_vertex_count] = {}; //массив для быстроты доступа, не оптимально? пох.
        FPoint mNormals     [settings::max_poly_vertex_count] = {}; //нормали плоскости, для подсчета отражения шаров
    };
    ///-------------------------------------------------------------------------




    using PComponentShapePolygon = std::shared_ptr< AComponentShapePolygon >;

}
