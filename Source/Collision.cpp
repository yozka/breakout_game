// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Collision.h"


#include "Manifold.h"
#include "MathUtils.h"

///-------------------------------------------------------------------------
using namespace game;
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// 
///
///
///-------------------------------------------------------------------------
void ACollision :: CircleToCircle (AManifold *m, const PComponentBody &a, const PComponentBody &b)
{
    const auto circleA = a->findComponent<AComponentShapeCircle>();
    const auto circleB = b->findComponent<AComponentShapeCircle>();

    if (!circleA || !circleB)
    {
        return;
    }

    m->clearContact();

    // Рассчитать вектор поступательного движения, который является нормалью
    auto normal = b->positionRelevant() - a->positionRelevant();

    auto dist_sqr = math::lengthSqr(normal);
    auto radius = circleA->radius() + circleB->radius();

    // Нет контакта!
    if (dist_sqr >= radius * radius)
    {
        return;
    }

    float distance = std::sqrt(dist_sqr);


    if (math::isEqualFloat(distance, 0.0f))
    {
        m->contact(FPoint(1.0f, 0.0f), a->positionRelevant(), circleA->radius());
    }
    else
    {
        auto penetration = radius - distance;
        normal = normal / distance; // Быстрее, чем использование Normalized, так как мы уже выполнили sqrt
        auto contact = normal * circleA->radius() + a->positionRelevant();
        m->contact(normal, contact, penetration);
    }

}
///-------------------------------------------------------------------------



 ///------------------------------------------------------------------------
///
///
///
/// поиск пересечений, полигона и круга
/// также находится нормаль контакта, и глубина контакта
///
///-------------------------------------------------------------------------
void ACollision::CircleToPolygon(AManifold *m, const PComponentBody &a, const PComponentBody &b)
{
    const auto circle   = a->findComponent<AComponentShapeCircle>();
    const auto polygon  = b->findComponent<AComponentShapePolygon>();

    if (!circle || !polygon)
    {
        //какието проблемы с компанентами
        return;
    }

    m->clearContact();

    // Преобразовать центр круга в пространство модели полигона
    auto center = a->positionRelevant();
    center = polygon->transpose() * (center - b->positionRelevant());

    // Находим ребро с минимальным проникновением
    // Точная концепция как использование опорных точек в Polygon против Polygon
    float separation = - FLT_MAX;
    size_t faceNormal = 0;

    const auto vertexCount = polygon->vertexCount();
    for (size_t i = 0; i < vertexCount; i++)
    {
        float s = math::dot(polygon->normal(i), center - polygon->vertex(i));

        if (s > circle->radius())
            return;

        if (s > separation)
        {
            separation = s;
            faceNormal = i;
        }
    }

    // сделать вершины внешней стороны
    auto v1 = polygon->vertex(faceNormal);
    auto i2 = faceNormal + 1 < vertexCount ? faceNormal + 1 : 0;
    auto v2 = polygon->vertex(i2);

    // Проверить, находится ли центр внутри многоугольника
    if (separation < math::EPSILON)
    {
        const FPoint normal = -(polygon->transform() * polygon->normal(faceNormal));
        const FPoint contact = normal * circle->radius() + a->positionRelevant();
        const float  penetration = circle->radius();
        m->contact(normal, contact, penetration);
        return;
    }

    // Определить, какая область краевого центра окружности лежит в пределах
    float dot1 = math::dot(center - v1, v2 - v1);
    float dot2 = math::dot(center - v2, v1 - v2);
    float penetration = circle->radius() - separation;

    // Ближайший к v1
    if (dot1 <= 0.0f)
    {
        if (math::distSqr(center, v1) > circle->radius() * circle->radius())
            return;

        auto normal = v1 - center;
        normal = polygon->transform() * normal;
        normal.normalize();
        v1 = polygon->transform() * v1 + b->positionRelevant();
        m->contact(normal, v1, penetration);
    }

    // Ближайший к v2
    else if (dot2 <= 0.0f)
    {
        if (math::distSqr(center, v2) > circle->radius() * circle->radius())
            return;

        auto normal = v2 - center;
        v2 = polygon->transform()* v2 + b->positionRelevant();
        normal = polygon->transform() * normal;
        normal.normalize();
        m->contact(normal, v2, penetration);
    }

    // Ближайший к лицу
    else
    {
        auto normal = polygon->normal(faceNormal);
        if (math::dot(center - v1, normal) > circle->radius())
            return;

        normal = polygon->transform() * normal;
        normal = -normal;
        auto contact = normal * circle->radius() + a->positionRelevant();
        m->contact(normal, contact, penetration);
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// 
///
///
///-------------------------------------------------------------------------
void ACollision::PolygonToCircle(AManifold *m, const PComponentBody &a, const PComponentBody &b)
{
    CircleToPolygon( m, b, a);
    m->inverseNormal();
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
///
///
/// 
///
///
///-------------------------------------------------------------------------
void ACollision::PolygonToPolygon(AManifold *m, const PComponentBody &a, const PComponentBody &b)
{
    const auto polygonA = a->findComponent<AComponentShapePolygon>();
    const auto polygonB = b->findComponent<AComponentShapePolygon>();
    const auto positionA = a->positionRelevant();
    const auto positionB = b->positionRelevant();

    if (!polygonA || !polygonB)
    {
        return;
    }

    m->clearContact();

    // Проверим разделительную ось с гранями А
    size_t faceA = 0;
    float penetrationA = findAxisLeastPenetration(faceA, polygonA, polygonB, positionA, positionB);
    if (penetrationA >= 0.0f)
    {
        return;
    }

    // Проверим разделительную ось с гранями B
    size_t faceB = 0;
    float penetrationB = findAxisLeastPenetration(faceB, polygonB, polygonA, positionB, positionA);
    if (penetrationB >= 0.0f)
    {
        return;
    }


    size_t referenceIndex = 0;
    bool flip = false; 

    PComponentShapePolygon refPoly; // Reference
    FPoint refPosition;

    PComponentShapePolygon incPoly; // Incident
    FPoint incPosition;

    // Определите, какая фигура содержит Reference грань
    if (math::biasGreaterThan(penetrationA, penetrationB))
    {
        refPoly = polygonA;
        refPosition = positionA;

        incPoly = polygonB;
        incPosition = positionB;
        referenceIndex = faceA;
        flip = false;
    }

    else
    {
        refPoly = polygonB;
        refPosition = positionB;

        incPoly = polygonA;
        incPosition = positionA;
        referenceIndex = faceB;
        flip = true;
    }

 
    FPoint incidentFace[2];
    findIncidentFace(incidentFace, refPoly, incPoly, incPosition, referenceIndex);

    //        y
    //        ^  ->n       ^
    //      +---c ------posPlane--
    //  x < | i |\
    //      +---+ c-----negPlane--
    //             \       v
    //              r
    //
    //  r : reference face
    //  i : incident poly
    //  c : clipped point
    //  n : incident normal

    // Настройка опорных граней вершин
    auto v1 = refPoly->vertex(referenceIndex);
    referenceIndex = (referenceIndex + 1 == refPoly->vertexCount()) ? 0 : referenceIndex + 1;
    auto v2 = refPoly->vertex(referenceIndex);

    // Преобразование вершин в мировое пространство
    v1 = refPoly->transform() * v1 + refPosition;
    v2 = refPoly->transform() * v2 + refPosition;

    // Рассчитать нормаль в мировом пространстве
    auto sidePlaneNormal = (v2 - v1);
    sidePlaneNormal.normalize();

    FPoint refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

    // ax + by = c
    // расстояние от начала координат
    float refC = math::dot(refFaceNormal, v1);
    float negSide = -math::dot(sidePlaneNormal, v1);
    float posSide = math::dot(sidePlaneNormal, v2);

    // Обрезать по эталонным граням
    if (clip(-sidePlaneNormal, negSide, incidentFace) < 2)
    {
        //общих точек не емеим
        return; 
    }

    if (clip(sidePlaneNormal, posSide, incidentFace) < 2)
    {
        return; 
    }
    
    FPoint normal = (flip) ? -refFaceNormal : refFaceNormal; //нормаль
    float penetration = 0.0f;//проникновение
    FPoint contacts[2]; //точка контактов
    size_t cp = 0;//количество контактов
    

    // Находим точки за контрольной гранью
    float separation = math::dot(refFaceNormal, incidentFace[0]) - refC;
    if (separation <= 0.0f)
    {
        contacts[cp] = incidentFace[0];
        penetration = -separation;
        cp++;
    }

    separation = math::dot(refFaceNormal, incidentFace[1]) - refC;
    if (separation <= 0.0f)
    {
        contacts[cp] = incidentFace[1];
        penetration += -separation;
        cp++;

        // среднее значение
        penetration /= (float)cp;
    }

    switch (cp)
    {
        case 1 : m->contact(normal, contacts[0], penetration); break;
        case 2 : m->contact(normal, contacts[1], contacts[0], penetration); break;
    }
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
int ACollision :: clip(const FPoint &n, const float c, FPoint face[])
{
    int sp = 0;
    FPoint out[3] = {
                        face[0],
                        face[1],
                        {0,0}
                    };

    // Получить расстояния от каждой конечной точки до линии
    // d = ax + by - c
    float d1 = math::dot(n, face[0]) - c;
    float d2 = math::dot(n, face[1]) - c;

    // Если отрицательный (за плоскостью) обрезать
    if (d1 <= 0.0f) out[sp++] = face[0];
    if (d2 <= 0.0f) out[sp++] = face[1];

    // Если точки находятся на разных сторонах плоскости
    if (d1 * d2 < 0.0f) 
    {
        // Протолкнуть точку пересечения
        float alpha = d1 / (d1 - d2);
        out[sp] = face[0] + alpha * (face[1] - face[0]);
        sp++;
    }

    // Назначим наши новые преобразованные значения
    face[0] = out[0];
    face[1] = out[1];

    return sp;
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
float ACollision::findAxisLeastPenetration(size_t &faceIndex, const PComponentShapePolygon &polygonA, const PComponentShapePolygon &polygonB, const FPoint &positionA, const FPoint &positionB)
{
    float bestDistance = -FLT_MAX;
    size_t bestIndex = 0;

    const auto countA = polygonA->vertexCount();
    for (size_t i = 0; i < countA; i++)
    {
        // Получить нормаль от А
        auto n = polygonA->normal(i);
        auto nw = polygonA->transform() * n;

        // преобразуем нормаль face в пространство модели B
        auto buT = polygonB->transpose();
        n = buT * nw;

        // получим точку поддержки от B вдоль -n
        auto s = polygonB->getSupport(-n);

        // Извлечь вершину из A, преобразовать в
        // пространство модели B
        auto v = polygonA->vertex(i);
        v = polygonA->transform() * v + positionA;
        v -= positionB;
        v = buT * v;

        // Вычислить расстояние проникновения (в модельном пространстве B)
        float d = math::dot(n, s - v);

        // Храним наибольшее расстояние
        if (d > bestDistance)
        {
            bestDistance = d;
            bestIndex = i;
        }
    }

    faceIndex = bestIndex;
    return bestDistance;
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
void ACollision :: findIncidentFace(FPoint v[], const PComponentShapePolygon &refPoly, const PComponentShapePolygon &incPoly, const FPoint &incPosition, const size_t referenceIndex)
{
    auto referenceNormal = refPoly->normal(referenceIndex);

    // Рассчитать нормаль в системе отсчета у кого было столкновение
    referenceNormal = refPoly->transform() * referenceNormal; // в мировое пространство
    referenceNormal = incPoly->transpose() * referenceNormal; // к пространству модели у кгого было столкновение

    // Найти наиболее не нормали face на многоугольнике у которого было столкновение
    size_t incidentFace = 0;
    float minDot = FLT_MAX;
    const auto count = incPoly->vertexCount();
    for (size_t i = 0; i < count; i++)
    {
        float dot = math::dot(referenceNormal, incPoly->normal(i));
        if (dot < minDot)
        {
            minDot = dot;
            incidentFace = i;
        }
    }

    // Назначить найденные вершины
    v[0] = incPoly->transform() * incPoly->vertex(incidentFace) + incPosition;

    incidentFace = (incidentFace + 1 >= count) ? 0 : incidentFace + 1;
    v[1] = incPoly->transform() * incPoly->vertex(incidentFace) + incPosition;
}