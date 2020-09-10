#pragma once
#include <memory>
#include <vector>

#include "../aaComponent.h"
#include "../aaActor.h"

namespace ecs
{
    ///-------------------------------------------------------------------------
    /// вспомогательные утилиты
    ///-------------------------------------------------------------------------


    //шаблон поиска компаненты по тегу
    template < class T >
    std::shared_ptr< T > findByTag(const AComponent *comp, const int tag)
    {
        if (const auto actor = comp->getActor())
        {
            for (const auto &obj : actor->findComponents<T>())
            {
                if (obj->tag() == tag)
                {
                    return obj;
                }
            }
        }
        return std::shared_ptr< T >();
    }



    //шаблон поиска компаненты по тегу
    template < class T >
    void findsByTag(const AComponent *comp, const int tag, std::vector<std::shared_ptr< T >> &list)
    {
        if (const auto actor = comp->getActor())
        {
            for (const auto &obj : actor->findComponents<T>())
            {
                if (obj->tag() == tag)
                {
                    list.push_back(obj);
                }
            }
        }
    }


    //шаблон поиска компаненты по тегу
    template < class T >
    std::vector<std::shared_ptr< T >> findsByTag(const AComponent *comp, const int tag)
    {
        std::vector<std::shared_ptr< T >> list;
        findsByTag(comp, tag, list);
        return list;
    }

}
