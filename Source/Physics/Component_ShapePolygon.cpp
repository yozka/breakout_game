// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_ShapePolygon.h"
#include "Component_Body.h"
#include "Utils/MathUtils.h"




///-------------------------------------------------------------------------
using namespace game;
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Constructor
///
///
///-------------------------------------------------------------------------
AComponentShapePolygon::AComponentShapePolygon()
{
    mTransform.setAngle(0);
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Constructor
///
///
///-------------------------------------------------------------------------
AComponentShapePolygon::AComponentShapePolygon(const float hw, const float hh)
{
    mTransform.setAngle(0);
    setBox(hw, hh);
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
///
///
/// Constructor
///
///
///-------------------------------------------------------------------------
AComponentShapePolygon::AComponentShapePolygon(const FPoint &sizeDiv)
{
    mTransform.setAngle(0);
    setBox(sizeDiv.x, sizeDiv.y);
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// инциализация
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentShapePolygon::initialize()
{
    computeMass(1.0f);
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// подсчитать массу объекта 
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentShapePolygon::computeMass(const float density)
{
    //подсчитаем центр нашего полигона и  момент инерции
    FPoint center(0.0f, 0.0f);
    float area = 0.0f;
    float inertia = 0;
    
    const float k_inv3 = 1.0f / 3.0f;

    for (size_t i = 0; i < mVertexCount; i++)
    {
        //Вершины треугольника, третья вершина подрузумевается как (0,0)
        const FPoint p1 = mVertices[i];
        const size_t j = i + 1 < mVertexCount ? i + 1 : 0;
        const FPoint p2 = mVertices[j];

        const float D = math::cross(p1, p2);
        const float triangleArea = 0.5f * D;

        area += triangleArea;

        //используем площадь, чтобы найти среднее значение центра, а не только по положению вершины
        center += triangleArea * k_inv3 * (p1 + p2);

        const float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
        const float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;

        inertia += (0.25f * k_inv3 * D) * (intx2 + inty2);
    }

    center *= 1.0f / area;

    //теперь нужно перевести вершины с учетом центра
    //педевинуть треугольники в центр 0,0 чтобы модель была без смещения
    //это какбы нахер не надо, но сделаем, чтобы потом норм было
    for (size_t i = 0; i < mVertexCount; i++)
    {
        mVertices[i] -= center;
    }


    if (const auto body = findComponent<AComponentBody>())
    {
        body->setMass(area * density, inertia * density);
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// ориентация объекта
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentShapePolygon::setAngleRadian(const float radians)
{
    mTransform.setAngle(radians);
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// сгенерим из полигонов прямоугольник
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentShapePolygon :: setBox(const float hw, const float hh)
{
    if (hw < math::EPSILON || hh < math::EPSILON)
    {
        return;
    }

    mVertexCount = 4;
    mVertices[0] = { -hw, -hh };
    mVertices[1] = {  hw, -hh };
    mVertices[2] = {  hw,  hh };
    mVertices[3] = { -hw,  hh };
    
    mNormals[0] = { 0.0f, -1.0f };
    mNormals[1] = { 1.0f,  0.0f };
    mNormals[2] = { 0.0f,  1.0f };
    mNormals[3] = {-1.0f,  0.0f };
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// возвратим матрицу для вычесления положения
/// </summary>
///
///-------------------------------------------------------------------------
math::matrix2 AComponentShapePolygon :: transpose() const
{
    return mTransform.transpose();
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// количество вершин
/// </summary>
///
///-------------------------------------------------------------------------
size_t AComponentShapePolygon:: vertexCount() const
{
    return mVertexCount;
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// возвратим нормаль
/// </summary>
///
///-------------------------------------------------------------------------
FPoint AComponentShapePolygon :: normal(const size_t index) const
{
    return mNormals[index];
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// возвратим вершину
/// </summary>
///
///-------------------------------------------------------------------------
FPoint AComponentShapePolygon :: vertex(const size_t index) const
{
    return mVertices[index];
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// возвратим матрицу
/// </summary>
///
///-------------------------------------------------------------------------
math::matrix2 AComponentShapePolygon::transform() const
{
    return mTransform;
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// Самая последния точка вдоль направления внутри многоугольника
/// </summary>
///
///-------------------------------------------------------------------------
FPoint AComponentShapePolygon:: getSupport(const FPoint &dir) const
{
    float bestProjection = -FLT_MAX;
    FPoint bestVertex = {0.0f, 0.0f};

    for (size_t i = 0; i < mVertexCount; ++i)
    {
        auto v = mVertices[i];
        auto projection = math::dot(v, dir);

        if (projection > bestProjection)
        {
            bestVertex = v;
            bestProjection = projection;
        }
    }

    return bestVertex;
}
///-------------------------------------------------------------------------








///------------------------------------------------------------------------
///
/// <summary>
/// ограничиваюшая рамка элемента
/// </summary>
///
///-------------------------------------------------------------------------
FPoint AComponentShapePolygon::boundingSize() const
{
    if (mVertexCount == 0)
    {
        return { 0.0f, 0.0f };
    }

    float xmin =  FLT_MAX;
    float xmax = -FLT_MAX;
    float ymin =  FLT_MAX;
    float ymax = -FLT_MAX;

    auto mm = mTransform.transpose();
    for (size_t i = 0; i < mVertexCount; ++i)
    {
        auto v = mVertices[i];
        auto projection = mm * v;
        
        xmin = std::min(xmin, projection.x);
        xmax = std::max(xmax, projection.x);

        ymin = std::min(ymin, projection.y);
        ymax = std::max(ymax, projection.y);
    }


    return { xmax - xmin, ymax - ymin };
}
///-------------------------------------------------------------------------

