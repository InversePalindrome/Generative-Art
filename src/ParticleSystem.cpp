/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ParticleSystem.cpp
InversePalindrome.com
*/


#include "ParticleSystem.hpp"

#include <cinder/Rand.h>
#include <cinder/gl/wrapper.h>


ParticleSystem::ParticleSystem() :
	sourcePosition(0.f, 0.f),
	range(100.f, 100.f)
{
}

void ParticleSystem::update()
{

}

void ParticleSystem::draw()
{
	for (const auto& particle : particles)
	{
		//cinder::gl::vertexAttrib2f(0, particle.getPosition().x, particle.getPosition().y);
	}
}

void ParticleSystem::addParticles(std::size_t particleCount)
{
	for (std::size_t i = 0u; i < particleCount; ++i)
	{
		particles.push_back(Particle({ sourcePosition.x + range.x * cinder::randFloat(), sourcePosition.y + range.y * cinder::randFloat() }));
	}
}

void ParticleSystem::clearParticles()
{
	particles.clear();
}

cinder::vec2 ParticleSystem::getSourcePosition() const
{
	return sourcePosition;
}

void ParticleSystem::setSourcePosition(const cinder::vec2& sourcePosition)
{
	this->sourcePosition = sourcePosition;
}

cinder::vec2 ParticleSystem::getRange() const
{
	return range;
}

void ParticleSystem::setRange(const cinder::vec2& range)
{
	this->range = range;
}