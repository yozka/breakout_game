#pragma once
#include <memory>
#include <random>


namespace dm
{
    ///-------------------------------------------------------------------------








    ///------------------------------------------------------------------------
   ///
   ///
   ///
   /// ќшибка при создании индификатора
   ///
   ///
   ///-------------------------------------------------------------------------
    class ARandom
    {
    public:

        static ARandom& instance()
        {
            static ARandom random;
            return random;
        }

        ARandom(ARandom const&) = delete;
        ARandom& operator = (ARandom const&) = delete;

    public:

        ARandom();

        int next(const int min, const int max) const; //генераци¤ целочисленных чисел от мин до (максимлаьно - 1) значения
        int next(const int max) const; //генераци¤ целочисленного числа от 0 до максимального

        float next(const float min, const float max) const;
        float nextReal() const; //генераци¤ вещественного числа от о до 1

        bool isChance(const float procent) const; //шанс выподания, показываем процент от 0 до 100%

    private:

        std::random_device      mDevice;
        mutable std::mt19937_64 mGenerator;

    };
    ///-------------------------------------------------------------------------







}
