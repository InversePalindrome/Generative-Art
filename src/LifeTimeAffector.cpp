/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - LifeTimeAffector.cpp
InversePalindrome.com
*/


#include "LifeTimeAffector.hpp"


LifeTimeAffector::LifeTimeAffector() :
    Affector(AffectorType::LifeTime)
{
}

void LifeTimeAffector::update(Particle& particle, float deltaTime)
{
    particle.setCurrentLifeTime(particle.getCurrentLifeTime() + deltaTime);
}