#pragma once
#include <memory>
#include <string>


#include "ShapeType.h"
#include "Components/Graphics/Component_Geometry.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------







     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Геометрия и расположение графического объекта
    /// для физического объекта
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentBody
        :
        public AComponentGeometry
    {
        using super = AComponentGeometry;

    public:

        AComponentBody(const FPoint &position = FPoint(), const float angle = 0.0f);


        void changeComponents() override; //компоненты поменялись, что-то добавилось, что-то удалилось

    public:

        FPoint  boundingSize() const override;//размер элемента

        FPoint  position() const override; //позиция
        float   angle() const override; //поворот в градусах
        
        void    setPosition(const FPoint &pos) override; //установим позицию новую
        void    setAngle(const float degrees) override; //установим угол


    public:

        void setStatic(); //устанавливаем объект встатический
        void setBall(); //устанавливаем объект как шар

        void applyForce(const FPoint &force); //добавить с которой будут двигатся объекты
        void applyImpulse(const FPoint &impulse, const FPoint &contactVector); //добавить импульс для физтела


        //специально для шара
        void applyBall(const FPoint &impulse); //импульс для шара
        void applyAngular(const FPoint &impulse, const FPoint &contactVector); //импульс кручения закручивание объекта


        void setAngleRadian(const float radians); //ориентация объекта


        void setMass(const float mass, const float inertia); //установка параметров массы и инерции
        
        void stopVelocity(); //остановить движение
        void setVelocity(const FPoint &value); //установка скорости

        EShapeType shapeType()const; //возвратим текущий тип фигуры

    public:

        void clearForce(); //удалить все силы
        void setBallSpeed(const float spd);
        float ballSpeed() const; //текущая скорость шара

    public:

        float   restitution() const; //возвратим отскок
        float   staticFriction() const; //трение в статике
        float   dynamicFriction() const; //трение в движении
        FPoint  velocity() const; //текущая скорость
        float   angularVelocity() const; //текущая угловая скорость
        float   massInverse() const; //масса поглащающая импульсы
        float   inertiaInverse() const; //обратная инерция
        bool    isDynamic() const; //проверяет, объект динамический или нет
        bool    isBall()const; //проверяет, это наш особенный объект мяч?
        bool    isStatic()const; //проверить, тело статичное или нет
        float   angleRadian()const; //угол наклона объекта в радианах

        FPoint  positionRelevant() const; //актуальня позиция

        void    integrateForces(const float time);//подсчет действующих сил
        void    integrateVelocity(const float time); //подсчет скоростией и движения

    private:

        EShapeType mShapeType       = { eCount };
        bool    mStatic             = { false }; //объект, статичный или нет

        FPoint  mPosition           = { 0.0f, 0.0f }; //текущая позиция
        FPoint  mVelocity           = { 0.0f, 0.0f }; //скорость движения
        
        float   mAngularVelocity    = { 0.0f }; //угловая скорость
        float   mTorque             = { 0.0f }; //крутящий момент
        float   mAngleRadians       = { 0.0f };

        FPoint  mForce              = { 0.0f, 0.0f }; //сила движения для обычных тел
        FPoint  mForceBall          = { 0.0f, 0.0f }; //сила движения для мячей, которая действует непрерывно

        //данные форм
        float   mShapeInertia           = { 0.0f }; //момент инерции
        float   mShapeInertiaInverse    = { 0.0f }; //инверсивная инерция
        float   mShapeMass              = { 0.0f }; //масса формы
        float   mShapeMassInverse       = { 0.0f }; //масса формы для поглощения импульсов


        //данные для физ объекта
        //магические цыфры, ищутся методом проб и ошибок
        float   mStaticFriction         = { 0.5f }; //трение об статический объект
        float   mDynamicFriction        = { 0.3f }; //трение в движении
        float   mRestitution            = { 0.2f }; //отскоки


        //особые данные для шара
        bool    mBall                   = { false };//это шар
        float   mBallSpeed              = { 0 };//Скорость движение шара


    private:


    };
    ///-------------------------------------------------------------------------



    using PComponentBody = std::shared_ptr< AComponentBody >;


}
