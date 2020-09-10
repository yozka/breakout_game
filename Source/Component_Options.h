#pragma once
#include <memory>
#include <string>

#include "base_Properties.h"
#include "ecs/aaComponent.h"

namespace parser
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Игровые настройки
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentOptions
        :
            public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

        static std::shared_ptr<AComponentOptions> fromFile(const std::string &fileName);

    public:

        AComponentOptions();
        virtual ~AComponentOptions();


    public:


        int paddleLength(); //размер ракетки
        int speedBall(); //скорость шаров 

    private:

        dm::properties mParameters;

    };
    ///-------------------------------------------------------------------------


   
    using PComponentOptions = std::shared_ptr< AComponentOptions >;


}
