/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ParticleSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Particle.hpp"

#include <cinder/gl/Texture.h>

#include <string>
#include <vector>


class ParticleSystem
{
public:
	explicit ParticleSystem(const std::string& filename="");

	void load(const std::string & filename);

	void update(float deltaTime);
	void draw();

	void addParticles(std::size_t particleCount);
	void clearParticles();

	void setTexture(const cinder::gl::Texture2dRef& texture);

	cinder::vec2 getSourcePosition() const;
	void setSourcePosition(const cinder::vec2& sourcePosition);

	cinder::vec2 getRange() const;
	void setRange(const cinder::vec2& range);

	cinder::vec2 getMinScale() const;
	void setMinScale(const cinder::vec2& minScale);

	cinder::vec2 getMaxScale() const;
	void setMaxScale(const cinder::vec2& maxScale);

	float getMinAngle() const;
	void setMinAngle(float minAngle);

	float getMaxAngle() const;
	void setMaxAngle(float maxAngle);

	cinder::vec2 getMinLinearVelocity() const;
	void setMinLinearVelocity(const cinder::vec2& minLinearVelocity);

	cinder::vec2 getMaxLinearVelocity() const;
	void setMaxLinearVelocity(const cinder::vec2& maxLinearVelocity);

	float getMinAngularVelocity() const;
	void setMinAngularVelocity(float minAngularVelocity);

	float getMaxAngularVelocity() const;
	void setMaxAngularVelocity(float maxAngularVelocity);

private:
	std::vector<Particle> particles;

	const cinder::gl::Texture2dRef* texture;

	cinder::vec2 sourcePosition;
	cinder::vec2 range;

	cinder::vec2 minScale;
	cinder::vec2 maxScale;

	float minAngle;
	float maxAngle;

	cinder::vec2 minLinearVelocity;
	cinder::vec2 maxLinearVelocity;

	float minAngularVelocity;
	float maxAngularVelocity;
};