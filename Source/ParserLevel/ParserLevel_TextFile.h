#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include "ParserLevel.h"

namespace parser
{
    ///-------------------------------------------------------------------------
    ///-------------------------------------------------------------------------





     ///------------------------------------------------------------------------
    ///
    /// <summary>
    /// Парсер текстового файла
    /// </summary>
    ///
    ///
    ///-------------------------------------------------------------------------
    class ATextFile
        :
        public AParserLevel
    {
        using super = AParserLevel;

    public:

        ATextFile(const std::string &fileName);
        ~ATextFile() override;


    public:


        bool readLine(std::vector<ecs::PActor> &line) override; //чтение одной строчки уровня
        dm::properties variables() const override { return mVariables;}; //базовые настройки

    private:


        std::string         mFileName;
        std::ifstream       mStream;
        dm::properties      mVariables;

    private:

        bool open(); //открытие файла
        ecs::PActor create(const float pos, const std::string &tag); //создание игрового объекта

        void parserVariables(const std::string &text);//парсим параметры
    };
    ///-------------------------------------------------------------------------




}
