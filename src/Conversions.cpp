/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Conversions.cpp
InversePalindrome.com
*/


#include "Conversions.hpp"


float Conversions::stringToFloat(const std::string& string, float optional)
{
	float value = 0.f;

	try
	{
		value = std::stof(string);
	}
	catch (const std::exception&)
	{
		return optional;
	}

	return value;
}