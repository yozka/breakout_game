// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "System_RenderDraw.h"
#include "Component_Geometry.h"

#include <algorithm>

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
ASystemRenderDraw::ASystemRenderDraw()
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
ASystemRenderDraw::~ASystemRenderDraw()
{


}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
///
///
///-------------------------------------------------------------------------
void ASystemRenderDraw::refreshComponents()
{
    super::refreshComponents();

    //сортируем спрайты по глубине отрисовке 
    std::stable_sort(components.begin(), components.end(),
        [](const auto &l, const auto &r)
        {
            return l->depth < r->depth;
        });
    
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
void ASystemRenderDraw::draw(dm::ARender &render)
{
    updatingSystem();

    for (const auto &obj : components)
    {
        if (obj->isVisible())
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
}
///-------------------------------------------------------------------------



