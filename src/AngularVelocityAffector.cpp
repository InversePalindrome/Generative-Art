/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - AngularVelocityAffector.cpp
InversePalindrome.com
*/


#include "AngularVelocityAffector.hpp"


void AngularVelocityAffector::update(Particle& particle, float deltaTime)
{
	particle.setAngle(particle.getAngle() + particle.getAngularVelocity() * deltaTime);
}