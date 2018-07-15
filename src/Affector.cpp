/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Affector.cpp
InversePalindrome.com
*/


#include "Affector.hpp"


Affector::Affector(AffectorType affectorType) :
	affectorType(affectorType)
{
}

AffectorType Affector::getAffectorType() const
{
	return affectorType;
}