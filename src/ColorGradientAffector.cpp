/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ColorGradientAffector.cpp
InversePalindrome.com
*/


#include "ColorGradientAffector.hpp"


ColorGradientAffector::ColorGradientAffector() :
	Affector(AffectorType::ColorGradient)
{
}

void ColorGradientAffector::update(Particle& particle, float deltaTime)
{
	particle.setColor((particle.getEndColor() - particle.getColor()) * (1 / particle.getTotalLifeTime()) + particle.getColor());
}