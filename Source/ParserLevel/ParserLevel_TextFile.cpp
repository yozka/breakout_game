// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <functional>

#include "ParserLevel/ParserLevel_TextFile.h"
#include "Builders/CreatorGameObject.h"
#include "Utils/base_String.h"
#include "Device.h"


///-------------------------------------------------------------------------
using namespace parser;
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// Constructor
///
///
///-------------------------------------------------------------------------
ATextFile::ATextFile(const std::string &fileName)
    :
    mFileName(fileName)
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
ATextFile::~ATextFile()
{

}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// чтение одной строчки уровня 
/// </summary>
///
///-------------------------------------------------------------------------
bool ATextFile::readLine(std::vector<ecs::PActor> &line)
{
    line.clear();
    if (!open()) return false;

    std::string text;

    if (!std::getline(mStream, text))
    {
        return false;
    }

    
    if (text.find("##") != std::string::npos)
    {
        //всчтрочке есть комментарии
        return true;
    }

    //парсим параметры
    parserVariables(text);


    const auto tags = dm::split(text, '|');
    if (tags.size() < 5)
    {
        //данных по уровню нет
        return true;
    }

    const float widthObj = 64; //размер игрового объекта
    const float width = dm::deviceWidth();
    float pos_x = (width - (widthObj * tags.size())) * 0.5f;// - (widthObj * 0.5f);
    for (const auto &tag : tags)
    {
        if (const auto obj = create(pos_x, tag))
        {
            line.push_back(obj);
        }
        pos_x += widthObj;
    }

    return true;
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
/// <summary>
/// парсим параметры
/// </summary>
///
///-------------------------------------------------------------------------
void ATextFile::parserVariables(const std::string &text)
{
    const auto vars = dm::split(text, '=', true);
    if (vars.size() != 2)
    {
        return;
    }

    const auto name = vars[0];
    const auto param = vars[1];
    
    size_t ok = 0;
    int param_i = std::stoi(param, &ok);
    if (ok)
    {
        mVariables.setInt(name, param_i);
        return;
    }

    mVariables.setString(name, param);

}





 ///------------------------------------------------------------------------
///
/// <summary>
/// открытие файла
/// </summary>
///
///-------------------------------------------------------------------------
bool ATextFile::open()
{
    if (mStream.is_open())
    {
        return true;
    }
    mStream.open("data/"+mFileName);
    return mStream.is_open();
}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
/// <summary>
/// создание игрового объекта
/// по канону это должен быть фабричный метод
/// </summary>
///
///-------------------------------------------------------------------------
ecs::PActor ATextFile::create(const float pos, const std::string &tag)
{
    const auto creator = std::make_shared<game::ACreatorGameObject>();
    static const std::map<std::string, std::function<ecs::PActor(float)>> factory_map =
    {
        //блоки
        {"BB", [creator](auto pos) { return creator->createBrick_blueRect   ({pos, 0}, 0); }},
        {"GG", [creator](auto pos) { return creator->createBrick_greenRect  ({pos, 0}, 0); }},
        {"EE", [creator](auto pos) { return creator->createBrick_greyRect   ({pos, 0}, 0); }},
        {"PP", [creator](auto pos) { return creator->createBrick_purpleRect ({pos, 0}, 0); }},
        {"RR", [creator](auto pos) { return creator->createBrick_redRect    ({pos, 0}, 0); }},
        {"YY", [creator](auto pos) { return creator->createBrick_yellowRect ({pos, 0}, 0); }},

        //бонусы
        {"+l", [creator](auto pos) { return creator->createBonus_lives          ({pos, 32}); }},
        {"+f", [creator](auto pos) { return creator->createBonus_livesFull      ({pos, 32}); }},
        {"+p", [creator](auto pos) { return creator->createBonus_paddleExpand   ({pos, 32}); }},
        {"+q", [creator](auto pos) { return creator->createBonus_paddleSqueeze  ({pos, 32}); }},
        {"+b", [creator](auto pos) { return creator->createBonus_ball           ({pos, 32}); }},
        {"+s", [creator](auto pos) { return creator->createBonus_ballSpeed      ({pos, 32}); }},
        {"+w", [creator](auto pos) { return creator->createBonus_weapon         ({pos, 32}); }}

    };
    

    const auto it = factory_map.find(tag);
    if (it != factory_map.cend())
    {
        return it->second(pos);
    }
    return ecs::PActor();
}