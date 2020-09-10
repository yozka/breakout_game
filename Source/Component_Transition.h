#pragma once
#include <memory>
#include <string>
#include <vector>


#include "ecs/update/aaComponent_Update.h"
#include "Component_Sprite.h"

namespace game
{
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Переход между экранами
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentTransition
        :
        public ecs::AComponentUpdate
    {
        using super = ecs::AComponentUpdate;

    public:

        AComponentTransition(const int cols, const int rows);
        ~AComponentTransition() override;


    public:

        void update(const float timeSpan) override;



    protected:

        std::vector<PComponentSprite> blocks; //блоки которые закрывают 
        void destroy();

    private:

        int mCols = { 0 };
        int mRows = { 0 };

    private:
    
        void initBlocks();
    };
    ///-------------------------------------------------------------------------



}
