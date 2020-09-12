#pragma once
#include <memory>
#include <vector>

#include "ecs/update/aaComponent_Update.h"
#include "Components/Graphics/Component_Geometry.h"

namespace game
{
    ///-------------------------------------------------------------------------

    namespace settings
    {
        constexpr float scrolling_height = 32.0f; //высота скроллинга уровня
    }



     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Скроллинг уровня в низ
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentScollDown
        :
        public ecs::AComponentUpdate
    {
        using super = ecs::AComponentUpdate;
    public:

        AComponentScollDown(const int rows);
        ~AComponentScollDown() override;


    public:

        void update     (const float timeSpan) override;
        void updateSlow (const float timeSpan) override;

    public:

        void replacement(const PComponentGeometry &old, const PComponentGeometry &obj); //добавить принудительно на скроллинг если есть скролл

    private:

        int     mRows       = {0}; //количество рядов сверху, на который идет скроллинг
        bool    mScolling   = {false}; //идет скроллинг вниз
        float   mTimer      = {0}; //скроллинг

        std::vector<std::pair<FPoint, PComponentGeometry>> mObjects; //объекты которые нужно скроллить
        
    private:
        
        void scrollStart(); //начало скроллинга

    };
    ///-------------------------------------------------------------------------



}
