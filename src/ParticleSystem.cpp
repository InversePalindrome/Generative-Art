/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ParticleSystem.cpp
InversePalindrome.com
*/


#include "ParticleSystem.hpp"
#include "TextureManager.hpp"

#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>

#include <pugixml.hpp>

#include <limits>


ParticleSystem::ParticleSystem() :
	randomEngine(std::random_device()()),
	emissionRate(1.f),
	emissionDifference(0.f),
	lifeTime(100.f),
	lifeTimeVariance(0.f),
	position(0.f, 0.f),
	positionVariance(0.f, 0.f),
	scale(1.f, 1.f),
	scaleVariance(0.f, 0.f),
	angle(0.f),
	angleVariance(0.f),
	linearVelocity(0.f, 0.f),
	linearVelocityVariance(0.f, 0.f),
	angularVelocity(0.f),
	angularVelocityVariance(0.f)
{
}

ParticleSystem::ParticleSystem(const std::string& filename) :
	ParticleSystem()
{
	load(filename);
}

void ParticleSystem::load(const std::string & filename)
{
	pugi::xml_document doc;
	
	if (doc.load_file(cinder::app::getAssetPath(filename).c_str()))
	{
		if (const auto particleSystemNode = doc.child("ParticleSystem"))
		{
			if (const auto emissionRateAttribute = particleSystemNode.attribute("emissionRate"))
			{
				emissionRate = emissionRateAttribute.as_float();
			}
			if (const auto lifeTimeAttribute = particleSystemNode.attribute("lifeTime"))
			{
				lifeTime = lifeTimeAttribute.as_float();
			}
			if (const auto lifeTimeVarianceAttribute = particleSystemNode.attribute("lifeTimeVariance"))
			{
			    lifeTimeVariance = lifeTimeVarianceAttribute.as_float();
			}
			if (const auto xPositionAttribute = particleSystemNode.attribute("xPosition"))
			{
				position.x = xPositionAttribute.as_float();
			}
			if (const auto yPositionAttribute = particleSystemNode.attribute("yPosition"))
			{
			    position.y = yPositionAttribute.as_float();
			}
			if (const auto xPositionVarianceAttribute = particleSystemNode.attribute("xPositionVariance"))
			{
				positionVariance.x = xPositionVarianceAttribute.as_float();
			}
			if (const auto yPositionVarianceAttribute = particleSystemNode.attribute("yPositionVariance"))
			{
				positionVariance.y = yPositionVarianceAttribute.as_float();
			}
			if (const auto widthScaleAttribute = particleSystemNode.attribute("widthScale"))
			{
				scale.x = widthScaleAttribute.as_float();
			}
			if (const auto heightScaleAttribute = particleSystemNode.attribute("heightScale"))
			{
				scale.y = heightScaleAttribute.as_float();
			}
			if (const auto widthScaleVarianceAttribute = particleSystemNode.attribute("widthScaleVariance"))
			{
				scaleVariance.x = widthScaleVarianceAttribute.as_float();
			}
			if (const auto heightScaleVarianceAttribute = particleSystemNode.attribute("heightScaleVariance"))
			{
				scaleVariance.y = heightScaleVarianceAttribute.as_float();
			}
			if (const auto angleAttribute = particleSystemNode.attribute("angle"))
			{
				angle = angleAttribute.as_float();;
			}
			if (const auto angleVarianceAttribute = particleSystemNode.attribute("angleVariance"))
			{
				angleVariance = angleVarianceAttribute.as_float();
			}
			if (const auto xLinearVelocityAttribute = particleSystemNode.attribute("XlinearVelocity"))
			{
			    linearVelocity.x = xLinearVelocityAttribute.as_float();
			}
			if (const auto yLinearVelocityAttribute = particleSystemNode.attribute("yLinearVelocity"))
			{
			    linearVelocity.y = yLinearVelocityAttribute.as_float();
			}
			if (const auto xLinearVelocityVarianceAttribute = particleSystemNode.attribute("xLinearVelocityVariance"))
			{
				linearVelocityVariance.x = xLinearVelocityVarianceAttribute.as_float();
			}
			if (const auto yLinearVelocityVarianceAttribute = particleSystemNode.attribute("yLinearVelocityVariance"))
			{
				linearVelocityVariance.y = yLinearVelocityVarianceAttribute.as_float();
			}
			if (const auto angularVelocityAttribute = particleSystemNode.attribute("angularVelocity"))
			{
				angularVelocity = angularVelocityAttribute.as_float();
			}
			if (const auto angularVelocityVarianceAttribute = particleSystemNode.attribute("angularVelocityVariance"))
			{
				angularVelocityVariance = angularVelocityVarianceAttribute.as_float();
			}

			for (const auto particleNode : particleSystemNode.children("Texture"))
			{
				textures.push_back(&TextureManager::getInstance()[Texture::_from_string(particleNode.text().as_string())]);

				std::size_t textureWeight = 1u;

				if (const auto textureWeightAttribute = particleNode.attribute("weight"))
				{
					textureWeight = textureWeightAttribute.as_uint();
				}

				textureWeights.push_back(textureWeight);
			}
		}
	}
}

void ParticleSystem::update(float deltaTime)
{
	for (auto& particle : particles)
	{
		particle.setPosition(particle.getPosition() + deltaTime * particle.getLinearVelocity());
		particle.setAngle(particle.getAngle() + deltaTime * particle.getAngularVelocity());
		particle.setLifeTime(particle.getLifeTime() - deltaTime);
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

		cinder::gl::draw(*textures[particle.getTextureIndex()]);
			
		cinder::gl::popModelMatrix();
	}
}

void ParticleSystem::addParticles(std::size_t particleCount)
{
	for (std::size_t i = 0u; i < particleCount; ++i)
	{
		Particle particle;
		particle.setPosition({ position.x + positionVariance.x * cinder::randFloat(-1.f, 1.f), position.y + positionVariance.y * cinder::randFloat(-1.f, 1.f) });
		particle.setScale({ scale.x + scaleVariance.x * cinder::randFloat(-1.f, 1.f), scale.y  + scaleVariance.y * cinder::randFloat(-1.f, 1.f)});
		particle.setAngle(angle + angleVariance * cinder::randFloat(-1.f, 1.f));
		particle.setLinearVelocity({ linearVelocity.x + linearVelocityVariance.x * cinder::randFloat(-1.f, 1.f), linearVelocity.y + linearVelocityVariance.y * cinder::randFloat(-1.f, 1.f) });
		particle.setAngularVelocity(angularVelocity + angularVelocityVariance * cinder::randFloat(-1.f, 1.f));
		particle.setLifeTime(lifeTime + lifeTimeVariance * cinder::randFloat(-1.f, 1.f));

		std::discrete_distribution<> textureDistribution(std::cbegin(textureWeights), std::cend(textureWeights));
		particle.setTextureIndex(textureDistribution(randomEngine));

		particles.push_back(particle);
	}
}

void ParticleSystem::clearParticles()
{
	particles.clear();
}

float ParticleSystem::getEmissionRate() const
{
	return emissionRate;
}

void ParticleSystem::setEmissionRate(float emissionRate)
{
	this->emissionRate = emissionRate;
}

float ParticleSystem::getLifeTime() const
{
	return lifeTime;
}

void ParticleSystem::setLifeTime(float lifeTime)
{
	this->lifeTime = lifeTime;
}

float ParticleSystem::getLifeTimeVariance() const
{
	return lifeTime;
}

void ParticleSystem::setLifeTimeVariance(float lifeTime)
{
	this->lifeTime = lifeTime;
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

void ParticleSystem::createParticles(float deltaTime)
{
	auto particleAmount = emissionRate * deltaTime + emissionDifference;
	auto numberOfParticles = static_cast<std::size_t>(particleAmount);

	emissionDifference = particleAmount - numberOfParticles;

	addParticles(numberOfParticles);
}

void ParticleSystem::removeDeadParticles()
{
	particles.erase(std::remove_if(std::begin(particles), std::end(particles), [](const auto& particle) { return particle.getLifeTime() <= 0.f; }), std::end(particles));
}