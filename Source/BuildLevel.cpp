// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "BuildLevel.h"
#include "Device.h"

#include "Rect.h"
#include "CreatorGameObject.h"
#include "CreatorWidget.h"
#include "ParserFactory.h"

#include "Component_Options.h"
#include "Component_Body.h"
#include "Component_ShapePolygon.h"
#include "Component_Cling.h"
#include "Component_Lives.h"
#include "Component_GeometryData.h"
#include "Component_DestroyOutArea.h"
#include "Component_LivesToBall.h"
#include "Component_Sprite.h"
#include "Component_GameOver.h"
#include "Component_GameWins.h"
#include "Component_ScrollDown.h"
#include "Component_LevelContent.h"
#include "Component_WaitToBall.h"
#include "Component_Effects.h"
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
ABuildLevel::ABuildLevel(ecs::AContainer *container)
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
ABuildLevel::~ABuildLevel()
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
void ABuildLevel::build()
{
    mContainer->clear();


    {
        //создание виджетов
        ACreatorWidget widgets;
        mContainer->append(widgets.createHUD(5));
        mContainer->append(widgets.createBackgroundForest());
    }


    //добавм на сцену настройки
    auto options = parser::AComponentOptions::fromFile("input.txt");
    {
        auto actor = mContainer->append(std::make_shared<ecs::AActor>());
        actor->append(options);
    }
    //


    //создание ракетки и мяча
    ACreatorGameObject creator;
    auto paddle = creator.createPaddle(static_cast<float>(options->paddleLength()));
    mContainer->append(paddle);
 
    auto ball = creator.createBall(options->speedBall(), {0.0f, 0.0f}, 1.0f);
    mContainer->append(ball);

    if (const auto cling = paddle->findComponent<AComponentCling>())
    {
        cling->clingBall(ball);
    }
    //


    //создание геймлпея
    makeBoundingArea();
    makeGameplay();
    makeLevel("level.txt"); //создание уровня
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// создадим ограничители
/// </summary>
///
///-------------------------------------------------------------------------
void ABuildLevel::makeBoundingArea()
{
    const float width = dm::deviceWidth();
    const float height = dm::deviceHeight();

    const float depth = 100;
    
    const auto bound = [&](const FRect &rect)
    {
        auto obj = mContainer->append(std::make_shared< ecs::AActor >());
        auto body = std::make_shared<AComponentBody>(rect.centerPoint());
        body->setStatic();
        obj->append(body);
        obj->append(std::make_shared<AComponentShapePolygon>(rect.width() * 0.5f, rect.height() * 0.5f));
        //obj->append(std::make_shared<AComponentPhysicsDebug>());
    };


    bound({-depth, 0, -depth, height + depth}); //left
    bound({ width, width + depth, -depth, height + depth }); //right
    bound({-depth, width + depth, -depth, 0});//top
}
///-------------------------------------------------------------------------








 ///------------------------------------------------------------------------
///
/// <summary>
/// создадим базовый геймплей
/// </summary>
///
///-------------------------------------------------------------------------
void ABuildLevel::makeGameplay()
{
    //создадим обработчики геймплея
    const auto gameplay = mContainer->append(std::make_shared<ecs::AActor>());
    gameplay->create<AComponentDestroyOutArea>();//удаляем объекты которые ушли за пределы экрана
    gameplay->create<AComponentLivesToBall>(); //преобразуем жизни в мячи (если мяча нет)
    gameplay->create<AComponentWaitToBall>(); //если нет активности, то дадим игроку новый мячь
    gameplay->create<AComponentGameOver>();//проверяем на проигрышь в игре
    gameplay->create<AComponentGameWins>();//проверяем на выигрышь в игре
    gameplay->create<AComponentScollDown>(8);//скролинг уровня вниз
    gameplay->create<AComponentLevelContent>();//создание системы контента кирпичей
    gameplay->create<AComponentEffects>(200);//эффекты
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// создание уровня из файла
/// </summary>
///
///-------------------------------------------------------------------------
void ABuildLevel::makeLevel(const std::string &fileName)
{
    //компонент который содержит весь уровень блоков, 
    //во время игры, эти блоки спавнятся на игровой уровень
    const auto content = mContainer->findComponent<AComponentLevelContent>();
    if (!content) return;
    
    //создаем парсер файла
    parser::AFactory factory;
    if (const auto file = factory.create(fileName))
    {
        //бежим по всему файлу и получаем игровые объекты
        //виде одной строки уровня
        std::vector<ecs::PActor> line;
        while (file->readLine(line))
        {
            //добавляем строку с блоками в игровой уровень
            content->append(line);
        }
    }
    //

    content->emptyTrim(); //удалить последние и первые пустые блоки
    content->firstSpawn(8); //покажем первые 8 рядов уровня
}