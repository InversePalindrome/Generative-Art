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

#include <pugixml.hpp>


ParticleSystem::ParticleSystem(const std::string& filename) :
	sourcePosition(0.f, 0.f),
	range(100.f, 100.f),
	minScale(1.f, 1.f),
	maxScale(1.f, 1.f),
	minAngle(0.f),
	maxAngle(1.f),
	minLinearVelocity(0.f, 0.f),
	maxLinearVelocity(0.f, 0.f),
	minAngularVelocity(0.f),
	maxAngularVelocity(0.f)
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
			if (const auto sourcePositionXAttribute = particleSystemNode.attribute("xPosition"))
			{
				sourcePosition.x = sourcePositionXAttribute.as_float();
			}
			if (const auto sourcePositionYAttribute = particleSystemNode.attribute("yPosition"))
			{
				sourcePosition.y = sourcePositionYAttribute.as_float();
			}
			if (const auto rangeWidthAttribute = particleSystemNode.attribute("rangeWidth"))
			{
				range.x = rangeWidthAttribute.as_float();
			}
			if (const auto rangeHeightAttribute = particleSystemNode.attribute("rangeHeight"))
			{
				range.y = rangeHeightAttribute.as_float();
			}
			if (const auto minScaleWidthAttribute = particleSystemNode.attribute("minScaleWidth"))
			{
				minScale.x = minScaleWidthAttribute.as_float();
			}
			if (const auto minScaleHeightAttribute = particleSystemNode.attribute("minScaleHeight"))
			{
				minScale.y = minScaleHeightAttribute.as_float();
			}
			if (const auto maxScaleWidthAttribute = particleSystemNode.attribute("maxScaleWidth"))
			{
				maxScale.x = maxScaleWidthAttribute.as_float();
			}
			if (const auto maxScaleHeightAttribute = particleSystemNode.attribute("maxScaleHeight"))
			{
				maxScale.y = maxScaleHeightAttribute.as_float();
			}
			if (const auto minAngleAttribute = particleSystemNode.attribute("minAngle"))
			{
				minAngle = minAngleAttribute.as_float();;
			}
			if (const auto maxAngleAttribute = particleSystemNode.attribute("maxAngle"))
			{
				maxAngle = maxAngleAttribute.as_float();
			}
			if (const auto minLinearVelocityXAttribute = particleSystemNode.attribute("minLinearVelocityX"))
			{
				minLinearVelocity.x = minLinearVelocityXAttribute.as_float();
			}
			if (const auto minLinearVelocityYAttribute = particleSystemNode.attribute("minLinearVelocityY"))
			{
				minLinearVelocity.y = minLinearVelocityYAttribute.as_float();
			}
			if (const auto maxLinearVelocityXAttribute = particleSystemNode.attribute("maxLinearVelocityX"))
			{
				maxLinearVelocity.x = maxLinearVelocityXAttribute.as_float();
			}
			if (const auto maxLinearVelocityYAttribute = particleSystemNode.attribute("maxLinearVelocityY"))
			{
				maxLinearVelocity.y = maxLinearVelocityYAttribute.as_float();
			}
			if (const auto minAngularVelocityAttribute = particleSystemNode.attribute("minAngularVelocity"))
			{
				minAngularVelocity = minAngularVelocityAttribute.as_float();
			}
			if (const auto maxAngularVelocityAttribute = particleSystemNode.attribute("maxAngularVelocity"))
			{
				maxAngularVelocity = maxAngularVelocityAttribute.as_float();
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
	}
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
		cinder::gl::draw(*texture);

		cinder::gl::popModelMatrix();
	}
}

void ParticleSystem::addParticles(std::size_t particleCount)
{
	for (std::size_t i = 0u; i < particleCount; ++i)
	{
		Particle particle;
		particle.setPosition({ sourcePosition.x + cinder::randFloat(range.x), sourcePosition.y + cinder::randFloat(range.y) });
		particle.setScale({ cinder::randFloat(minScale.x, maxScale.x), cinder::randFloat(minScale.y, maxScale.y) });
		particle.setAngle(cinder::randFloat(minAngle, maxAngle));
		particle.setLinearVelocity({ cinder::randFloat(minLinearVelocity.x, maxLinearVelocity.x), cinder::randFloat(minLinearVelocity.y, maxLinearVelocity.y) });
		particle.setAngularVelocity(cinder::randFloat(minAngularVelocity, maxAngularVelocity));

		particles.push_back(particle);
	}
}

void ParticleSystem::clearParticles()
{
	particles.clear();
}

void ParticleSystem::setTexture(const cinder::gl::Texture2dRef& texture)
{
	this->texture = &texture;
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

cinder::vec2 ParticleSystem::getMinScale() const
{
	return minScale;
}

void ParticleSystem::setMinScale(const cinder::vec2& minScale)
{
	this->minScale = minScale;
}

cinder::vec2 ParticleSystem::getMaxScale() const
{
	return maxScale;
}

void ParticleSystem::setMaxScale(const cinder::vec2& maxScale)
{
	this->maxScale = maxScale;
}

float ParticleSystem::getMinAngle() const
{
	return minAngle;
}

void ParticleSystem::setMinAngle(float minAngle)
{
	this->minAngle = minAngle;
}

float ParticleSystem::getMaxAngle() const
{
	return maxAngle;
}

void ParticleSystem::setMaxAngle(float maxAngle)
{
	this->maxAngle = maxAngle;
}

cinder::vec2 ParticleSystem::getMinLinearVelocity() const
{
	return minLinearVelocity;
}

void ParticleSystem::setMinLinearVelocity(const cinder::vec2& minLinearVelocity)
{
	this->minLinearVelocity = minLinearVelocity;
}

cinder::vec2 ParticleSystem::getMaxLinearVelocity() const
{
	return maxLinearVelocity;
}

void ParticleSystem::setMaxLinearVelocity(const cinder::vec2& maxLinearVelocity)
{
	this->maxLinearVelocity = maxLinearVelocity;
}

float ParticleSystem::getMinAngularVelocity() const
{
	return minAngularVelocity;
}

void ParticleSystem::setMinAngularVelocity(float minAngularVelocity)
{
	this->minAngularVelocity = minAngularVelocity;
}

float ParticleSystem::getMaxAngularVelocity() const
{
	return maxAngularVelocity;
}

void ParticleSystem::setMaxAngularVelocity(float maxAngularVelocity)
{
	this->maxAngularVelocity = maxAngularVelocity;
}