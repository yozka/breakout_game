#pragma once
#include <memory>
#include <string>
#include <vector>


#include "ecs/aaComponent.h"

namespace game
{



    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Элемент который можно скроллить 
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentScrollCan
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

 
        virtual bool isScrollingControl() { return false;}; //скроллинг может остановится

    private:


    };
    ///-------------------------------------------------------------------------


    using PComponentScrollCan = std::shared_ptr< AComponentScrollCan >;









    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Элемент который можно скроллить 
   /// но он не может останавливать сколллинг
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentScrollCanControl
        :
        public AComponentScrollCan
    {
        using super = AComponentScrollCan;

    public:


        bool isScrollingControl() override { return true; }; //скроллинг может остановится

    private:


    };
    ///-------------------------------------------------------------------------


}
