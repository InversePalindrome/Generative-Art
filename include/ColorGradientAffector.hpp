/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - AngularVelocityAffector.cpp
InversePalindrome.com
/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ColorGradientAffector.hpp
InversePalindrome.com
*/


#pragma once

#include "Affector.hpp"


class ColorGradientAffector : public Affector
{
public:
	ColorGradientAffector();

	virtual void update(Particle& particle, float deltaTime) override;
};