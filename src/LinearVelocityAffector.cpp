/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - LinearVelocityAffector.cpp
InversePalindrome.com
*/


#include "LinearVelocityAffector.hpp"


LinearVelocityAffector::LinearVelocityAffector() :
	Affector(AffectorType::LinearVelocity)
{
}

void LinearVelocityAffector::update(Particle& particle, float deltaTime)
{
	particle.setPosition(particle.getPosition() + particle.getLinearVelocity() * deltaTime);
}