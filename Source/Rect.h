#pragma once
#include <math.h>
#include "Point.h"
#include "MathUtils.h"


template <typename T>
struct Rect
{
    T xStart    = { 0 };
    T xEnd      = { 0 };
    T yStart    = { 0 };
    T yEnd      = { 0 };


    // Покомпонентный конструктор
    constexpr Rect(const T xStartValue, const T xEndValue, const T yStartValue, const T yEndValue)
        : 
        xStart(xStartValue),
        xEnd(xEndValue),
        yStart(yStartValue),
        yEnd(yEndValue)
    {
    }

    template <typename TT>
    constexpr Rect(const TT xStartValue, const TT xEndValue, const TT yStartValue, const TT yEndValue)
        :
        xStart  (static_cast<T>(xStartValue)),
        xEnd    (static_cast<T>(xEndValue)),
        yStart  (static_cast<T>(yStartValue)),
        yEnd    (static_cast<T>(yEndValue))
    {
    }


    // Возвращает ширину прямоугольника
    constexpr T width() const 
    {
        return std::abs(xEnd - xStart);
    }

    // Возвращает высоту прямоугольника
    constexpr T height() const 
    {
        return std::abs(yEnd - yStart);
    }


    // Возвращает центральную точку прямоугольника
    constexpr Point<T> centerPoint() const 
    {
        return {(xStart + xEnd) / 2, (yStart + yEnd) / 2};
    }


    // Содержит ли прямоугольник точку point
    constexpr bool contains(const Point<T>& point) const  
    {
        return  math::isGreaterOrEqual<T>  (point.x, std::min(xStart, xEnd)) &&
                math::isLessOrEqual<T>     (point.x, std::max(xStart, xEnd)) &&
                math::isGreaterOrEqual<T>  (point.y, std::min(yStart, yEnd)) &&
                math::isLessOrEqual<T>     (point.y, std::max(yStart, yEnd));
    }

};



using FRect = Rect<float>;
using IRect = Rect<int>;