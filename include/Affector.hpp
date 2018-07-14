/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Affector.hpp
InversePalindrome.com
*/


#pragma once

#include "Particle.hpp"


class Affector
{
public:
	virtual void update(Particle& particle, float deltaTime)=0;
};