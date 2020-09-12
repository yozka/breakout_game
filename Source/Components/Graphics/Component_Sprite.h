#pragma once
#include <memory>
#include <string>


#include "Component_Draw.h"
#include "Utils/Point.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Компанент спрайта
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentSprite
        :
        public AComponentDraw
    {
        using super = AComponentDraw;

    public:

        AComponentSprite(const std::string &name, const int tag = 0, const int depth = 0);
        ~AComponentSprite() override;

    public:


        bool isVisible() const override; //проверка спрайт нужно отрисовывать или нет
        void draw(dm::ARender &render) override; //отрисовка спрайта


    public:

        FPoint size()const; //размер спрайта
        int width() const; //размер спрайта в пикселях
        int height() const;
        int tag() const; //возвратим тег спрайта
        float angle() const; //поворот спрайта в радианах

    public:    

        void setScale(const float scale); //масштаб спрайта
        void setScale(const FPoint &scale); //масштаб спрайта
        void setPosition(const FPoint &position); //установка позиции
        void setVisible(const bool enabled); //установка режим отображения
        void setAngle(const float angle); //установка поворота спрайта в радианах

    private:


        sf::Sprite mSprite;
        //FPoint mOrigin      = {0.0f, 0.0f}; //центр
        //FPoint mScale       = {1.0f, 1.0f};
        //FPoint mPosition    = {0.0f, 0.0f}; //смещение позиция
        //float   mAngle  = {0.0f}; //поворот

        int mTag = { 0 }; //какойто индификатор

        bool mVisible = {true}; //отрисовка

    };
    ///-------------------------------------------------------------------------



    ///-------------------------------------------------------------------------
    using PComponentSprite = std::shared_ptr< AComponentSprite >;
    ///-------------------------------------------------------------------------




}
