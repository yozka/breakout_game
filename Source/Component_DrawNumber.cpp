// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_DrawNumber.h"
#include "Device.h"
#include "Rect.h"



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
AComponentDrawNumber::AComponentDrawNumber(const int tag, const int depth)
    :
    super(depth),
    mTag(tag)
{
    for (int i = 0; i < 10; i++)
    {
        mTextures[i] =  dm::loadSprite("hud" + std::to_string(i));
    }

    setNumber(0);
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
AComponentDrawNumber::~AComponentDrawNumber()
{


}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// возвратим текущую текстуру
/// </summary>
///
///-------------------------------------------------------------------------
void AComponentDrawNumber::draw(dm::ARender &render)
{

    const float width = 64;
    const float height = 64;
    const FPoint origin(width * 0.5f, height * 0.5f);

    render.matrixTranslate((-origin * mScale) + mPosition);

    const FPoint    shift   (-height * mScale.y * mKerning, 0.0f);

    if (mNumber == 0)
    {
        mTextures[0].setScale(mScale.x, mScale.y);
        render.render(mTextures[0]);
    }
    else
    {
        int number = mNumber;
        while (number > 0)
        {
            int id = number % 10;
            number = number / 10;
    
            mTextures[id].setScale(mScale.x, mScale.y);
            render.render(mTextures[id]);

            render.matrixTranslate(shift);
        }
    }
}
///-------------------------------------------------------------------------









 ///------------------------------------------------------------------------
///
/// <summary>
/// масштаб спрайта
/// </summary>
///
///-------------------------------------------------------------------------
AComponentDrawNumber::pthis AComponentDrawNumber::setScale(const float scale)
{
    mScale = { scale, scale };
    return this;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// возвратим тег спрайта
/// </summary>
///
///-------------------------------------------------------------------------
int AComponentDrawNumber::tag() const
{
    return mTag;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// установка позиции
/// </summary>
///
///-------------------------------------------------------------------------
AComponentDrawNumber::pthis AComponentDrawNumber::setPosition(const FPoint &position)
{
    mPosition = position;
    return this;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// масштаб спрайта
/// </summary>
///
///-------------------------------------------------------------------------
AComponentDrawNumber::pthis AComponentDrawNumber::setScale(const FPoint &scale)
{
    mScale = scale;
    return this;
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
/// <summary>
/// установка числа
/// </summary>
///
///-------------------------------------------------------------------------
AComponentDrawNumber::pthis AComponentDrawNumber::setNumber(const int value)
{
    mNumber = value;
    return this;
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// установка режим отображения
/// </summary>
///
///-------------------------------------------------------------------------
AComponentDrawNumber::pthis AComponentDrawNumber::setVisible(const bool enabled)
{
    mVisible = enabled;
    return this;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// проверка спрайт нужно отрисовывать или нет
/// </summary>
///
///-------------------------------------------------------------------------
bool AComponentDrawNumber::isVisible() const
{
    return mVisible;
}
///-------------------------------------------------------------------------

