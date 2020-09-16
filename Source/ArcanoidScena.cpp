// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "ArcanoidScena.h"
#include "Builders/BuildLevel.h"
#include "Builders/BuildMenu.h"





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
AArcanoidScena::AArcanoidScena()
    :
        mSystemUpdate(settings::time_update)
{

    //регистрация систем
    mSystemUpdate.          registerContainer(&mContainer);
    mSystemRenderDraw.      registerContainer(&mContainer);
    mSystemRenderDebug.     registerContainer(&mContainer);
    mSystemPhysicsBall.     registerContainer(&mContainer);
    mSystemInput.           registerContainer(&mContainer);
    mSystemEffects.         registerContainer(&mContainer);

    beginGame();
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
void AArcanoidScena::beginGame()
{
    /*ABuildLevel level(mContainer);
    level.build();*/

    ABuildMenu menu(&mContainer);
    menu.build();
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// Отрисовка
/// </summary>
///
///-------------------------------------------------------------------------
void AArcanoidScena :: draw(dm::ARender &render)
{
    mSystemRenderDraw.draw(render);
    mSystemRenderDebug.draw(render);
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// Обновление логики
/// </summary>
///
///-------------------------------------------------------------------------
void AArcanoidScena :: update(const float dt) 
{
    mSystemUpdate.      update(dt);
    mSystemPhysicsBall. update(dt);
    mSystemInput.       update(dt);
    mSystemEffects.     update(dt);
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
void AArcanoidScena :: input(const dm::EventInput &input)
{
    if (input.mouseMove)
    {
        mSystemInput.mouseMove(input);
    }

    const bool press = input.mouseLeft | input.mouseRigth;
    if (press && !mMousePress)
    {
        mMousePress = true;
        mSystemInput.mouseDown(input);
    }
    if (!press && mMousePress)
    {
        mMousePress = false;
        mSystemInput.mouseUp(input);
    }
}
///-------------------------------------------------------------------------








 ///------------------------------------------------------------------------
///
/// <summary>
/// нажали на кнопку клавы
/// </summary>
///
///-------------------------------------------------------------------------
void AArcanoidScena::keyPressed()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
    {
        mSystemRenderDebug.enabled();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
    {
        mSystemRenderDebug.disabled();
    }
}
///-------------------------------------------------------------------------




