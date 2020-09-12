#pragma once
#include <memory>
#include <string>
#include <vector>


#include "ecs/update/aaComponent_Update.h"
#include "Components/Graphics/Component_Geometry.h"

namespace game
{
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// удаление всех объектов, которые вышли за пределы экрана
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentDestroyOutArea
        :
        public ecs::AComponentUpdate
    {
        using super = ecs::AComponentUpdate;

    public:

        AComponentDestroyOutArea();
        ~AComponentDestroyOutArea() override;


    public:

        void updateSlow(const float timeSpan) override;
     
    private:

        using TList = std::vector<PComponentGeometry>;
        TList mObjects;
        TList::const_iterator mCurrent = {mObjects.cbegin()};

        void next(); //првоерим следующий объект
    };
    ///-------------------------------------------------------------------------



}
