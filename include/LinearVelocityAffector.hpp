/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - LinearVelocityAffector.hpp
InversePalindrome.com
*/


#pragma once

#include "Affector.hpp"


class LinearVelocityAffector : public Affector
{
public:
	LinearVelocityAffector();

	virtual void update(Particle& particle, float deltaTime) override;
};