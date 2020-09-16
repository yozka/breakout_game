#pragma once
#include <memory>
#include <string>
#include <vector>



#include "Component_Body.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Штука хранит информацию о контактах между физ объектами
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AManifold
    {


    public:

        AManifold(const PComponentBody &bodyA, const PComponentBody &bodyB);
        virtual ~AManifold()=default;

    public:


        void solve(); //подсчитаем точку контакта
        bool isContact()const; //проверим есть контакт или нет
        void clearContact(); //удалим все контакты
        void contact(const FPoint &normal, const FPoint &contact, const float penetration); //установка контакта
        void contact(const FPoint &normal, const FPoint &contact1, const FPoint &contact2, const float penetration); //установка контакта для двух точек
        void inverseNormal(); //инвертировать нормаль

        void calculateParameters(const float time);//расчитать трение и отскок
        void correctPositions();//коррекция позиций
        void applyImpulse();//приложить импульсы к физ объектам

    public:
        
        std::vector<FPoint> contacts() const; //возвратим контакты

    private:


   
        PComponentBody mBodyA;
        PComponentBody mBodyB;


        size_t  mContactCount           = { 0 };            //количество контактов
        float   mPenetration            = { 0.0f };         // Depth of penetration from collision
        FPoint  mNormal                 = { 0.0f, 0.0f };   // From A to B
        FPoint  mContacts[2];                       // Points of contact during collision
        float   mMixedRestitution       = { 0.0f }; // Mixed restitution
        float   mMixedDynamicFriction   = { 0.0f }; // Mixed dynamic friction
        float   mMixedStaticFriction    = { 0.0f }; // Mixed static friction


    private:

        void infiniteMassCorrection(); //коррекция скоросрей у объектов без массы

    };
    ///-------------------------------------------------------------------------



    ///-------------------------------------------------------------------------

    ///-------------------------------------------------------------------------



}
