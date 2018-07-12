/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ParticleSystem.cpp
InversePalindrome.com
*/


#include "ParticleSystem.hpp"

#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>


ParticleSystem::ParticleSystem() :
	emissionRate(5.f),
	emissionDifference(0.f),
	totalLifeTime(100.f),
	lifeTimeVariance(0.f),
	position(0.f, 0.f),
	positionVariance(250.f, 250.f),
	scale(1.f, 1.f),
	scaleVariance(0.f, 0.f),
	angle(0.f),
	angleVariance(0.f),
	linearVelocity(0.f, 0.f),
	linearVelocityVariance(0.f, 0.f),
	angularVelocity(0.f),
	angularVelocityVariance(0.f),
	startColor(cinder::ColorA::white()),
	startColorVariance(cinder::ColorA::white()),
	endColor(cinder::ColorA::white()),
	endColorVariance(cinder::ColorA::white())
{
}

void ParticleSystem::update(float deltaTime)
{
	for (auto& particle : particles)
	{
		particle.setCurrentLifeTime(particle.getCurrentLifeTime() + deltaTime);
		particle.setPosition(particle.getPosition() + deltaTime * particle.getLinearVelocity());
		particle.setAngle(particle.getAngle() + deltaTime * particle.getAngularVelocity());
		particle.setColor((particle.getEndColor() - particle.getColor()) * (1 / particle.getTotalLifeTime()) + particle.getColor());
	}
	
	createParticles(deltaTime);
	removeDeadParticles();
}

void ParticleSystem::draw()
{
	for (const auto& particle : particles)
	{
		cinder::gl::pushModelMatrix();

		cinder::gl::translate(particle.getPosition().x, particle.getPosition().y);
		cinder::gl::scale(particle.getScale());
		cinder::gl::rotate(particle.getAngle());
		cinder::gl::color(particle.getColor());

		cinder::gl::draw(texture);
		
		cinder::gl::popModelMatrix();
	}
}

void ParticleSystem::addParticles(std::size_t particleCount)
{
	for (std::size_t i = 0u; i < particleCount; ++i)
	{
		Particle particle;
		particle.setTotalLifeTime(totalLifeTime + lifeTimeVariance * cinder::randFloat(-1.f, 1.f));
		particle.setPosition({ position.x + positionVariance.x * cinder::randFloat(-1.f, 1.f), position.y + positionVariance.y * cinder::randFloat(-1.f, 1.f) });
		particle.setScale({ scale.x + scaleVariance.x * cinder::randFloat(-1.f, 1.f), scale.y  + scaleVariance.y * cinder::randFloat(-1.f, 1.f)});
		particle.setAngle(angle + angleVariance * cinder::randFloat(-1.f, 1.f));
		particle.setLinearVelocity({ linearVelocity.x + linearVelocityVariance.x * cinder::randFloat(-1.f, 1.f), linearVelocity.y + linearVelocityVariance.y * cinder::randFloat(-1.f, 1.f) });
		particle.setAngularVelocity(angularVelocity + angularVelocityVariance * cinder::randFloat(-1.f, 1.f));
		particle.setColor(startColor + startColorVariance * cinder::randFloat(-1.f, 1.f));
		particle.setEndColor(endColor + endColorVariance * cinder::randFloat(-1.f, 1.f));

		particles.push_back(particle);
	}
}

void ParticleSystem::clearParticles()
{
	particles.clear();
}

void ParticleSystem::setTexture(cinder::gl::Texture2dRef texture)
{
	this->texture = texture;
}

float ParticleSystem::getEmissionRate() const
{
	return emissionRate;
}

void ParticleSystem::setEmissionRate(float emissionRate)
{
	this->emissionRate = emissionRate;
}

float ParticleSystem::getTotalLifeTime() const
{
	return totalLifeTime;
}

void ParticleSystem::setTotalLifeTime(float totalLifeTime)
{
	this->totalLifeTime = totalLifeTime;
}

float ParticleSystem::getLifeTimeVariance() const
{
	return lifeTimeVariance;
}

void ParticleSystem::setLifeTimeVariance(float lifeTimeVariance)
{
	this->lifeTimeVariance = lifeTimeVariance;
}

cinder::vec2 ParticleSystem::getPosition() const
{
	return position;
}

void ParticleSystem::setPosition(const cinder::vec2& pPosition)
{
	this->position = position;
}

cinder::vec2 ParticleSystem::getPositionVariance() const
{
	return positionVariance;
}

void ParticleSystem::setPositionVariance(const cinder::vec2& positionVariance)
{
	this->positionVariance = positionVariance;
}

cinder::vec2 ParticleSystem::getScale() const
{
	return scale;
}

void ParticleSystem::setScale(const cinder::vec2& scale)
{
	this->scale = scale;
}

cinder::vec2 ParticleSystem::getScaleVariance() const
{
	return scaleVariance;
}

void ParticleSystem::setScaleVariance(const cinder::vec2& scaleVariance)
{
	this->scaleVariance = scaleVariance;
}

float ParticleSystem::getAngle() const
{
	return angle;
}

void ParticleSystem::setAngle(float angle)
{
	this->angle = angle;
}

float ParticleSystem::getAngleVariance() const
{
	return angleVariance;
}

void ParticleSystem::setAngleVariance(float angleVariance)
{
	this->angleVariance = angleVariance;
}

cinder::vec2 ParticleSystem::getLinearVelocity() const
{
	return linearVelocity;
}

void ParticleSystem::setLinearVelocity(const cinder::vec2& linearVelocity)
{
	this->linearVelocity = linearVelocity;
}

cinder::vec2 ParticleSystem::getLinearVelocityVariance() const
{
	return linearVelocityVariance;
}

void ParticleSystem::setLinearVelocityVariance(const cinder::vec2& linearVelocityVariance)
{
	this->linearVelocityVariance = linearVelocityVariance;
}

float ParticleSystem::getAngularVelocity() const
{
	return angularVelocity;
}

void ParticleSystem::setAngularVelocity(float angularVelocity)
{
	this->angularVelocity = angularVelocity;
}

float ParticleSystem::getAngularVelocityVariance() const
{
	return angularVelocityVariance;
}

void ParticleSystem::setAngularVelocityVariance(float angularVelocityVariance)
{
	this->angularVelocityVariance = angularVelocityVariance;
}

cinder::ColorA ParticleSystem::getStartColor() const
{
	return startColor;
}

void ParticleSystem::setStartColor(const cinder::ColorA& startColor)
{
	this->startColor = startColor;
}

cinder::ColorA ParticleSystem::getStartColorVariance() const
{
	return startColorVariance;
}

void ParticleSystem::setStartColorVariance(const cinder::ColorA& startColorVariance)
{
	this->startColorVariance = startColorVariance;
}

cinder::ColorA ParticleSystem::getEndColor() const
{
	return endColor;
}

void ParticleSystem::setEndColor(const cinder::ColorA& endColor)
{
	this->endColor = endColor;
}

cinder::ColorA ParticleSystem::getEndColorVariance() const
{
	return endColorVariance;
}

void ParticleSystem::setEndColorVariance(const cinder::ColorA& endColorVariance)
{
	this->endColorVariance = endColorVariance;
}

void ParticleSystem::createParticles(float deltaTime)
{
	auto particleAmount = emissionRate * deltaTime + emissionDifference;
	auto numberOfParticles = static_cast<std::size_t>(particleAmount);

	emissionDifference = particleAmount - numberOfParticles;

	addParticles(numberOfParticles);
}

void ParticleSystem::removeDeadParticles()
{
	particles.erase(std::remove_if(std::begin(particles), std::end(particles), [](const auto& particle) { return particle.getCurrentLifeTime() >= particle.getTotalLifeTime(); }), std::end(particles));
}