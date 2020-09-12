#pragma once
#include <memory>
#include <string>
#include <vector>


#include "ecs/update/aaComponent_Update.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Ракетка, и компонент который изменяет размер ракетки
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentPaddle
        :
        public ecs::AComponentUpdate
    {
        using super = ecs::AComponentUpdate;

    public:

        AComponentPaddle(const float length);
        ~AComponentPaddle() override;

    public:


        //спрайты ракетыки
        enum ePaddleTag : int
        {
            left    = 1,
            center  = 2,
            right   = 3
        };

    public:

        void update(const float timeSpan) override;
        void changeComponents() override; //компоненты поменялись, что-то добавилось, что-то удалилось


    public:
        
        float length() const; //текущая длина ракетки


        void setLength(const float length); //установим размер ракетки
    
        void expand(); //расширить ракетку
        void squeeze(); //скукожить ракетку
        void reset();//востановить ракетку в исходное состояние
  
    private:

        float   mBaseLength     = { 100.0f }; //базовый размер ракетки

        float   mLength         = { 100.0f }; //текущий размер ракетки
        bool    mChangeSize     = { true }; //флаг что нужно поменять размер ракетки
        void    resizing(); //изменение размера ракетки


        

    };
    ///-------------------------------------------------------------------------


    using PComponentPaddle = std::shared_ptr< AComponentPaddle >;

}
