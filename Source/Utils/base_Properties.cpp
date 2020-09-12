// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "base_Properties.h"

// сериализация variant в поток
template <typename T>
void variant_write(std::ostream & s, dm::variant const & v)
{
   	const auto* value = std::get_if<T>(&v);
    if (value)
    {
        s.write(reinterpret_cast<const char*>(value), sizeof(T));
    }
}



void writeString(std::ostream & s, const std::string &value)
{
	const size_t size = value.length();
	s.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	if (size)
	{
		s.write(value.c_str(), value.length());
	}
}



void variant_writeString(std::ostream & s, dm::variant const & v)
{
    writeString(s, dm::get<std::string>(v, std::string()));
}



std::ostream & operator << (std::ostream & s, dm::variant const & v)
{
	const uint8_t type = static_cast<const uint8_t>(v.index());
	s.write(reinterpret_cast<const char*>(&type), sizeof(uint8_t));
	switch (type)
	{
	case 0: variant_writeString(s, v); break;
	case 1: variant_write<int>(s, v); break;
	case 2: variant_write<float>(s, v); break;
	case 3: variant_write<bool>(s, v); break;
	}
	return s;
}





//десериализация данных из потока

template <typename T>
void variant_read(std::istream & s, dm::variant & v)
{
	T data;
	s.read(reinterpret_cast<char*>(&data), sizeof(T));
	v = data;
}



std::string readString(std::istream & s)
{
	size_t size = 0;
	s.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	if (!size)
	{
		return std::string();
	}
	std::string value;
	value.resize(size);
	s.read(reinterpret_cast<char*>(value.data()), size);
	return value;
}



void variant_readString(std::istream & s, dm::variant & v)
{
	v = readString(s);
}



std::istream & operator >> (std::istream & s, dm::variant & v)
{
	uint8_t type = 0xFF;
	s.read(reinterpret_cast<char*>(&type), sizeof(uint8_t));
	switch (type)
	{
	case 0: variant_readString(s, v); break;
	case 1: variant_read<int>(s, v); break;
	case 2: variant_read<float>(s, v); break;
	case 3: variant_read<bool>(s, v); break;
	}

	return s;
}







std::istream & operator >> (std::istream & s, dm::properties & prop)
{
	size_t size = 0;
	s.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	for (size_t i = 0; i < size; i++)
	{
		const auto key = readString(s);
		dm::variant v;
		s >> v;
		prop.insert({ key, v });
	}
	return s;
}





//сериализация свойств
std::ostream & operator << (std::ostream & s, dm::properties const & prop)
{
	//запишем количество свойств
	const size_t size = prop.size();
	s.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

	for (const auto &item : prop)
	{
		writeString(s, item.first); //сериализуем ключь
		s << item.second; //сериализцем данные
	}
	return s;
}


