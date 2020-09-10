#pragma once
#include <memory>
#include <list>
#include <map>
#include <algorithm>


#include "aaActor.h"



//Entity Component System
namespace ecs
{
	///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





	 ///------------------------------------------------------------------------
	///
	///
	///
	/// Базовый Компанент элемента
	///
	///
	///-------------------------------------------------------------------------
	class AComponent
	{
	public:


		AComponent() noexcept; 
		virtual ~AComponent();

    public:




        void setActor(std::weak_ptr<AActor> parent) noexcept;
        std::shared_ptr<AActor> getActor() const noexcept;

        AContainer* getContainer() const noexcept; //возвратим текущий контейнер


        virtual void changeComponents() {}; //компаненты поменялись, чтото добавилось, чтото удалилось

        virtual void assignContainer() {}; //доавляем себя в контейнера
        virtual void rejectContainer() {}; //удаляем себя из контейнера



    public:


        ///-------------------------------------------------------------------------
        /// поиск компанента в акторе
        template< class T = AComponent>
        std::shared_ptr<T> findComponent() const noexcept
        {
            const auto objActor = mParent.lock();
            if (objActor)
            {
                const auto obj = objActor->findComponent<T>();
                if (obj && obj.get() != this)
                {
                    return obj;
                }
            }
            return std::shared_ptr<T>();
        }
        ///-------------------------------------------------------------------------





        ///-------------------------------------------------------------------------
        /// поиск компанента в акторе
        template< class T = AComponent >
        void findComponents(std::vector<std::shared_ptr<T>> &list) const noexcept
        {
            const auto objActor = mParent.lock();
            if (objActor)
            {
                objActor->findComponents<T>(list);
            }
        }
        ///-------------------------------------------------------------------------




        ///-------------------------------------------------------------------------
        /// поиск компанента в акторе
        template< class T = AComponent>
        std::vector<std::shared_ptr<T>> findComponents() const noexcept
        {
            const auto objActor = mParent.lock();
            if (objActor)
            {
                return objActor->findComponents<T>();
            }
            return std::vector<std::shared_ptr<T>>();
        }
        ///-------------------------------------------------------------------------




	public:





	 
     private:

        std::weak_ptr<AActor> mParent;

  

	};
	///-------------------------------------------------------------------------



	///-------------------------------------------------------------------------
	using PComponent = std::shared_ptr<AComponent>;
	///-------------------------------------------------------------------------



}
