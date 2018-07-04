/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Particle.cpp
InversePalindrome.com
*/


#include "Particle.hpp"


Particle::Particle(const cinder::vec2& position) :
	position(position)
{
}

cinder::vec2 Particle::getPosition() const
{
	return position;
}

void Particle::setPosition(const cinder::vec2& position)
{
	this->position = position;
}

cinder::vec2 Particle::getVelocity() const
{
	return velocity;
}

void Particle::setVelocity(const cinder::vec2& velocity)
{
	this->velocity = velocity;
}

std::chrono::milliseconds Particle::getLifeTime() const
{
	return lifeTime;
}

void Particle::setLifeTime(const std::chrono::milliseconds& lifeTime)
{
	this->lifeTime = lifeTime;
}