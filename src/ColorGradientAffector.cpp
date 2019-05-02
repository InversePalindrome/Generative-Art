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
    particle.setColor(particle.getColor() + (particle.getEndColor() - particle.getColor()) * (deltaTime / particle.getTotalLifeTime()));
}