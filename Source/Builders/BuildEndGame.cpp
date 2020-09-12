// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "BuildEndGame.h"
#include "BuildMenu.h"
#include "Device.h"
#include "CreatorWidget.h"

#include "Components/Player/Component_PlayerControls.h"
#include "Components/Graphics/Component_Sprite.h"
#include "Components/Gameplay/Component_GameOver.h"
#include "Components/Gameplay/Component_GameWins.h"

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
ABuildEndGame::ABuildEndGame(ecs::AContainer *container)
    :
    mContainer(container)
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
ABuildEndGame::~ABuildEndGame()
{


}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// Сборка 
/// </summary>
///
///-------------------------------------------------------------------------
void ABuildEndGame::build()
{
    const auto container = mContainer;
    const float width = dm::deviceWidth();
    const float height = dm::deviceHeight();
    ACreatorWidget creator;

    remove<AComponentPlayerControls>();
    remove<AComponentGameOver>();
    remove<AComponentGameWins>();

    onBuild();

       



    const auto startMenu = [container]()
    {
        ABuildMenu menu(container);
        menu.build();
    };


    //Переход
    const auto transition = [container, startMenu]()
    {
        ACreatorWidget creator;
        container->append(creator.createTransitionHide([container, startMenu]()
        {
            //скрыли экран, он чорный
            //запускаем меню и создаем открытие экрана
            startMenu();
            ACreatorWidget creator;
            container->append(creator.createTransitionShow());
        }));
    };

    auto but = container->append(creator.createButtonIcon({ width * 0.5f, height * 0.75f }, "label_menu", transition));
    but->create<AComponentSprite>("yellow_panel", 0, 5);
}
///-------------------------------------------------------------------------









