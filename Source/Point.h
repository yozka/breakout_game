#pragma once
#include <memory>
#include <math.h>

template <typename T>
struct Point
{

    ////////////////////////////////////////////////////////////
    T x = { 0 };
    T y = { 0 };



    ////////////////////////////////////////////////////////////
    Point()
    {
    }


    ////////////////////////////////////////////////////////////
    Point(const T& value)
        :
        x(value),
        y(value)
    {
    }


    ////////////////////////////////////////////////////////////
    template <typename TT>
    Point(const TT& X, const TT& Y)
        :
        x(static_cast<T>(X)),
        y(static_cast<T>(Y))
    {
    }



    ////////////////////////////////////////////////////////////
    Point(const T& X, const T& Y)
        :
        x(X),
        y(Y)
    {
    }




    T length() const
    {
        return sqrtf(x * x + y * y);
    }


    T lengthSquared() const
    {
        return x * x + y * y;
    }


    T normalize()
    {
        const auto len = length();
        if (len < FLT_EPSILON)
        {
            return 0;
        }
        const auto invLength = 1 / len;
        x *= invLength;
        y *= invLength;

        return len;
    }

};
////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////
template <typename T>
inline Point<T> operator -(const Point<T>& right)
{
    return Point<T>(-right.x, -right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Point<T>& operator +=(Point<T>& left, const Point<T>& right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
inline Point<T>& operator -=(Point<T>& left, const Point<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
inline Point<T> operator +(const Point<T>& left, const Point<T>& right)
{
    return Point<T>(left.x + right.x, left.y + right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Point<T> operator -(const Point<T>& left, const Point<T>& right)
{
    return Point<T>(left.x - right.x, left.y - right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Point<T> operator *(const Point<T>& left, T right)
{
    return Point<T>(left.x * right, left.y * right);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Point<T> operator *(T left, const Point<T>& right)
{
    return Point<T>(right.x * left, right.y * left);
}


//1
////////////////////////////////////////////////////////////
template <typename T>
inline Point<T> operator *(const Point<T>& left, Point<T>& right)
{
    return Point<T>(left.x * right.x, left.y * right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Point<T> operator *(Point<T>& left, const Point<T>& right)
{
    return Point<T>(right.x * left.x, right.y * left.y);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Point<T> operator *(const Point<T>& left, const Point<T>& right)
{
    return Point<T>(right.x * left.x, right.y * left.y);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Point<T> operator *(Point<T>& left, Point<T>& right)
{
    return Point<T>(right.x * left.x, right.y * left.y);
}
//


////////////////////////////////////////////////////////////
template <typename T>
inline Point<T>& operator *=(Point<T>& left, T right)
{
    left.x *= right;
    left.y *= right;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
inline Point<T> operator /(const Point<T>& left, T right)
{
    return Point<T>(left.x / right, left.y / right);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Point<T>& operator /=(Point<T>& left, T right)
{
    left.x /= right;
    left.y /= right;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
inline bool operator ==(const Point<T>& left, const Point<T>& right)
{
    return (left.x == right.x) && (left.y == right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
inline bool operator !=(const Point<T>& left, const Point<T>& right)
{
    return (left.x != right.x) || (left.y != right.y);
}






using FPoint = Point<float>;
using IPoint = Point<int>;