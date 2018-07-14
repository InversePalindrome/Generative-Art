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
	emissionDifference(0.f)
{
}

void DefaultEmitter::update(ParticleSystem& particleSystem, float deltaTime)
{
	for (std::size_t i = 0; i < numberOfEmittedParticles(deltaTime); ++i)
	{
		Particle particle;
		particle.setTotalLifeTime(getTotalLifeTime() + getLifeTimeVariance() * cinder::randFloat(-1.f, 1.f));
		particle.setPosition({ getPosition() + getPositionVariance() * cinder::randFloat(-1.f, 1.f) });
		particle.setScale({ getScale() + getScaleVariance() * cinder::randFloat(-1.f, 1.f) });
		particle.setAngle(getAngle() + getAngleVariance() * cinder::randFloat(-1.f, 1.f));
		particle.setLinearVelocity({ getLinearVelocity() + getLinearVelocityVariance() * cinder::randFloat(-1.f, 1.f) });
		particle.setAngularVelocity(getAngularVelocity() + getAngularVelocityVariance() * cinder::randFloat(-1.f, 1.f));
		particle.setColor(getStartColor() + getStartColorVariance() * cinder::randFloat(-1.f, 1.f));
		particle.setEndColor(getEndColor() + getEndColorVariance() * cinder::randFloat(-1.f, 1.f));

		particleSystem.emitParticle(particle);
	}
}

std::size_t DefaultEmitter::numberOfEmittedParticles(float deltaTime)
{
	const auto particleAmount = getEmissionRate() * deltaTime + emissionDifference;
	const auto numberOfParticles = static_cast<std::size_t>(particleAmount);

	emissionDifference = particleAmount - numberOfParticles;

	return numberOfParticles;
}