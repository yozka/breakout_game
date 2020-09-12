#pragma once
#include <memory>
#include <math.h>

#include "Point.h"


namespace math
{
    constexpr float EPSILON     = 0.00001f;
    constexpr float PI          = 3.141592654f;
    constexpr float OneByPI     = 1 / PI;
    constexpr float SqrtPI      = 1.772453851f;


    inline bool isZero(const float a)
    {
        return std::fabsf(a) < EPSILON;
    }

    inline bool isEqualFloat(const float a, const float b)
    {
        return std::fabsf(a - b) < EPSILON;
    }


    /// Возвращает left, если value < left, right, если value > right, иначе value.
    /// Использовать можно только арифметические типы.
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    constexpr T clamp(T left, T right, T value)
    {
        return (value < left) ? left : (value > right) ? right : value;
    }


    /// Квадрат числа
    constexpr float sqr(float value) { return value * value; }


    template <typename T>
    constexpr bool isLessOrEqual(const T a, const T b, const T delta = EPSILON)
    {
        return (a - delta <= b);
    }

    template <typename T>
    constexpr bool isGreaterOrEqual(const T a, const T b, const T delta = EPSILON) 
    {
        return (a + delta >= b);
    }


    inline FPoint cross(const FPoint &v, float a)
    {
        return { a * v.y, -a * v.x };
    }

    inline FPoint cross(float a, const FPoint &v)
    {
        return { -a * v.y, a * v.x };
    }

    inline float cross(const FPoint &a, const FPoint &b)
    {
        return a.x * b.y - a.y * b.x;
    }

    inline float dot(const FPoint& a, const FPoint& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    inline float distSqr(const FPoint& a, const FPoint& b)
    {
        const auto c = a - b;
        return dot(c, c);
    }


    inline float lengthSqr(const FPoint& v)
    {
        return v.x * v.x + v.y * v.y;
    }


    inline bool biasGreaterThan(const float a, const float b)
    {
        const float k_biasRelative = 0.95f;
        const float k_biasAbsolute = 0.01f;
        return a >= b * k_biasRelative + a * k_biasAbsolute;
    }


    //матрица 2х2
    struct matrix2
    {
        union 
        {
            struct
            {
                float m00, m01;
                float m10, m11;
            };

            float m[2][2];
            float v[4];
        };


        matrix2()
            :
            m00(0.0f), m01(0.0f),
            m10(0.0f), m11(0.0f)
        {
        }
        
        matrix2(const float radians)
        {
            setAngle(radians);
        }


        matrix2(const float a, const float b, const float c, const float d)
            :
                m00(a), m01(b),
                m10(c), m11(d)
        {

        }


        
        void setAngle(const float radians)
        {
            float c = std::cos(radians);
            float s = std::sin(radians);

            m00 = c; m01 = -s;
            m10 = s; m11 = c;
        }


        matrix2 transpose() const
        {
            return matrix2( m00, m10, m01, m11);
        }

        const FPoint operator * (const FPoint &rhs) const
        {
            return FPoint( m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y);
        }

    };//matrix2





}

