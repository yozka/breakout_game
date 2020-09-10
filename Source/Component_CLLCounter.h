#pragma once
#include <memory>


#include "Component_Collision.h"

namespace game
{
    ///-------------------------------------------------------------------------
  




     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Обработчик столкновения с физ объектом
    /// подсчет столкновения
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    template <class T>
    class AComponentCLLCounter
        :
        public AComponentCollision
    {
        using super = AComponentCollision;

    public:

        bool collision(const std::vector<FPoint> &contacts, const PComponentBody &body)override
        {
            if (body->findComponent<T>())
            {
                mContact++;
            }
            return false;
        }

        size_t contactCount() const
        {
            return mContact;
        }

    private:

        size_t mContact = { 0 }; //количество контактов

       
    };
    ///-------------------------------------------------------------------------




}
