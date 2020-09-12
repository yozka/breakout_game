// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_Transition.h"

#include "ecs/utils/aaUtils.h"
#include "ecs/aaContainer.h"
///-------------------------------------------------------------------------




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
AComponentTransition::AComponentTransition(const int cols, const int rows)
    :
        mCols(cols),
        mRows(rows)
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
AComponentTransition::~AComponentTransition()
{

}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentTransition::update(const float timeSpan)
{
    if (blocks.empty())
    {
        initBlocks();
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentTransition::initBlocks()
{
    blocks.clear();
    for (int j = 0; j < mRows; j++)
        for (int i = 0; i < mCols; i++)
        {
            blocks.push_back(ecs::findByTag<AComponentSprite>(this, i + j * mCols));
        }
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// удалить себя
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentTransition::destroy()
{
    if (auto container = getContainer())
    {
        container->remove(getActor());
    }
}
///-------------------------------------------------------------------------



