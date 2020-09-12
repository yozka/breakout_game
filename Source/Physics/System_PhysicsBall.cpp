// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "System_PhysicsBall.h"
#include "Components/Graphics/Component_Geometry.h"
#include "Component_Collision.h"
#include "Utils/MathUtils.h"
using namespace game;
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Constructor
///
///
///-------------------------------------------------------------------------
ASystemPhysicsBall::ASystemPhysicsBall()
{

}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Destructor
///
///
///-------------------------------------------------------------------------
ASystemPhysicsBall::~ASystemPhysicsBall()
{


}
///-------------------------------------------------------------------------











 ///------------------------------------------------------------------------
///
///
///
/// обновление логики
/// 
///
///-------------------------------------------------------------------------
void ASystemPhysicsBall::update(const float timeSpan)
{
    if (changed)
    {
        updatingSystem();
    }

    const float maxTime = 1.0f / 15.0f;
    
    mAccumulator += timeSpan;
    if (mAccumulator > maxTime)
    {
        mAccumulator = maxTime;
    }

    while (mAccumulator > settings::stepPhysics)
    {
        step(settings::stepPhysics);
        mAccumulator -= settings::stepPhysics;
    }
}
///-------------------------------------------------------------------------








 ///------------------------------------------------------------------------
///
///
///
/// одна итерация физ симуляции
/// 
///
///-------------------------------------------------------------------------
void ASystemPhysicsBall :: step(const float time)
{
    const float divTime = time * 0.5f;
    //


    //найдем коллизии
    detectContacts();


    //подсчет сил для объектов
    //первый проход
    for (const auto &obj : components)
    {
        obj->integrateForces(divTime);
    }
    //

    //подсчет коллизии
    for (auto &contact : mContacts)
    {
        contact.calculateParameters(time);
    }
    //

    //решение столкновений
    //расчет новых скоростей для столкновений
    //и идет подсчет для выталкивания объекта друг из друга
    for (int i = 0; i < settings::iterations; i++)
    {
        for (auto &contact : mContacts)
        {
            contact.applyImpulse();
        }
    }

    //интегрировать скоростя
    for (const auto &obj : components)
    {
        obj->integrateVelocity(time);
        obj->integrateForces(divTime);
    }
    //


    //коррекция позицйй при столкновений
    for (auto &contact : mContacts)
    {
        contact.correctPositions();
    }


    //очистка движущий сил
    for (const auto &obj : components)
    {
        obj->clearForce();
    }
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
///
///
/// определения столкновений
///
///-------------------------------------------------------------------------
void ASystemPhysicsBall::detectContacts()
{
    //сгенерируем информацию по колизиям
    //все тупа, все физ объекты ищем полным перебором. ХА!

    mContacts.clear();
    for (auto itemA = components.cbegin(); itemA != components.cend(); ++itemA)
    {
        const PComponentBody bodyA = *itemA;

        auto itemB = itemA;
        ++itemB;
        while (itemB != components.cend())
        {
            const PComponentBody bodyB = *itemB;
            ++itemB;

            if (math::isZero(bodyA->massInverse()) && math::isZero(bodyB->massInverse()))
            {
                //если тело неимет отталкивающей силы то контакта нет
                continue;
            }

            if (bodyA->isStatic() && bodyB->isStatic())
            {
                //статичные тела, тоже небудем просчитывать на предмет коллизий
                continue;
            }

            AManifold m(bodyB, bodyA);
            m.solve();
            if (m.isContact())
            {
                //есть контакт!!!
                const auto list = m.contacts();
                bool ok  = collision(list, bodyA, bodyB);
                     ok |= collision(list, bodyB, bodyA);

                if (ok) mContacts.emplace_back(m);
            }
        }
    }
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
///
///
/// объектам отошлем сообщение об столкновении
///
///-------------------------------------------------------------------------
bool ASystemPhysicsBall::collision(const std::vector<FPoint> &contacts, const PComponentBody &bodyA, const PComponentBody &bodyB)
{
    std::vector<PComponentCollision> list;
    bodyA->findComponents<AComponentCollision>(list);
    if (list.empty())
    {
        //обработчиков коллизий нет
        return true;
    }

    bool ok = false;
    for (const auto &obj : list)
    {
        ok |=  obj->collision(contacts, bodyB);
    }
    return ok;
}