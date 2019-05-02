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

void Affector::load(const pugi::xml_node& affectorNode)
{
}

void Affector::save(pugi::xml_node& affectorNode) const
{
    affectorNode.append_attribute("type") = affectorType._to_string();
}

AffectorType Affector::getAffectorType() const
{
    return affectorType;
}