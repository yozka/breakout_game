#pragma once
#include <memory>
#include <vector>

#include "Utils/base_Properties.h"
#include "ecs/aaActor.h"

namespace parser
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Парсер уровня
    /// интерфейс
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AParserLevel
    {
    public:

        AParserLevel() = default;
        virtual ~AParserLevel() = default;


    public:


        virtual bool readLine(std::vector<ecs::PActor> &line) = 0; //чтение одной строчки уровня

        virtual dm::properties variables() const= 0; //параметры

    };
    ///-------------------------------------------------------------------------


    using PParserLevel = std::shared_ptr< AParserLevel >;


}
