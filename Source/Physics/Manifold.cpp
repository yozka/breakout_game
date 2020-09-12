// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Manifold.h"
#include "Collision.h"
#include "Component_Shape.h"
#include "System_PhysicsBall.h"
///-------------------------------------------------------------------------
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
AManifold::AManifold(const PComponentBody &bodyA, const PComponentBody &bodyB)
    :
        mBodyA(bodyA),
        mBodyB(bodyB)
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
AManifold::~AManifold()
{


}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// подсчитаем точку контакта
/// </summary>
///
///-------------------------------------------------------------------------
void AManifold :: solve()
{
    ACollision::dispatcher(this, mBodyA, mBodyB);
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// проверим есть контакт или нет
/// </summary>
///
///-------------------------------------------------------------------------
bool AManifold::isContact()const
{
    return mContactCount > 0 ? true : false;
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// удалим все контакты
/// </summary>
///
///-------------------------------------------------------------------------
void AManifold::clearContact()
{
    mContactCount = 0;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// установка первого контакта
/// </summary>
///
///-------------------------------------------------------------------------
void AManifold::contact(const FPoint &normal, const FPoint &contact, const float penetration)
{
    mContactCount = 1;
    mNormal = normal;
    mContacts[0] = contact;
    mPenetration = penetration;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// установка контакта для двух точек
/// </summary>
///
///-------------------------------------------------------------------------
void AManifold::contact(const FPoint &normal, const FPoint &contact1, const FPoint &contact2, const float penetration)
{
    mContactCount = 2;
    mNormal = normal;
    mContacts[0] = contact1;
    mContacts[1] = contact2;
    mPenetration = penetration;
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// инвертировать нормаль
/// </summary>
///
///-------------------------------------------------------------------------
void AManifold::inverseNormal()
{
    mNormal = -mNormal;
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// расчитать трение и отскок
/// </summary>
///
///-------------------------------------------------------------------------
void AManifold::calculateParameters(const float time)
{
    if (mContactCount == 0)
    {
        //контакта нет, незачем расчитывать коллизию
        return;
    }

    // Расчитать средний отсткок
    mMixedRestitution = std::min(mBodyA->restitution(), mBodyB->restitution());

    // Подсчитать статическое и динамическое трение
    mMixedStaticFriction    = std::sqrt(mBodyA->staticFriction() * mBodyB->staticFriction());
    mMixedDynamicFriction   = std::sqrt(mBodyA->dynamicFriction() * mBodyB->dynamicFriction());

    for (size_t i = 0; i < mContactCount; i++)
    {
        // Рассчитать радиусы до контакта
        auto ra = mContacts[i] - mBodyA->positionRelevant();
        auto rb = mContacts[i] - mBodyB->positionRelevant();

        auto rv = mBodyB->velocity() + math::cross(mBodyB->angularVelocity(), rb) -
                  mBodyA->velocity() - math::cross(mBodyA->angularVelocity(), ra);


        // Определяем, должны ли мы выполнить столкновение в состоянии покоя или нет
        // Идея в том, что если единственное, что движет этим объектом, это гравитация,
        // тогда столкновение должно быть выполнено без отскока
        auto rvLength = math::lengthSqr(rv);
        auto gvLength = math::lengthSqr(time * settings::gravity) + math::EPSILON;

        if (rvLength < gvLength)
        {
            mMixedRestitution = 0.0f;
        }
    }
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// коррекция позиций
/// </summary>
///
///-------------------------------------------------------------------------
void AManifold::correctPositions()
{
    if (mContactCount == 0)
    {
        //контакта нет
        return;
    }
    const float k_slop = 0.05f; // Пропускная способность
    const float percent = 0.4f; // Испровляемый процент проникновения

    const auto miA = mBodyA->massInverse();
    const auto miB = mBodyB->massInverse();

    const auto correction = (std::max(mPenetration - k_slop, 0.0f) / (miA + miB)) * mNormal * percent;

    if (mBodyA->isDynamic())
    {
        auto positionA = mBodyA->positionRelevant();
        positionA -= correction * miA;
        mBodyA->setPosition(positionA);
    }


    if (mBodyB->isDynamic())
    {
        auto positionB = mBodyB->positionRelevant();
        positionB += correction * miB;
        mBodyB->setPosition(positionB);
    }
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// коррекция
/// </summary>
///
///-------------------------------------------------------------------------
void AManifold::infiniteMassCorrection()
{
    mBodyA->stopVelocity();
    mBodyB->stopVelocity();
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// приложить импульсы к физ объектам
/// </summary>
///
///-------------------------------------------------------------------------
void AManifold::applyImpulse()
{
    if (mContactCount == 0)
    {
        //контакта нет, столкновение не прописываем
        return;
    }

    const auto miA              = mBodyA->massInverse();
    const auto miB              = mBodyB->massInverse();
    const auto iiA              = mBodyA->inertiaInverse();
    const auto iiB              = mBodyB->inertiaInverse();

    if (math::isEqualFloat(miA + miB, 0.0f))
    {
        infiniteMassCorrection();
        return;
    }
    //

    for (size_t i = 0; i < mContactCount; i++)
    {
        //подсчитать радиусыдо контакта
        auto ra = mContacts[i] - mBodyA->positionRelevant();
        auto rb = mContacts[i] - mBodyB->positionRelevant();
        
        //относительная скорость
        auto rv =   mBodyB->velocity() + math::cross( mBodyB->angularVelocity(), rb ) -
                    mBodyA->velocity() - math::cross( mBodyA->angularVelocity(), ra );
    
        //подсчет относительной скорости нормали столкновения
        float contactVel = math::dot( rv, mNormal );
        
        //точка контакта не срабатывает, если скорость положительная относительно проникновения между
        //двумя объектами
        if (contactVel > 0.0f)
        {
            return;
        }
    
        float raCrossN = math::cross( ra, mNormal );
        float rbCrossN = math::cross( rb, mNormal );
        float invMassSum = miA + miB + math::sqr( raCrossN ) * iiA + math::sqr( rbCrossN ) * iiB;

        //подсчитаем скалярный импульс
        float j = -(1.0f + mMixedRestitution) * contactVel;
        j /= invMassSum;
        j /= (float)mContactCount;


        //накладываем ипульсы к физтелам
        auto impulse = mNormal * j;
        mBodyA->applyImpulse( -impulse, ra);
        mBodyB->applyImpulse(  impulse, rb);

        //импульс отдельно для шаров
        //ввиде нормали отскока, по этой нормали всегда высчитывается движение шара
        mBodyA->applyBall( -mNormal );
        mBodyB->applyBall(  mNormal );

        //подсчитаем импулсь трения
        rv = mBodyB->velocity() + math::cross( mBodyB->angularVelocity(), rb ) -
             mBodyA->velocity() - math::cross( mBodyA->angularVelocity(), ra );
        
        auto t = rv - (mNormal * math::dot( rv, mNormal));
        if (!math::isEqualFloat(t.x, 0.0f) || !math::isEqualFloat(t.y, 0.0f))
        {
            t.normalize();
        }
        //подсчет велечины касания
        float jt = -math::dot( rv, t);
        jt /= invMassSum;
        jt /= (float)mContactCount;

        //не будем изменять импульс у тел, если касания нет
        if (math::isEqualFloat(jt, 0.0f))
        {
            return;
        }
        //


        //используем закон кулона, для неподвижных физфигур
        FPoint tangentImpulse = {0.0f, 0.0f};
        if (std::abs( jt ) < j * mMixedStaticFriction)
        {
            tangentImpulse = t * jt;
        }
        else
        {
            tangentImpulse = t * -j * mMixedDynamicFriction;
        }
        //

        //применим силу отскока
        if (mBodyA->isBall())
        {
            //для шаров только крутящийся момент            
            mBodyA->applyAngular(-tangentImpulse, ra);
        }
        else
        {
            mBodyA->applyImpulse(-tangentImpulse, ra);
        }
        
        if (mBodyB->isBall())
        {
            mBodyB->applyAngular(tangentImpulse, rb);
        }
        else
        {
            mBodyB->applyImpulse(tangentImpulse, rb);
        }

        
    }
    

}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// точки контакта, мировые координаты
/// </summary>
///
///-------------------------------------------------------------------------
std::vector<FPoint> AManifold::contacts() const
{
    std::vector<FPoint> list;
    for (size_t i = 0; i < mContactCount; i++)
    {
        list.push_back(mContacts[i]);
    }
    return list;
}