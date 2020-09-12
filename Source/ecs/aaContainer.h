#pragma once
#include <memory>
#include <vector>
#include <list>

#include "aaActor.h"
#include "aaCaching.h"


//Entity Component System
namespace ecs
{
    ///-------------------------------------------------------------------------
    class ISystem;
    ///-------------------------------------------------------------------------







     ///------------------------------------------------------------------------
    ///
    ///
    ///
    /// Контейнер данных
    ///
    ///
    ///-------------------------------------------------------------------------
    class AContainer
    {
    public:
      

        AContainer();
        virtual ~AContainer();


    ///-------------------------------------------------------------------------
    public:




        
        void registerSystem     (ISystem *system); //регистрация в системе
        void unregisterSystem   (ISystem *system); //снятие регистрации

        void cleanup(); //почистить кеш
        ///-------------------------------------------------------------------------
    public:


        std::vector<PActor>& actors() noexcept { return mActors; }

        PActor append(const PActor &actor); //добавление 
        void remove(const PActor &actor); //удаление

        void clear(); //полностью все почистить

    ///-------------------------------------------------------------------------
    public:





        ///-------------------------------------------------------------------------
        /// поиск компонентов
        template< class T >
        void findComponents(std::vector<std::shared_ptr<T>> &list) const noexcept
        {
            if (sys::caching<T>::findList(this, list))
            {
                return;
            }
            std::vector<std::shared_ptr<T>> save;
            for (const auto &actor : mActors)
            {
                actor->findComponents<T>(save);
            }
            sys::caching<T>::emplaceList(this, save);

            list.insert(list.end(), save.cbegin(), save.cend());
        }
        ///-------------------------------------------------------------------------




        ///-------------------------------------------------------------------------
        /// поиск компонентов
        template< class T >
        std::vector<std::shared_ptr<T>> findComponents() const noexcept
        {
            std::vector<std::shared_ptr<T>> list;
            findComponents<T>(list);
            return list;
        }
        ///-------------------------------------------------------------------------




         ///-------------------------------------------------------------------------
        /// поиск одного компонента
        template< class T >
        std::shared_ptr<T> findComponent() const noexcept
        {
            std::shared_ptr<T> obj;
            if (sys::caching<T>::find(this, obj))
            {
                return obj;
            }

            for (const auto &actor : mActors)
            {
                obj = actor->findComponent<T>();
                if (obj)
                {
                    break;
                }
            }

            sys::caching<T>::emplace(this, obj);
            return obj;
        }
        ///-------------------------------------------------------------------------




    ///-------------------------------------------------------------------------
    private:

       


        std::vector<PActor>	mActors;
        std::vector<ISystem*> mSystems;



    };
    ///-------------------------------------------------------------------------



    ///-------------------------------------------------------------------------

}
