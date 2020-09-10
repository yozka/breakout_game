// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "CreatorWidget.h"
#include "Device.h"



#include "Component_Body.h"
#include "Component_ShapePolygon.h"
#include "Component_Cling.h"
#include "Component_Lives.h"
#include "Component_GeometryData.h"
#include "Component_Button.h"
#include "Component_LivesToBall.h"
#include "Component_Sprite.h"
#include "Component_TransitionHide.h"
#include "Component_TransitionShow.h"

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
ACreatorWidget::ACreatorWidget()
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
ACreatorWidget::~ACreatorWidget()
{


}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// кнопка
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorWidget::createButtonIcon(const FPoint &pos, const std::string &icon, const std::function<void()> &signal)
{
    int depth = 10;
    auto button = std::make_shared<ecs::AActor>();
    button->create<AComponentGeometryData>(pos, FPoint(150, 50));
    button->create<AComponentSprite>("green_button07", AComponentButton::tagNormal, depth++);
    button->create<AComponentSprite>("green_button08", AComponentButton::tagPushed, depth++)->setVisible(false);
    button->create<AComponentSprite>("green_button11", AComponentButton::tagHover,  depth++)->setVisible(false);
    button->create<AComponentSprite>(icon, AComponentButton::tagIcon, depth++);
    button->create<AComponentButton>(signal);
    return button;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// создадим компонент с количеством жизней
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorWidget::createHUD(const int lives)
{
    const float padding = 10.0f;
    auto hud = std::make_shared<ecs::AActor>();

    hud->create<AComponentGeometryData>(FPoint(padding, padding + 25.0f));
    hud->create<AComponentLives>(lives);

    return hud;
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// создадим задник фон
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorWidget::createBackgroundForest()
{
    const float width = dm::deviceWidth();
    const float height = dm::deviceHeight();
    auto back = std::make_shared<ecs::AActor>();
    back->create<AComponentGeometryData>(FPoint(width * 0.5f, height * 0.5f));
    back->create<AComponentSprite>("backgroundColorForest", 0, -110);//->setScale({width / 32, height / 32});
    return back;
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// создадим задник фон
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorWidget::createBackground()
{
    const float width = dm::deviceWidth();
    const float height = dm::deviceHeight();
    auto back = std::make_shared<ecs::AActor>();
    back->create<AComponentGeometryData>(FPoint(width * 0.5f, height * 0.5f));
    back->create<AComponentSprite>("backgroundForest", 0, -110);
    return back;
}
///-------------------------------------------------------------------------





///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorWidget::createTransition(int &outCols, int &outRows)
{
    const float width = dm::deviceWidth();
    const float height = dm::deviceHeight();
    const FPoint size(width, height);

    const int depth = 2000;
    const int sprWidth = 58;
    const int sprHeight = 58;

    const int cols = std::lround(width / sprWidth) + 1;
    const int rows = std::lround(height / sprHeight) + 1;
    const FPoint shift(-width * 0.5f, -height * 0.5f);

    auto obj = std::make_shared<ecs::AActor>();
    obj->create<AComponentGeometryData>(size * 0.5f, size);
    for (int j = 0; j < rows; j++)
        for (int i = 0; i < cols; i++)
        {
            const auto block = obj->create<AComponentSprite>("transition_block", i + j * cols, depth);
            block->setPosition(FPoint(i * sprWidth, j * sprHeight) + shift);
        }

    outCols = cols;
    outRows = rows;
    return obj;
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// штука, которая скрывает весь игровой экран
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorWidget::createTransitionHide(const std::function<void()> &completed)
{
    int cols = 0;
    int rows = 0;
    auto obj = createTransition(cols, rows);
    obj->create<AComponentTransitionHide>(cols, rows, completed);
    return obj;
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorWidget::createTransitionShow(const std::function<void()> &completed)
{
    int cols = 0;
    int rows = 0;
    auto obj = createTransition(cols, rows);
    obj->create<AComponentTransitionShow>(cols, rows, completed);
    return obj;
}