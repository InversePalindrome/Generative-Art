/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - DefaultEmitter.cpp
InversePalindrome.com
*/


#include "Particle.hpp"
#include "DefaultEmitter.hpp"
#include "ParticleSystem.hpp"

#include <cinder/Rand.h>


DefaultEmitter::DefaultEmitter() :
	Emitter(EmitterType::Default),
	emissionDifference(0.f)
{
}

void DefaultEmitter::update(ParticleSystem& particleSystem, float deltaTime)
{
	for (std::size_t i = 0; i < numberOfEmittedParticles(deltaTime); ++i)
	{
		Particle particle;
		particle.setTotalLifeTime(getTotalLifeTime() + getLifeTimeVariance() * cinder::randFloat(-1.f, 1.f));
		particle.setPosition(getPosition() + getPositionVariance() * cinder::vec2(cinder::randFloat(-1.f, 1.f), cinder::randFloat(-1.f, 1.f)));
		particle.setScale( getScale() + getScaleVariance() * cinder::vec2(cinder::randFloat(-1.f, 1.f), cinder::randFloat(-1.f, 1.f)));
		particle.setAngle(getAngle() + getAngleVariance() * cinder::randFloat());
		particle.setLinearVelocity( getLinearVelocity() + getLinearVelocityVariance() * cinder::vec2(cinder::randFloat(-1.f, 1.f), cinder::randFloat(-1.f, 1.f)));
		particle.setAngularVelocity(getAngularVelocity() + getAngularVelocityVariance() * cinder::randFloat(-1.f, 1.f));
		particle.setColor(getStartColor() + getStartColorVariance() * cinder::ColorA(cinder::randFloat(), cinder::randFloat(), cinder::randFloat()));
		particle.setEndColor(getEndColor() + getEndColorVariance() * cinder::ColorA(cinder::randFloat(), cinder::randFloat(), cinder::randFloat()));
	
		particleSystem.addParticle(particle);
	}
}

std::size_t DefaultEmitter::numberOfEmittedParticles(float deltaTime)
{
	const auto particleAmount = getEmissionRate() * deltaTime + emissionDifference;
	const auto numberOfParticles = static_cast<std::size_t>(particleAmount);

	emissionDifference = particleAmount - numberOfParticles;

	return numberOfParticles;
}