// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_PhysicsDebug.h"
#include "Component_Body.h"
#include "base_Random.h"



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
AComponentPhysicsDebug::AComponentPhysicsDebug()
{
    auto &random = dm::ARandom::instance();

    mColor.r = random.next(100, 0xFF);
    mColor.g = random.next(100, 0xFF);
    mColor.b = random.next(100, 0xFF);
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Destructor
///
///
///-------------------------------------------------------------------------
AComponentPhysicsDebug::~AComponentPhysicsDebug()
{


}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
///  
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPhysicsDebug::draw(dm::ARender &render)
{
    if (const auto body = findComponent<AComponentBody>())
    {
        drawBodyInfo(render, body);
    }

    if (const auto circle = findComponent<AComponentShapeCircle>())
    {
        drawCircle(render, circle);
        return;
    }

    if (const auto polygon = findComponent<AComponentShapePolygon>())
    {
        drawPolygon(render, polygon);
        return;
    }

}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// отрисовка круга
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPhysicsDebug :: drawCircle (dm::ARender &render, const PComponentShapeCircle &circle)
{
    const auto radius = circle->mRadius;
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color(0,0,0,0));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(mColor);
    shape.setOrigin({radius, radius});
    render.render(shape);
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// отрисовка полигона
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPhysicsDebug :: drawPolygon (dm::ARender &render, const PComponentShapePolygon &polygon)
{
    const auto count = polygon->mVertexCount;
    if (count < 2)
    {
        return;
    }

    sf::ConvexShape convex;
    convex.setFillColor(sf::Color(0, 0, 0, 0));
    convex.setOutlineThickness(2);
    convex.setOutlineColor(mColor);

    convex.setPointCount(count);

    for (size_t i = 0; i < count; i++)
    {
        const auto &pos = polygon->mVertices[i];
        convex.setPoint(i, {pos.x, pos.y});
    }
 
    render.render(convex);
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// отрисовка справочной информации по физтелу
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentPhysicsDebug :: drawBodyInfo(dm::ARender &render, const PComponentBody &body)
{
    /* fix
    const auto s = [](const float val)
    {
        return std::to_string((int)(std::round(val)));
    };


    const auto velocity = body->velocity();
    const auto size = body->boundingSize();

    std::string text = "VC: " + s(velocity.x) + " : " + s(velocity.y);
    text += "\nBS: " + s(size.x)+ ", " + s(size.y);

    Render::device.PushMatrix();
    Render::device.MatrixRotate(math::Vector3(0, 0, 1), -body->angle());

    Render::BeginColor(Color::GREEN);
    Render::BindFont("arial");
    Render::PrintString(size * 0.5f, text, 1.0f, LeftAlign, BottomAlign);
    Render::EndColor();

    Render::device.PopMatrix();
    */
}