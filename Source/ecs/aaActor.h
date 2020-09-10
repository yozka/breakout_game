#pragma once
#include <memory>
#include <vector>
#include <map>



#include "aaCaching.h"


//Entity Component System
namespace ecs 
{

	///-------------------------------------------------------------------------
	class AContainer;
    class AComponent;
	///-------------------------------------------------------------------------





	 ///------------------------------------------------------------------------
	///
	///
	///
	/// Один элемент
	///
	///
	///-------------------------------------------------------------------------
	class AActor
		:
			public std::enable_shared_from_this < AActor >
	{
	public:

		AActor() noexcept;
		virtual ~AActor();

        AActor(AActor const&) = delete;
        AActor& operator = (AActor const&) = delete;

    public:

        AContainer* getContainer() const noexcept;

        bool isContainer()const; //проверка является ли присоеденненым в контейнер

        void assignContainer(AContainer *container); //доавляем себя в контейнера
        void rejectContainer(); //удаляем себя из контейнера

	public:

        bool isEmpty() const; //проверка, пустой актор или нет

		void append(const std::shared_ptr<AComponent> &component);
		void remove(const std::shared_ptr<AComponent> &component);

        void clear(); //полностью все почистить




         ///-------------------------------------------------------------------------
        /// поиск компанента в акторе
        template< class T = AComponent>
        std::shared_ptr<T> findComponent() const noexcept
        {
            //поиск в кеше
            std::shared_ptr<T> obj;
            if (sys::caching<T>::find(this, obj))
            {
                return obj;
            }

            for (const auto &comp : mComponents)
            {
                obj = std::dynamic_pointer_cast<T>(comp);
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
         /// поиск компанента в акторе
        template< class T = AComponent>
        void findComponents(std::vector<std::shared_ptr<T>> &list) const noexcept
        {
            if (sys::caching<T>::findList(this, list))
            {
                return;
            }


            std::vector<std::shared_ptr<T>> save;
            for (const auto &comp : mComponents)
            {
                if (auto obj = std::dynamic_pointer_cast<T>(comp))
                {
                    list.push_back(obj);
                    save.push_back(obj);
                }
            }

            sys::caching<T>::emplaceList(this, save);
        }
        ///-------------------------------------------------------------------------





        ///-------------------------------------------------------------------------
        /// поиск компанента в акторе
        template< class T = AComponent>
        std::vector<std::shared_ptr<T>> findComponents() const noexcept
        {
            std::vector<std::shared_ptr<T>> list;
            findComponents<T>(list);
            return list;
        }
        ///-------------------------------------------------------------------------



        ///-------------------------------------------------------------------------
        /// создание и добавление компанента в актор
        template< class T, typename... Args>
        std::shared_ptr<T> create(Args&&... args)
        {
            const auto obj = std::make_shared<T>(std::forward<Args>(args)...);
            append(obj);
            return obj;
        }
        ///-------------------------------------------------------------------------



    protected:
    ///-------------------------------------------------------------------------





	///-------------------------------------------------------------------------
	private:

        AContainer *mParentContainer = { nullptr };
		std::vector<std::shared_ptr<AComponent>> mComponents;

	};
	///-------------------------------------------------------------------------


	///-------------------------------------------------------------------------
	using PActor = std::shared_ptr<AActor>;
	///-------------------------------------------------------------------------



}
