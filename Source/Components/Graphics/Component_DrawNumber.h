#pragma once
#include <memory>
#include <string>

#include "Utils/Point.h"
#include "Component_Draw.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Отрисовка целочисленных чисел
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentDrawNumber
        :
        public AComponentDraw
    {
        using super = AComponentDraw;
        using pthis = AComponentDrawNumber*;

    public:

        AComponentDrawNumber(const int tag = 0, const int depth = 0);
        ~AComponentDrawNumber() override;

    public:


        bool isVisible() const override; //проверка спрайт нужно отрисовывать или нет
        void draw(dm::ARender &render) override; //отрисовка спрайта


    public:

        int tag() const; //возвратим тег спрайта
        
        int number() const;
    public:

        pthis setScale(const float scale); //масштаб спрайта
        pthis setScale(const FPoint &scale); //масштаб спрайта
        pthis setPosition(const FPoint &position); //установка позиции
        pthis setVisible(const bool enabled); //установка режим отображения

        pthis setNumber(const int value); //установка числа
    private:

        int mNumber = {0};

        sf::Sprite mTextures[10] = { }; 


        FPoint mScale       = { 1.0f, 1.0f }; //размер
        FPoint mPosition    = { 0.0f, 0.0f }; //смещение позиция

        
        float  mKerning     = { 0.7f }; //межбуквенный интервал

        int mTag = { 0 }; //какойто индификатор
        bool mVisible = { true }; //отрисовка

    };
    ///-------------------------------------------------------------------------



    ///-------------------------------------------------------------------------
    using PComponentDrawNumber = std::shared_ptr< AComponentDrawNumber >;
    ///-------------------------------------------------------------------------




}
