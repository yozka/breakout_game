// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "aaContainer.h"
#include "aaActor.h"
#include "aaComponent.h"
#include "aaSystem.h"


#include <stdexcept>

using namespace ecs;
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Constructor
///
///
///-------------------------------------------------------------------------
AContainer::AContainer()
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
AContainer :: ~AContainer()
{
    clear();
    while (!mSystems.empty())
    {
        unregisterSystem(mSystems.back());
    }
}
///-------------------------------------------------------------------------









 ///------------------------------------------------------------------------
///
///
///
/// добавление актора
///
///
///-------------------------------------------------------------------------
PActor AContainer::append(const PActor &actor)
{
    if (actor->isContainer())
    {
        throw std::invalid_argument("actor is assign other container");
        return actor;
    }


    mActors.push_back(actor);
    actor->assignContainer(this);
    cleanup();
    return actor;
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
///
///
/// удаление актора
///
///
///-------------------------------------------------------------------------
void AContainer::remove(const PActor &actor)
{
    if (actor)
    {
        actor->rejectContainer();
    }
    const auto item = std::find(mActors.cbegin(), mActors.cend(), actor);
    if (item != mActors.cend())
    {
        mActors.erase(item);
    }

    cleanup();
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// полностью все почистить
///
///
///-------------------------------------------------------------------------
void AContainer::clear()
{
    while (!mActors.empty())
    {
        remove(mActors.back());
    }
    cleanup();
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// 
///
///
///-------------------------------------------------------------------------
void AContainer::cleanup()
{
    sys::caching_system::cleanup(this);
    for (const auto &system : mSystems)
    {
        system->changeComponents();
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// 
///
///
///-------------------------------------------------------------------------
void AContainer :: registerSystem(ISystem *system)
{
    auto item = std::find(mSystems.begin(), mSystems.end(), system);
    if (item == mSystems.end())
    {
        mSystems.push_back(system);
        system->registerContainer(this);
    }
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
///
///
/// 
///
///
///-------------------------------------------------------------------------
void AContainer::unregisterSystem(ISystem *system)
{
    auto item = std::find(mSystems.begin(), mSystems.end(), system);
    if (item != mSystems.end())
    {
        mSystems.erase(item);
        system->unregisterContainer();
    }
}