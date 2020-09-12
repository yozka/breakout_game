#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Component_Draw.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Компонент с эффектами, нужен один на всю сцену
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentEffects
        :
        public AComponentDraw
    {
        using super = AComponentDraw;

    public:

        AComponentEffects(const int depth = 0);
        ~AComponentEffects() override;

    public:

        bool isVisible() const override; //проверка спрайт нужно отрисовывать или нет
        void draw(dm::ARender &render) override; //отрисовка спрайта


    public:

        void update(const float timeSpan);
        void setVisible(const bool enabled); //установка режим отображения


        //ParticleEffectPtr addEffect(const std::string &effectName); fix

    private:



        bool                mVisible = { true }; //отрисовка
        //EffectsContainer    mEffects; fix
    };
    ///-------------------------------------------------------------------------


    using PComponentEffects = std::shared_ptr< AComponentEffects >;

}
