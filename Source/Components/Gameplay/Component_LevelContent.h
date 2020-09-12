#pragma once
#include <memory>
#include <string>
#include <vector>
#include <list>

#include "ecs/aaComponent.h"

namespace game
{

    namespace settings
    {
        constexpr float height_block = 32; //размерность блока по высоте
    }




    ///------------------------------------------------------------------------
   ///
   /// <summary>
   /// Штуковина которая спавнит новые блоки уровня
   /// все блоки хранятся ввиде списка
   /// </summary>
   ///
   ///
   ///-------------------------------------------------------------------------
    class AComponentLevelContent
        :
        public ecs::AComponent
    {
        using super = ecs::AComponent;

    public:

        AComponentLevelContent();
        ~AComponentLevelContent() override;


    public:

        bool isEmpty()const; //проверка, есть еще данные для спавна уровня
        void append(const std::vector<ecs::PActor> &line); //добавить одну линию уровня


        void nextSpawn(); //выведем следующую строчку уровня
        void firstSpawn(const int countRows); //выводим строки уровня сразу
        void emptyTrim(); //удалим первые и последние пустые строчки

    private:

        std::list<std::vector<ecs::PActor>> mContents;//список уровня


    private:

        void spawn(const float pos_y, const std::vector<ecs::PActor> &line); //спавн в указанную позицию

    };
    ///-------------------------------------------------------------------------


    using PComponentLevelContent = std::shared_ptr< AComponentLevelContent >;

}
