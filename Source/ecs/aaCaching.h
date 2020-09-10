#pragma once
#include <memory>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <functional>
///-------------------------------------------------------------------------




//Entity Component System
namespace ecs
{
    ///-------------------------------------------------------------------------



    namespace sys
    {
        ///-------------------------------------------------------------------------
        using ptr = void;
        ///-------------------------------------------------------------------------




        ///-------------------------------------------------------------------------
        struct caching_system
        {


        
            static void cleanup(const ptr *entity) noexcept
            {
                for (const auto &clean : get_cache_functors())
                {
                    clean(entity);
                }
            }



        protected:
            caching_system() = default;
            virtual ~caching_system() = default;



            using functor_clean = std::function<void(const ptr* entity)>;
            using functors = std::vector<functor_clean>;



            static void registerClean(functor_clean functor) noexcept
            {
                auto &cache_functors = get_cache_functors();
                cache_functors.push_back(functor);
            }



        private:



            static functors& get_cache_functors() noexcept
            {
                static functors cache_functors;
                return cache_functors;
            }



        };
        ///-------------------------------------------------------------------------





         ///------------------------------------------------------------------------
        ///
        ///
        ///
        ///  Кеширование
        ///
        ///
        ///-------------------------------------------------------------------------
        template < class T >
        struct caching 
                    : private caching_system
        {
        public:
            caching() noexcept = default;
            ~caching() override = default;


            ///-------------------------------------------------------------------------
            using sptr      = std::shared_ptr<T>;
            using wptr      = std::weak_ptr<T>;
            using slist     = std::vector< std::shared_ptr<T> >;
            using wlist     = std::vector< std::weak_ptr<T> >;
            using map_one   = std::unordered_map<const ptr*, wptr>;
            using map_list  = std::unordered_map<const ptr*, wlist>;
            ///-------------------------------------------------------------------------



             ///-------------------------------------------------------------------------
            /// поиск компанента в кеше
            static bool find(const ptr *entity, sptr &obj) noexcept
            {
                auto &cache_one = get_cache_one();
                const auto it = cache_one.find(entity);
                if (it != cache_one.cend())
                {
                    obj = it->second.lock();
                    return true;
                }
                return false;
            }
            ///-------------------------------------------------------------------------



             ///-------------------------------------------------------------------------
            /// поиск компанента в кеше
            static bool findList(const ptr *entity, slist &list) noexcept
            {
                auto &cache_list = get_cache_list();
                const auto it = cache_list.find(entity);
                if (it != cache_list.cend())
                {
                    for (const auto &item : it->second)
                    {
                        if (auto obj = item.lock())
                        {
                            list.push_back(obj);
                        }
                    }
                    return true;
                }
                return false;
            }
            ///-------------------------------------------------------------------------



             ///-------------------------------------------------------------------------
            /// установка кеша
            static void emplace(const ptr *entity, const wptr &obj) noexcept
            {
                auto &cache_one = get_cache_one();
                cache_one.emplace(entity, obj);

                init();
            }
            ///-------------------------------------------------------------------------




             ///-------------------------------------------------------------------------
            /// установка кеша
            static void emplaceList(const ptr *entity, const slist &list) noexcept
            {
                auto &cache_list = get_cache_list();
                wlist obj;
                obj.insert(obj.begin(), list.cbegin(), list.cend());
                cache_list.emplace(entity, obj);

                init();
            }
            ///-------------------------------------------------------------------------





             ///-------------------------------------------------------------------------
            /// очистка кеша
            static void clean(const ptr *entity) noexcept
            {
                auto &cache_one = get_cache_one();
                auto &cache_list = get_cache_list();

                cache_one.erase(entity);
                cache_list.erase(entity);
            }
            ///-------------------------------------------------------------------------




             ///-------------------------------------------------------------------------
            /// инцализация системы очистки кеша
            static void init() noexcept
            {
                static bool cache_init = true;
                if (cache_init)
                {
                    cache_init = false;
                    registerClean(&caching<T>::clean);
                }
            }


  
            static inline map_one& get_cache_one() noexcept
            {
                static map_one cache_one;
                return cache_one;
            }
       
            static inline map_list& get_cache_list() noexcept
            {
                static map_list cache_list;
                return cache_list;
            }



        };
        ///-------------------------------------------------------------------------







    }
}
