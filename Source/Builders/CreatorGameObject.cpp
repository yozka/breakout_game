// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "CreatorGameObject.h"
#include "Utils/base_Random.h"

#include "Physics/Component_Body.h"
#include "Physics/Component_ShapeCircle.h"
#include "Physics/Component_ShapePolygon.h"
#include "Physics/Component_PhysicsDebug.h"

#include "Components/Graphics/Component_Sprite.h"
#include "Components/Graphics/Component_GeometryData.h"
#include "Components/Graphics/Component_DrawNumber.h"

#include "Components/Player/Component_PlayerControls.h"
#include "Components/Player/Component_Paddle.h"
#include "Components/Player/Component_Cling.h"
#include "Components/Player/Component_Weapon.h"

#include "Components/Briks/Component_CLLDestroyBrick.h"
#include "Components/Briks/Component_Brick.h"
#include "Components/Briks/Component_ScrollCan.h"
#include "Components/Briks/Component_DestroyBrick.h"

#include "Components/Balls/Component_CLLSpeedBall.h"
#include "Components/Balls/Component_Ball.h"

#include "Components/Bonus/Component_CLLBonusUse.h"
#include "Components/Bonus/Component_BonusLives.h"
#include "Components/Bonus/Component_BonusLivesFull.h"
#include "Components/Bonus/Component_BonusPaddleExpand.h"
#include "Components/Bonus/Component_BonusPaddleSqueeze.h"
#include "Components/Bonus/Component_BonusBall.h"
#include "Components/Bonus/Component_BonusBallSpeed.h"
#include "Components/Bonus/Component_BonusWeapon.h"

#include "Components/Gameplay/Component_CLLBullet.h"
#include "Components/Gameplay/Component_CLLCounter.h"
#include "Components/Gameplay/Component_CLLEffect.h"




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
ACreatorGameObject::ACreatorGameObject()
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
ACreatorGameObject::~ACreatorGameObject()
{


}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// созать игровую платформу
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createPaddle(const float length)
{
    int depth = 10;
    auto paddle = std::make_shared< ecs::AActor >();
    paddle->create<AComponentPlayerControls>();
    paddle->create<AComponentSprite>("paddle_left",     AComponentPaddle::left, depth++);
    paddle->create<AComponentSprite>("paddle_center",   AComponentPaddle::center, depth++);
    paddle->create<AComponentSprite>("paddle_right",    AComponentPaddle::right, depth++);
    paddle->create<AComponentBody>();
    paddle->create<AComponentShapePolygon>();
    paddle->create<AComponentPaddle>(length);
    paddle->create<AComponentCling>();
    paddle->create<AComponentCLLCounter<AComponentBall>>(); //подсчет количества столкновений


    //оружие
    const FPoint bulletPos(0, 20);

    paddle->create<AComponentSprite>("bonus_weapon", AComponentWeapon::left, depth++);
    paddle->create<AComponentSprite>("bonus_weapon", AComponentWeapon::right, depth++);
    paddle->create<AComponentSprite>("bullet_panel", AComponentWeapon::bulletPanel, depth++)->setPosition(bulletPos);
    paddle->create<AComponentDrawNumber>(AComponentWeapon::bulletNumber, depth++)->setPosition(bulletPos + FPoint(10, -3))->setScale(0.4f);

    paddle->create<AComponentWeapon>();

    paddle->create<AComponentPhysicsDebug>();
    return paddle;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// созать шар
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBall(const int speed, const FPoint &position, const float scale)
{
    const float factor = speed / 100.0f;

    const int tag = 0;
    const int depth = 500;
    auto ball = std::make_shared< ecs::AActor >();
    ball->create<AComponentSprite>("ballBlue", tag, depth)->setScale(scale);
    ball->create<AComponentBody>(position)->setBall();
    ball->create<AComponentShapeCircle>(24.0f * 0.5f * scale);
    ball->create<AComponentBall>(factor);
    ball->create<AComponentCLLSpeedBall>();
    ball->create<AComponentCLLEffect>("ball_collision");
    ball->create<AComponentPhysicsDebug>();
    return ball;
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// создать кирпич
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBrick(const std::string &name, const FPoint &position, const float angle)
{
    auto brick = std::make_shared< ecs::AActor >();
    brick->create<AComponentBody>(position)->setStatic();
    brick->create<AComponentShapePolygon>(brick->create<AComponentSprite>(name)->size() * 0.5f);
    brick->create<AComponentCLLDestroyBrick>();
    brick->create<AComponentBrick>();
    brick->create<AComponentScrollCanControl>();
    brick->create<AComponentDestroyBrick>();
    brick->create<AComponentPhysicsDebug>();
    return brick;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// создать синий кирпич
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBrick_blueRect(const FPoint &position, const float angle)
{
    auto brick = createBrick("element_blue_rectangle", position, angle);
    return brick;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// создать красный кирпич
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBrick_redRect(const FPoint &position, const float angle)
{
    auto brick = createBrick("element_red_rectangle", position, angle);
    return brick;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// создать зеленый кирпич
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBrick_greenRect(const FPoint &position, const float angle)
{
    auto brick = createBrick("element_green_rectangle", position, angle);
    return brick;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// создать серый кирпич
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBrick_greyRect(const FPoint &position, const float angle)
{
    auto brick = createBrick("element_grey_rectangle", position, angle);
    return brick;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// создать пурпурный кирпич
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBrick_purpleRect(const FPoint &position, const float angle)
{
    auto brick = createBrick("element_purple_rectangle", position, angle);
    return brick;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// создать желтый кирпич
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBrick_yellowRect(const FPoint &position, const float angle)
{
    auto brick = createBrick("element_yellow_rectangle", position, angle);
    return brick;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// бонус, прибавить одну жизнь
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBonus(const FPoint &position)
{
    auto bonus = std::make_shared< ecs::AActor >();
    bonus->create<AComponentBody>(position);
    bonus->create<AComponentShapePolygon>(25.0f, 25.0f);
    bonus->create<AComponentSprite>("boxBonus");
    bonus->create<AComponentCLLBonusUse>();
    bonus->create<AComponentPhysicsDebug>();
    return bonus;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// бонус, прибавить одну жизнь
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBonus_lives(const FPoint &position)
{
    auto bonus = createBonus(position);
    bonus->create<AComponentSprite>("hudHeart_full", 0, 1)->setScale(0.5f);
    bonus->create<AComponentBonusLives>();
    return bonus;
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// бонус, увеличивает все потраченные жизни
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBonus_livesFull(const FPoint &position)
{
    auto bonus = createBonus(position);
    bonus->create<AComponentSprite>("bonus_lives_full", 0, 1);
    bonus->create<AComponentBonusLivesFull>();
    return bonus;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// бонус, увеличивает ракетку
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBonus_paddleExpand(const FPoint &position)
{
    auto bonus = createBonus(position);
    bonus->create<AComponentSprite>("bonus_paddle_expand", 0, 1);
    bonus->create<AComponentBonusPaddleExpand>();
    return bonus;
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// бонус, уменьшает ракетку
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBonus_paddleSqueeze(const FPoint &position)
{
    auto bonus = createBonus(position);
    bonus->create<AComponentSprite>("bonus_paddle_squeeze", 0, 1);
    bonus->create<AComponentBonusPaddleSqueeze>();
    return bonus;
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// бонус, удваевает шары
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBonus_ball(const FPoint &position)
{
    auto bonus = createBonus(position);
    bonus->create<AComponentSprite>("bonus_ball", 0, 1);
    bonus->create<AComponentBonusBall>();
    return bonus;
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// бонус, уменьшает скорость шаров
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBonus_ballSpeed(const FPoint &position)
{
    auto bonus = createBonus(position);
    bonus->create<AComponentSprite>("bonus_ball_speed", 0, 1);
    bonus->create<AComponentBonusBallSpeed>();
    return bonus;
}
///-------------------------------------------------------------------------




 ///------------------------------------------------------------------------
///
/// <summary>
/// бонус, оружие
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBonus_weapon(const FPoint &position)
{
    auto bonus = createBonus(position);
    bonus->create<AComponentSprite>("bonus_weapon", 0, 1);
    bonus->create<AComponentBonusWeapon>();
    return bonus;
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// создание пули
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ACreatorGameObject::createBullet(const FPoint &position, const FPoint &direct)
{
    const auto &random = dm::ARandom::instance();

    const auto impulse  = 1000000.0f;
    const auto force    = direct * impulse;
    const auto contact  = FPoint(random.next(-20, 20), 0);

    auto bullet = std::make_shared< ecs::AActor >();
    auto body = bullet->create<AComponentBody>(position);
    bullet->create<AComponentShapeCircle>(45.0f / 2);
    bullet->create<AComponentSprite>("bullet_red");
    bullet->create<AComponentPhysicsDebug>();
    bullet->create<AComponentCLLBullet>();

    body->setBall();
    body->applyImpulse(force, contact);
    body->setBallSpeed(force.length());
    return bullet;
}
///-------------------------------------------------------------------------



