#pragma once
#include <memory>
#include <vector>



#include "ecs/aaSystem.h"
#include "Component_Body.h"
#include "Manifold.h"


namespace game
{
    ///-------------------------------------------------------------------------
    namespace settings
    {
        //вермя симуляции
        #ifdef _DEBUG
        constexpr   float   stepPhysics     = 1.0f / 100.0f;
        constexpr   int     iterations      = 5;
        #else
        constexpr   float   stepPhysics     = 1.0f / 400.0f;
        constexpr   int     iterations      = 5;
        #endif    

        //гравитация
        constexpr   float   gravityScale    = 5.0f;
        const       FPoint  gravity         = { 0.0f, 10.0f * gravityScale };
    }
    ///-------------------------------------------------------------------------






     ///------------------------------------------------------------------------
    ///
    ///
    ///
    /// Система которая движет мячи и физобъекты
    ///
    ///
    ///-------------------------------------------------------------------------
    class ASystemPhysicsBall
        :
        public ecs::ASystem<AComponentBody>
    {
    public:


        ASystemPhysicsBall();
        ~ASystemPhysicsBall() override;



        ///-------------------------------------------------------------------------

    public:


        void update(const float timeSpan);




        ///-------------------------------------------------------------------------

    private:

        void step(const float time); //одна итерация физ симуляции
        void detectContacts(); //определения столкновений
        bool collision(const std::vector<FPoint> &contacts, const PComponentBody &bodyA, const PComponentBody &bodyB); //объектам отошлем сообщение об столкновении

    private:

        std::vector<AManifold> mContacts;
        
        float mAccumulator =  { 0.0 }; //время симуляции
    };
    ///-------------------------------------------------------------------------




}
