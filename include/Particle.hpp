/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Particle.hpp
InversePalindrome.com
*/


#pragma once

#include <cinder/Vector.h>


class Particle
{
public:
	Particle();

	cinder::vec2 getPosition() const;
	void setPosition(const cinder::vec2& position);

	cinder::vec2 getScale() const;
	void setScale(const cinder::vec2& scale);

	float getAngle() const;
	void setAngle(float angle);

	cinder::vec2 getLinearVelocity() const;
	void setLinearVelocity(const cinder::vec2& linearVelocity);

	float getAngularVelocity() const;
	void setAngularVelocity(float angularVelocity);

	float getLifeTime() const;
	void setLifeTime(float lifeTime);

	std::size_t getTextureIndex() const;
	void setTextureIndex(std::size_t textureIndex);

private:
	cinder::vec2 position;
	cinder::vec2 scale;
	float angle;

	cinder::vec2 linearVelocity;
	float angularVelocity;

    float lifeTime;

	std::size_t textureIndex;
};