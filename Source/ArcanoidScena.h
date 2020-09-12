#pragma once
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "Device.h"
#include "ecs/aaContainer.h"
#include "ecs/update/aaSystem_Update.h"

#include "Systems/System_RenderDraw.h"
#include "Systems/System_Input.h"
#include "Systems/System_RenderDebug.h"
#include "Systems/System_Effects.h"
#include "Physics/System_PhysicsBall.h"


namespace game
{
    ///-------------------------------------------------------------------------
    namespace settings
    {
        constexpr float time_update = 0.3f;
    }
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// базовый экран
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AArcanoidScena
    {

    public:

        AArcanoidScena();
        virtual ~AArcanoidScena();

    public:


        void draw(dm::ARender &render);
        void update(const float dt);
        void input(const dm::EventInput &input);
        void keyPressed();


    public:


   

        void beginGame();



    private:


        ecs::AContainer     mContainer; //контейнер с игровыми элементами

        //системы для обновления логики у объктов
        //система отрисовки элементов
        //система физики движения мячиков

        ecs::ASystemUpdate      mSystemUpdate; 
        ASystemRenderDraw       mSystemRenderDraw;
        ASystemRenderDebug      mSystemRenderDebug;
        ASystemPhysicsBall      mSystemPhysicsBall;
        ASystemInput            mSystemInput;
        ASystemEffects          mSystemEffects;

        bool mMousePress = { false };





        

    };
    ///-------------------------------------------------------------------------



    ///-------------------------------------------------------------------------

    ///-------------------------------------------------------------------------



}
