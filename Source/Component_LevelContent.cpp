// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_LevelContent.h"
#include "Component_Geometry.h"
#include "ecs/aaContainer.h"
#include "Device.h"


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
AComponentLevelContent::AComponentLevelContent()
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
AComponentLevelContent::~AComponentLevelContent()
{

}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// проверка, есть еще данные для спавна уровня
/// </summary>
///
///-------------------------------------------------------------------------
bool AComponentLevelContent::isEmpty()const
{
    return mContents.empty();
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// добавить одну линию уровня
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLevelContent::append(const std::vector<ecs::PActor> &line)
{
    mContents.push_back(line);
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// выведем следующую строчку уровня
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLevelContent::nextSpawn()
{
    if (mContents.empty())
    {
        return;
    }
    
    const float pos_y = -settings::height_block * 0.5f;
    spawn(pos_y, mContents.back());
    mContents.pop_back();
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// спавн в указанную позицию
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLevelContent::spawn(const float pos_y, const std::vector<ecs::PActor> &line)
{
    auto container = getContainer();
    if (!container) return;
    
    for (const auto &obj : line)
    {
        if (const auto geometry = obj->findComponent<AComponentGeometry>())
        {
            auto pos = geometry->position();
            pos.y += pos_y;
            geometry->setPosition(pos);
        }
        container->append(obj);
    }
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// выводим строки уровня сразу
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLevelContent::firstSpawn(const int countRows)
{
    float top = -settings::height_block * 0.5f + (countRows * settings::height_block);
    for (int i = 0; i <= countRows; i++)
    {
        if (mContents.empty())
        {
            return;
        }
        spawn(top, mContents.back());
        mContents.pop_back();
        top -= settings::height_block;
    }
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// удалим первые и последние пустые строчки
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentLevelContent::emptyTrim()
{
    while (!mContents.empty() && mContents.cbegin()->empty())
    {
        mContents.pop_front();
    }

    while (!mContents.empty() && mContents.crbegin()->empty())
    {
        mContents.pop_back();
    }
}
///-------------------------------------------------------------------------


