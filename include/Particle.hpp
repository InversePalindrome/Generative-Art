/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Particle.hpp
InversePalindrome.com
*/


#pragma once

#include <cinder/Color.h>
#include <cinder/Vector.h>

#include <chrono>


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

	cinder::Colorf getColor() const;
	void setColor(const cinder::Colorf& color);

	std::chrono::milliseconds getLifeTime() const;
	void setLifeTime(const std::chrono::milliseconds& lifeTime);

private:
	cinder::vec2 position;
	cinder::vec2 scale;
	float angle;

	cinder::vec2 linearVelocity;
	float angularVelocity;

	cinder::Colorf color;

	std::chrono::milliseconds lifeTime;
};