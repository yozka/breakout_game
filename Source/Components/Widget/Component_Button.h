#pragma once
#include <memory>
#include <string>
#include <functional>

#include "Systems/Component_Input.h"

namespace game
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Кнопка которую можно нажимать мышкой
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class AComponentButton
        :
        public AComponentInput
    {
        using super = AComponentInput;
        using TSignal = std::function<void()>;

    public:


        AComponentButton(const TSignal &signal);
        ~AComponentButton();

    public:

        enum TAGS : int
        {
            tagNormal,
            tagPushed,
            tagHover,
            tagIcon
        };

    public:

        void changeComponents() override; //компоненты поменялись, что-то добавилось, что-то удалилось


        bool mouseDown  (const dm::EventInput &input) override;
        void mouseMove  (const dm::EventInput &input) override;
        void mouseUp    (const dm::EventInput &input) override;

   
        void update(const float timeSpan) override;

    private:

        //статус кнопки
        enum STATUS
        {
            none, //ничего нет
            hover, //подсвечена
            pushed //нажата
        };


        TSignal mSignalClick = { nullptr };
        
        STATUS mStatus  = { none };
        bool mPushed    = {false}; //кнопка нажата

    private:
        void changeStatus(const STATUS &st); //установка нового статуса
        bool isArea(const IPoint &mouse) const; //првоерка, мышка находится на кнопке или нет
        void correctIcon(); //выставляем корректную позицию иконки, взависемости нажата или нет кнопка
    };
    ///-------------------------------------------------------------------------




}
