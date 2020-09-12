// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_CLLEffect.h"
#include "Component_Effects.h"
#include "ecs/aaContainer.h"




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
AComponentCLLEffect::AComponentCLLEffect(const std::string &effectName)
    :
        mEffectName(effectName)
{

}
///-------------------------------------------------------------------------








 ///------------------------------------------------------------------------
///
/// <summary>
/// destructor
/// </summary>
///
///-------------------------------------------------------------------------
AComponentCLLEffect::~AComponentCLLEffect()
{

}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// обработка контакта взаимодействия
/// </summary>
///
///-------------------------------------------------------------------------
bool AComponentCLLEffect::collision(const std::vector<FPoint> &contacts, const PComponentBody &body)
{
    if (mLastContact == body)
    {
        return true;
    }
    mLastContact = body;

    if (const auto container = getContainer())
    {
        if (const auto effects = container->findComponent<AComponentEffects>())
        {
            for (const auto &pos : contacts)
            {
                /* fix
               auto particle = effects->addEffect(mEffectName);
                particle->SetPos(pos);
                particle->Reset();*/
            }
        }
    }
    return true;
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// компоненты поменялись, что-то добавилось, что-то удалилось
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentCLLEffect::changeComponents()
{
    mLastContact = PComponentBody();
}