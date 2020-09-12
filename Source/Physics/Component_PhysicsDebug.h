#pragma once
#include <memory>
#include <string>



#include "Components/Graphics/Component_Debug.h"
#include "Component_ShapeCircle.h"
#include "Component_ShapePolygon.h"
#include "Component_Body.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Компонент дебажная отрисовка физики
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentPhysicsDebug
        :
        public AComponentDebug
    {
        using super = AComponentDebug;

    public:

        AComponentPhysicsDebug();
        ~AComponentPhysicsDebug() override;

    public:



        void draw(dm::ARender &render) override; //отрисовка спрайта





    private:

        sf::Color mColor = { sf::Color::White };

        void drawCircle     (dm::ARender &render, const PComponentShapeCircle &circle); //отрисовка круга
        void drawPolygon    (dm::ARender &render, const PComponentShapePolygon &polygon); //отрисовка полигона

        void drawBodyInfo   (dm::ARender &render, const PComponentBody &body); //отрисовка справочной информации по физтелу

    };
    ///-------------------------------------------------------------------------





}
