/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - LifeTimeAffector.hpp
InversePalindrome.com
*/


#pragma once

#include "Affector.hpp"


class LifeTimeAffector : public Affector
{
public:
	virtual void update(Particle& particle, float deltaTime) override;
};