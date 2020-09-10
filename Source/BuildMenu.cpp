// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "BuildMenu.h"
#include "BuildLevel.h"
#include "Device.h"
#include "base_Random.h"

#include "CreatorGameObject.h"
#include "CreatorWidget.h"



#include "Component_Body.h"
#include "Component_ShapePolygon.h"
#include "Component_Cling.h"
#include "Component_Lives.h"
#include "Component_GeometryData.h"
#include "Component_DestroyOutArea.h"
#include "Component_LivesToBall.h"
#include "Component_Sprite.h"
#include "Component_Timer.h"
#include "Component_ShapeCircle.h"
#include "Component_Body.h"
#include "Component_PhysicsDebug.h"


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
ABuildMenu::ABuildMenu(ecs::AContainer *container)
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
ABuildMenu::~ABuildMenu()
{


}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// Сборка уровня
/// </summary>
///
///-------------------------------------------------------------------------
void ABuildMenu::build()
{
    const float width = dm::deviceWidth();
    const float height = dm::deviceHeight();
    const float buttonY = height * 0.7f;
    


    ACreatorWidget creator;


    auto container = mContainer;
    container->clear();

   
    container->append(creator.createBackground());
    makeBanner();
    makeBrick(buttonY);
    makeSpawnBall();
    
    //Начало новой игры
    const auto startGame = [container]()
    {
        ABuildLevel level(container);
        level.build();
    };


    //Переход
    const auto transition = [container, startGame]()
    {
        ACreatorWidget creator;
        container->append(creator.createTransitionHide([container, startGame]()
        {
            //скрыли экран, он чорный
            //запускаем игру и создаем открытие экрана
            startGame();
            ACreatorWidget creator;
            container->append(creator.createTransitionShow());
        }));
    };
    container->append(creator.createButtonIcon({width*0.5f, buttonY}, "label_play", transition));

}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
void ABuildMenu::makeBanner()
{
    const float width = dm::deviceWidth();
    const float height = dm::deviceHeight();

   
    auto obj = mContainer->append(std::make_shared< ecs::AActor >());
    obj->create<AComponentGeometryData>(FPoint({width * 0.5f, height * 0.3f}));
    obj->create<AComponentSprite>("banner", 0, 100);
    
}
///-------------------------------------------------------------------------








 ///------------------------------------------------------------------------
///
/// <summary>
/// 
/// </summary>
///
///-------------------------------------------------------------------------
void ABuildMenu::makeBrick(const float posY)
{
    ACreatorGameObject creator;

    const int cols = 4;

    const int brickWidth = 64;
    const int brickHeight = 32;
    const FPoint shift((dm::deviceWidth() - brickWidth * cols) * 0.5f, posY);
    const FPoint dm(0, 60);
    for (int i = 0; i <= cols; i++)
    {
        const auto pos = FPoint(i * brickWidth, 0) + shift;
        mContainer->append(creator.createBrick_redRect(pos + dm, 0));
        mContainer->append(creator.createBrick_redRect(pos - dm, 0));
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
void ABuildMenu::makeSpawnBall()
{
    //лямбда которая создает шарик
    const auto onSpawn = [](const auto timer)
    {
        //стартовая позиция шарика
        const auto container = timer->getContainer();
        const auto geometry = timer->findComponent<AComponentGeometry>();
        if (!geometry) return;
        if (!container) return;

        
        const auto &random = dm::ARandom::instance();
        const float impulse = random.next(50, 99) * 10000.0f;
        const FPoint force(random.next(-1.0f, 1.0f), -5.0f);
        const float scale = random.next(0.5f, 1.2f);


        auto ball = container->append(std::make_shared< ecs::AActor >());
        ball->create<AComponentSprite>("ballBlue")->setScale(scale);
        ball->create<AComponentBody>(geometry->position())->applyForce(force * impulse);
        ball->create<AComponentShapeCircle>(24.0f * 0.5f * scale);
        ball->create<AComponentPhysicsDebug>();

    };


    const float width = dm::deviceWidth();
    const float height = dm::deviceHeight();


    auto obj = mContainer->append(std::make_shared< ecs::AActor >());
    obj->create<AComponentGeometryData>(FPoint({ width * 0.5f, -50 }));
    obj->create<AComponentDestroyOutArea>();
    obj->create<AComponentTimer>(1.0f, onSpawn);
    
}
///-------------------------------------------------------------------------


