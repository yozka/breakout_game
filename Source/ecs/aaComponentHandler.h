#pragma once
#include <memory>
#include <type_traits>

#include "aaComponent.h"


namespace ecs
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------


    // пример использоавни¤ через
    // ecs::make_component
    /*
    void example()
    {
        struct stExample
        {
            int ab;
            stExample(int _ab = 0) : ab(_ab) {}

            void changeComponents()
            {
            }
        };

        auto compA = ecs::make_component<stExample>();
        auto compB = ecs::make_component<stExample>(42); //с передачай параметров в конструктор

        auto obj = std::make_shared<ecs::cActor>();
        obj->append(compA);
        obj->append(compB);

        auto compExample = obj->findComponent<stExample>();
    }
    */


     ///------------------------------------------------------------------------
    ///
    ///
    ///
    /// ќбертка над любой структурой, оборачива¤ его в объект
    ///
    ///
    ///-------------------------------------------------------------------------
    template<typename T>
    class AComponentHandler
        :
        public AComponent,
        public T
    {
        using super = AComponent;
    public:

        //вызов конструктора с разными списком параметрами
        template<typename... Args>
        AComponentHandler(Args&&... args)
            :
                T(std::forward<Args>(args)...)
        {

        }

        
        //методы определ¤ют, есть данна¤ функци¤ в классе или нет
        template <typename TT, typename = size_t>
        struct is_changeComponents : std::false_type { };
        template <typename TT>
        struct is_changeComponents <TT, decltype(sizeof(&TT::changeComponents))> : std::true_type { };

        //компаненты помен¤лись, чтото добавилось, чтото удалилось
        void changeComponents() override
        {
            if constexpr (is_changeComponents<T>())
            {
                T::changeComponents();
            }
        }
        //


        //
        template <typename TT, typename = size_t>
        struct is_assignContainer : std::false_type { };
        template <typename TT>
        struct is_assignContainer <TT, decltype(sizeof(&TT::assignContainer))> : std::true_type { };

        //доавл¤ем себ¤ в контейнера
        void assignContainer() override
        {
            if constexpr (is_assignContainer<T>())
            {
                T::assignContainer();
            }
        }
        //



        //
        template <typename TT, typename = size_t>
        struct is_rejectContainer : std::false_type { };
        template <typename TT>
        struct is_rejectContainer <TT, decltype(sizeof(&TT::rejectContainer))> : std::true_type { };

        //удал¤ем себ¤ из контейнера
        void rejectContainer() override
        {
            if constexpr (is_rejectContainer<T>())
            {
                T::rejectContainer();
            }
        }
        //


 
    };
    ///-------------------------------------------------------------------------



    ///-------------------------------------------------------------------------
    template<typename T, typename... Args>
    inline std::shared_ptr<AComponentHandler<T>> make_component(Args&&... args)
    {
        return std::make_shared<AComponentHandler<T>>(std::forward<Args>(args)...);
    }
    ///-------------------------------------------------------------------------



}
