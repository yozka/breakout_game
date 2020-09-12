// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Component_Options.h"
#include "ParserLevel/ParserFactory.h"




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
AComponentOptions::AComponentOptions()
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
AComponentOptions::~AComponentOptions()
{

}
///-------------------------------------------------------------------------






 ///------------------------------------------------------------------------
///
///
///
/// 
///
///
///-------------------------------------------------------------------------
std::shared_ptr<AComponentOptions> AComponentOptions::fromFile(const std::string &fileName)
{
    auto options = std::make_shared<AComponentOptions>();

    AFactory factory;
    if (auto file = factory.create(fileName))
    {
        std::vector<ecs::PActor> line;
        while (file->readLine(line));
        options->mParameters = file->variables();
    }
    
    return options;
}
///-------------------------------------------------------------------------







 ///------------------------------------------------------------------------
///
///
///
/// размер ракетки
///
///
///-------------------------------------------------------------------------
int AComponentOptions:: paddleLength()
{
    return mParameters.toInt("PlatformWidth", 200);
}
///-------------------------------------------------------------------------





 ///------------------------------------------------------------------------
///
///
///
/// скорость шаров 
///
///
///-------------------------------------------------------------------------
int AComponentOptions::speedBall()
{
    return mParameters.toInt("Speed", 100);
}
///-------------------------------------------------------------------------



