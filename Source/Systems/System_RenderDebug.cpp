// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "System_RenderDebug.h"
#include "Components/Graphics/Component_Geometry.h"

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
ASystemRenderDebug::ASystemRenderDebug()
{

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
ASystemRenderDebug::~ASystemRenderDebug()
{


}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
///
///
/// ќбновление логики
///
///
///-------------------------------------------------------------------------
void ASystemRenderDebug::draw(dm::ARender &render)
{
    if (!mEnabled)
    {
        return;
    }

    updatingSystem();


    for (const auto &obj : components)
    {
        render.pushMatrix();

        //задаем позицию самого объекта
        if (const auto geometry = obj->findComponent<AComponentGeometry>())
        {
            render.matrixTranslate(geometry->position());
            render.matrixRotate(geometry->angle());
        }

        obj->draw(render);
        render.popMatrix();
    }

}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
///
///
///
///-------------------------------------------------------------------------
void ASystemRenderDebug::enabled()
{
    mEnabled = true;
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
///
///
///
///-------------------------------------------------------------------------
void ASystemRenderDebug::disabled()
{
    mEnabled = false;
}