#pragma once
#include <memory>
#include <vector>

#include "aaContainer.h"

namespace ecs
{
    ///-------------------------------------------------------------------------
    class AContainer;
    ///-------------------------------------------------------------------------


    



     ///------------------------------------------------------------------------
    ///
    ///
    ///
    /// базовая система
    ///
    ///
    ///-------------------------------------------------------------------------
    class ISystem
    {
    public:
        ISystem();
        virtual ~ISystem();


        void registerContainer (AContainer *pContainer); //регистрация контейнера
        void unregisterContainer (); //снятие регистрации с контейнера

        void changeComponents(); //система поменяла свои действия
        virtual void refreshComponents() {} ; //нужно изменить компаненты


    protected:

        AContainer *container = { nullptr };
        bool changed = { false }; //данные поменялись
    };
    ///-------------------------------------------------------------------------






     ///------------------------------------------------------------------------
    ///
    ///
    ///
    /// Система которая работает над компанентами
    ///
    ///
    ///-------------------------------------------------------------------------
    template <class T>
    class ASystem
        :
            public ISystem
    {
    public:
        ///-------------------------------------------------------------------------
        ASystem() = default;
        ~ASystem() override
        {
            components.clear();
        }


   

        ///-------------------------------------------------------------------------
    protected:

        std::vector<std::shared_ptr<T>> components; //список компанентов

        void refreshComponents() override
        {
            components.clear();
            if (container)
            {
                container->findComponents<T>(components);
            }
            changed = false;
        }

        void updatingSystem() //обновление системы
        {
            if (changed)
            {
                refreshComponents();
            }
        }

    };
    ///-------------------------------------------------------------------------






}
