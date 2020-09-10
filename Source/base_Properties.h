#pragma once
#include <memory>
#include <string>
#include <variant>
#include <map>
#include <iostream>
#include <initializer_list>
#include <vector>
namespace dm
{
	using variant = std::variant<std::string, int, float, bool>;
   

    template <typename T>
    const T& get(const variant &v, const T &def)
    {
        const auto* pValue = std::get_if<T>(&v);
        if (pValue)
        {
            return *pValue;
        }
        return def;
    }

	
	struct properties
		: std::map< std::string, variant >
	{
        
		//constructors
		properties() = default;


		// конструктор для одной пары, пример использования
		//
		// su::properties prop = {"key1", std::string("value1")};
		//
		properties(const std::string &key, const variant &value)
		{
			insert({ key, value });
		}
		//

		
		// конструктор для списка, пример использования
		//
		// su::properties prop = { {"key1", std::string("value1")}, {"key2", std::string("value2")} };
		//
		properties(const std::initializer_list<std::pair<std::string, variant>> &list)
		{
			for (const auto &item : list)
			{
				insert({item.first, item.second});
			}
		}
		//

		template <typename T>
		const T& value(const std::string &key, const T &def) const
		{
			const auto index = find(key);
			if (index != cend())
			{
                return get<T>(index->second, def);
            }
			return def;
		}



		inline int toInt(const std::string &key, const int def = 0) const
		{
			return value<int>(key, def);
		}



		inline float toFloat(const std::string &key, const float def = 0.0f) const
		{
			return value<float>(key, def);
		}



		inline bool toBool(const std::string &key, const bool def = false) const
		{
			return value<bool>(key, def);
		}



		inline const std::string& toString(const std::string &key, const std::string &def = std::string()) const
		{
			return value<std::string>(key, def);
		}



		inline void setInt(const std::string &key, const int value) 
		{
			emplace( key, value);
		}



		inline void setFloat(const std::string &key, const float value)
		{
            emplace( key, value );
		}



		inline void setBool(const std::string &key, const bool value)
		{
            emplace( key, value );
		}



		inline void setString(const std::string &key, const std::string &value)
		{
            emplace( key, value );
		}


        inline void appendChild(const std::string &key, const dm::properties& prop)
        {
            //Warning! Can contain pairs with same key - not bug, feature!
            childs.emplace_back(std::make_pair(key, prop));
        }

        std::vector<std::pair<std::string, dm::properties>> childs;
        
	};
         
}


//сериализация данных
std::istream & operator >> (std::istream & s, dm::variant & v);
std::ostream & operator << (std::ostream & s, dm::variant const & v);

std::istream & operator >> (std::istream & s, dm::properties & prop);
std::ostream & operator << (std::ostream & s, dm::properties const & prop);
